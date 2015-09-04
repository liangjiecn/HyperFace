% Experiment 1
% Check if noisy bands on 3D LDP codes in lambda dimension generated on hyperspectral images come from the data or the method itself. 
addpath('3DLDP')
addpath('../common');
%If a path or file name contains spaces, enclose the input string in single quotes. 
datapath = 'C:/Users/s2882161/Documents/MATLAB/data/OnlineDatabase';
% select a hyperspectral image from each database
list = {[datapath '/Foster/example.mat'];[datapath '/Harvard/example.mat'];...
           [datapath '/CAVE/example.mat'];[datapath '/../SpectralLab/example.mat']};
subImageSize = [8,8,8];    
order = 2;
for i = 1 : length(list)
   filename = list{i};
   datacube =  importdata(filename);   
   [m,n,b] = size(datacube);
   [~, ldpData, ~] = mex3DLDP(datacube, subImageSize, order);
   % ldpX should also be tested as an comparision with ldpZ.
   ldpDataXTemp = ldpData(:,1:1*n*b);
   ldpDataX = reshape(ldpDataXTemp,m,n,b);
   ldpDataYTemp = ldpData(:,1+1*n*b:2*n*b);
   ldpDataY = reshape(ldpDataYTemp,m,n,b);
   ldpDataZTemp = ldpData(:,1+2*n*b:3*n*b);
   ldpDataZ = reshape(ldpDataZTemp,m,n,b);
   
   [zx, zy, zb] = size(ldpDataZ);
   % measure the clearance of each band of codes
   for j = 1:zb
       slice1 = squeeze(ldpDataX(:,:,j));
       localentropy1 = entropyfilt(slice1); 
       noiselevel1(j) = mean(localentropy1(:));
       
       slice2 = squeeze(ldpDataY(:,:,j));
       localentropy2 = entropyfilt(slice2); 
       noiselevel2(j) = mean(localentropy2(:));
       
       slice3 = squeeze(ldpDataZ(:,:,j));
       localentropy3 = entropyfilt(slice3); 
       noiselevel3(j) = mean(localentropy3(:));
   end
   h = figure(i); hold all,
   plot([1:zb],noiselevel1); 
   plot([1:zb],noiselevel2); 
   plot([1:zb],noiselevel3); 
   legend('ldpX', 'ldpY', 'ldpZ');
   figurename = ['./temp/example',num2str(i), '_noiselevel'];
   hgsave(h, figurename);
   ldpXname = ['./temp/example',num2str(i), '_ldpX',  '.mat'];
   save(ldpXname, 'ldpDataX');
   ldpYname = ['./temp/example',num2str(i), '_ldpY',  '.mat'];
   save(ldpYname, 'ldpDataY');
   ldpZname = ['./temp/example',num2str(i), '_ldpZ',  '.mat'];
   save(ldpZname, 'ldpDataZ');
end
    
       

       
       
       
       
        