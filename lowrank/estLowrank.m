% test Yinqiang's algorithm on on-line hyperspectral dataset
function [Rest, Iest] = estLowrank(varargin)
% varargin 1: hyperspectral images
% varargin 2: database used to create the basis
% varargin 3: subspace dimension
% close all,
%addpath
addpath('./data');
addpath('./dependency');    
if nargin < 1
    %load hyperspectral image
    load imCC18_INCFLU.mat
    Image = imCC18_INC_OF;
else
    if ischar(varargin{1})
        Image = importdata(varargin{1});
    else
        Image = varargin{1};
    end
end
% Read video
[height width band] = size(Image);
if band == 57
    rband = [420:5:700];
elseif band == 31
    Image = Image(:,:,2:end-1);
    rband = [420:10:700];
    band = 29;
elseif band == 65
    Image = double(Image);
    Image = Image(:,:,1:end-39);
    rband = [450:10:700];
    band = 26;
end


%----------Build the basis of the low rank hyperspectral images--------% 
if nargin < 2
    %load reflectance dataset
    load MacbethCCDC_380_730_10
    %from 420:700
    dbband = [380:10:730]; % database band index
    database = interp1(dbband,MacbethCCDC,rband);   
else
    if ischar(varargin{2})
        MacbethCCDC = importdata(varargin{2});
        temp = MacbethCCDC(:,:,2:end-1);
        temp = reshape(temp, [size(temp,1)*size(temp,2), size(temp,3)]);   
        database = temp';
    else 
        %spectral face
        database = varargin{2};
    end
end
[Bases] = PCA_ZeroMean(database.');
if nargin < 3
    %load reflectance dataset
    subdim = 3; 
else
    subdim = varargin{3} ;
end


%load the illumination spectra
% load INCFLU.mat
% L = INC_OF;
% L = L(1:2:end);
% L = L/max(L);
L = ones(1,band);


% Construct data matrix
Data = Image;
Data = reshape(Data,height*width,band);
Data = Data.';

% Scale Normalize
Data = Data/max(max(abs(Data)));

%Robust approximation 
%W = ones(size(Data));
%[Data_n U_est V_est L1_error] = RobustApproximation_M_UV_ALM(Data,W,8,1.2,1,1);
Data_n = Data;

%SVD factorization
[U S V] = svds(Data_n,subdim);

%Choose the best dimensionality s=3
for dim = subdim:subdim
    %QP with constraints
    temp = -kron(Bases(:,1:dim),ones(1,dim)).*kron(ones(1,dim),U(:,1:dim));
    Quad = [eye(dim^2) temp.'; temp diag(sum(Bases(:,1:dim).^2,2))];
    temp = max(Data_n,[],2);
    [tempval tempind] = max(temp);
    tempA = zeros(1,dim^2+band);
    tempA(dim^2+tempind) = 1;

    para.outputflag = 1;
    model.Q = sparse(Quad);
    model.obj = zeros(1,band+dim^2);
    model.lb = [-inf*ones(dim^2,1); temp];
    model.A = sparse(tempA);
    model.sense = '<';
    model.rhs = tempval*1.1;

    results  = gurobi(model,para);
    xx = results.x;
    Qt = reshape(xx(1:dim^2),dim,dim);
    Lest = xx(dim^2+1:end);
    
    %uncomment the following line for refinement
    %[Lest] = LocalRefinement_GeneralLight_L2_Linear(Lest, Bases(:,1:dim), Data_n);

    %rescale the estimated illumination spectra
    Lestn = Lest*dot(Lest,L)/dot(Lest,Lest);

    %estimate the reflectance spectra
    Ref = Bases(:,1:8)*(pinv(diag(Lest)*Bases(:,1:8))*Data_n);

    %Error(dim) = norm(L-Lestn);
end

%reshape into hyperspectral reflectance image
Ref = reshape(Ref,[band,height,width]);
Ref = permute(Ref,[2,3,1]);

%show the original hyperspectral image
Hyperspectral_to_RGB_Sample(Image,1,'Original');

%show the hyperspectral reflectance image
Hyperspectral_to_RGB_Sample(Ref,1,'Reflectance Image');

w= 350; h= 300;

%show recovered light spectra
datax = rband; datax = datax.';
i= 0;
figure('position',[w*i,100,w,h]);
box('on');
hold('all');

plot(datax,L,'k--','LineWidth',3); hold on; plot(datax,Lestn,'g','LineWidth',3); 
set(gca,'FontSize',20); xlim([420,700]); ylim([0,1.8]);
set(gca,'linewidth',2);
xtick= 420:70:700;
set(gca,'xtick',xtick);
legend('Measured','Recovered','Location','NorthWest');
title('Illumination Spectra');
grid on;
%xlabel('Wavelength','FontSize',18);






