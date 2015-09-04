% seperating illumination and reflectance
% still working
close all,
clear,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p); 
cd(pathstr);
addpath(pathstr);
faceDataPath = '..\data\hsface\UWA-FSRD\UWA-FSRD';
cd(faceDataPath);
numofSubject = 40;

galleryData = cell(numofSubject, 2); % { person index, feature } 
probeData = cell(numofSubject, 2); % { person index, feature }

sf = zeros(1201,6);
if exist('faceinfor.mat', 'file')
    load('faceinfor.mat');
end

faceinfor = faceinfor(1:322,:);
sface = sortrows(faceinfor, -2); % face infor sortted by date
olddate = sface{1,2};
totaldata = [];
% figure, hold all;
inddate = 1;
indface = 1;
for i = 1: length(sface)
    newdate = sface{i,2};
    if ~strcmp(olddate, newdate)
       olddate = newdate;
       dface{inddate} = totaldata;
       totaldata = [];
       inddate = inddate + 1;
    end
    totaldata = cat(2,totaldata, sface{i,4});
    
%     plot(400:0.5:1000,s1);  
end
dface{inddate} = totaldata; %when it comes to the last one, it jump out of loop without assigning value 
matface = cell2mat(dface);
testmat = dface{3};
[U, S, V] = svd(testmat);% U m*m
% disp(s);
[coeff, score, latent] = pca(matface);
k = 8; % assume the rank is equal to 8
B = score(:,1:k); % m*k
C = coeff(:,1:k);
matfaceTemp = B*C';
matfaceR = bsxfun(@plus, matfaceTemp, mean(matface));

newdface = sface;
faceMat = zeros(1201, length(newdface));
for i = 1: length(newdface)
    faceR = matfaceR(:,1+(i-1)*6);
    newdface{i,4} = faceR;
    faceMat(:,i) = faceR;
end









% plot(matface(:,1));
% hold on,
% plot(matfaceR(:,1), 'r');

% UU = U(:,1:k)*U(:,1:k)';
% [Vector,Eigenvalue] = eig(UU);
% V1 = Vector(:,end);
% B1 = B(:,1);
% l1 = V1./B1;
% plot(l1), hold on
% V2 = Vector(:,end-1);
% B2 = B(:,2);
% l2 = V2./B2;
% plot(l2,'r');
% 
% V3 = Vector(:,end-2);
% B3 = B(:,3);
% l3 = V3./B3;
% plot(l3, 'g');



