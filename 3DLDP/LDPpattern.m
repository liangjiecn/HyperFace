% show the LDP pattern and based on it, find a way to maximise the
% information but supress noise 
clear,
close all,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p);
cd(pathstr);
addpath(genpath(pathstr));
addpath(genpath('../../common'));

datacube = importdata('session1_ns.mat');

datacube = smooth3(datacube, 'gaussian', [9 9 9], 0.8);
save('session1_gaussian.mat','datacube');           

datacube = uint8(datacube);
[m,n,b] = size(datacube);
subImageSize = [8,8,8];
order = 2;
[ldpHist, ldpData, derivativeData] = mex3DLDP(datacube, subImageSize, order);

derivativeDataXTemp = derivativeData(:,1:n*b);
derivativeDataX = reshape(derivativeDataXTemp,m,n,b);

derivativeDataYTemp = derivativeData(:,1+n*b:2*n*b);
derivativeDataY = reshape(derivativeDataYTemp,m,n,b);

derivativeDataZTemp = derivativeData(:,1+2*n*b:3*n*b);
derivativeDataZ = reshape(derivativeDataZTemp,m,n,b);
save('derivativeDataZ.mat','derivativeDataZ');           

ldpDataXTemp = ldpData(:,1:n*b);
ldpDataX = reshape(ldpDataXTemp,m,n,b);
save('ldpDataX.mat','ldpDataX');
ldpDataYTemp = ldpData(:,1+n*b:2*n*b);
ldpDataY = reshape(ldpDataYTemp,m,n,b);
save('ldpDataY.mat', 'ldpDataY');
ldpDataZTemp = ldpData(:,1+2*n*b:3*n*b);
ldpDataZ = reshape(ldpDataZTemp,m,n,b);

for i = 1:size(ldpDataZ,3)
   slice = ldpDataZ(:,:,i); 
   noiselevel1(i) = entropy(slice); 
   localentropy = entropyfilt(slice); 
   noiselevel2(i) = mean(localentropy(:));
   noiselevel3(i) = fmeasure(slice, 'GDER',[]);
end
figure, plot([450:10:1090], noiselevel1, 'b', [450:10:1090], noiselevel2, 'r');
figure, plot([450:10:1090], noiselevel3, 'g');
save('ldpDataZ.mat', 'ldpDataZ');

% View_Spec;