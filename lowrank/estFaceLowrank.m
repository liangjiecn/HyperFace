% test Yinqiang's algorithm on on-line hyperspectral dataset
function [Rest, Iest] = estFaceLowrank(varargin)
% varargin 1: hyperspectral images
% varargin 2: database used to create the basis
% varargin 3: subspace dimension
% close all,
%addpath   

Image = varargin{1};
[band, pixel] = size(Image);
rband = [400:0.5:1000];

%----------Build the basis of the low rank hyperspectral images--------% 


database = varargin{2};
[Bases] = PCA_ZeroMean(database.');
subdim = 3; 

%load the illumination spectra
% load INCFLU.mat
% L = INC_OF;
% L = L(1:2:end);
% L = L/max(L);
L = ones(1,band);


% Construct data matrix
Data = Image;

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

Iest = Lestn;
Rest = Ref;





