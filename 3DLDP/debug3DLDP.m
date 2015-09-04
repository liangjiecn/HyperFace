% debug the 3D LDP mex
% [ldpHist, ldpData] = mexLDP(image, subImageSize, order)
datacube = importdata('session1_ns.mat');
[m,n,b] = size(datacube);
subImageSize = [4,4,4];
order = 2;
tic,
[ldpHist, ldpData, derivativeData] = mex3DLDP(datacube, subImageSize, order);
toc,
derivativeDataXTemp = derivativeData(:,1:n*b);
derivativeDataX = reshape(derivativeDataXTemp,m,n,b);
derivativeDataYTemp = derivativeData(:,1+n*b:2*n*b);
derivativeDataY = reshape(derivativeDataYTemp,m,n,b);
derivativeDataZTemp = derivativeData(:,1+2*n*b:3*n*b);
derivativeDataZ = reshape(derivativeDataZTemp,m,n,b);
            

ldpDataXTemp = ldpData(:,1:n*b);
ldpDataX = reshape(ldpDataXTemp,m,n,b);
ldpDataYTemp = ldpData(:,1+n*b:2*n*b);
ldpDataY = reshape(ldpDataYTemp,m,n,b);
ldpDataZTemp = ldpData(:,1+2*n*b:3*n*b);
ldpDataZ = reshape(ldpDataZTemp,m,n,b);




