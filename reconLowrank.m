% reconstruct spectrum using low rank method 

% close all,
clear,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p); 
cd(pathstr);
addpath(pathstr);
faceDataPath = '..\data\hsface\UWA-FSRD\UWA-FSRD';
addpath(genpath('lowrank'));
%cd(faceDataPath);
filename = fullfile(faceDataPath,'faceinfor.mat');
load(filename);

% build the spectra database using all regions of all faces
rawmat = cat(2,faceinfor{:,4});

% prepare data 
%show spectra for each date
faceSorted= sortrows(faceinfor, 2); % face infor sortted based on date 
[date,ia,ic] = unique(faceSorted(:,2));
facedate = cell(length(date),1);
for i = 1: length(date)
    index = find(ic == i);
    facedate{i} =  faceSorted(index,:);
end

Rmat = [];
Imat = zeros(1201,length(date));
for indexdate = 1:length(date)
% make an example
    radiance = cat(2,facedate{indexdate}{:,4});
% reconstruct 
    try [Rest, Iest] = estFaceLowrank(radiance, rawmat);
    catch err
        Rest = radiance;
    end
    Rmat = cat(2,Rmat,Rest);
    Imat(:,indexdate) = Iest;
end

% assigan reconstructed reflectance to original data 
reconface = faceSorted;
for i = 1: length(faceinfor)
    spec = Rmat(:,1+(i-1)*6: i*6);
    reconface{i,4} = spec;
end

% show the results
%     rband = [400:0.5:1000];
%     figure, plot(rband, Iest);



% numpixel = size(radiance,2);
% figure(2),
% hold all,
% for j = 1:numpixel
%     spec = radiance(:,j);
%     plot(rband, spec);
% end
% 
% figure(3),
% hold all,
% for j = 1:numpixel
%     spec = Rest(:,j);
%     plot(rband, spec);
% end




