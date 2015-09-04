% recognition with spectra using correlation
close all,
clear,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p); 
cd(pathstr);
addpath(genpath(pathstr));
faceDataPath = '..\data\hsface\UWA-FSRD\UWA-FSRD';
%cd(faceDataPath);
filename = fullfile(faceDataPath,'faceinfor.mat');
%%----- reconstruction with low rank ----
% filename = fullfile(faceDataPath,'reconface.mat');
% it reduces the accuracy so far
%%--------------------------------%

faceinfor = importdata(filename);
% %----- reconstruction with PCA ----
% faceinfor = reconpca(faceinfor);
% %it reduces the accuracy so far
% %--------------------------------%

% faceinfor = extractgabor(faceinfor);

% calculate recognition rate based on each region
% leave one out strategy
dimfeature = length(faceinfor{1,4});
for repeat = 1:10
    [probeset, galleryset] = buildGalleryProbe(faceinfor);
    probeMat = [];
    galleryMat = [];
    for indregion = 1:7
        if indregion ~= 7 
            for i = 1: length(probeset)
                probeMat(:,i) = probeset{i,4}(:,indregion);
            end
            for i = 1: length(galleryset)
                galleryMat(:,i) = galleryset{i,4}(:,indregion);
            end
        else
            for i = 1: length(probeset)
                probeMat(:,i) = reshape(probeset{i,4}, [dimfeature*6,1]);
            end
            for i = 1: length(galleryset)
                galleryMat(:,i) = reshape(galleryset{i,4}, [dimfeature*6,1]);
            end
        end
        ccsubject = corr(probeMat,galleryMat);
        [~,same] = max(ccsubject,[],2);
        results = galleryset(same,:);
        tsubject = strcmp(results(:,1),probeset(:,1));
        rsubject(repeat, indregion) = sum(tsubject)/length(probeset);
    %     tdate = strcmp(results(:,2),faceinfor(:,2));
    %     rdate(indregion) = sum(tdate)/length(faceinfor);
    %     ttotal= or(tsubject, tdate);
    %     rtotal(indregion) = sum(ttotal)/length(faceinfor);
         probeMat = [];
         galleryMat = [];
    end
end
rm = mean(rsubject);
rstd = std(rsubject);
regionname = {'Forehead'; 'Right cheek'; 'Left cheek'; 'Lips'; 'Chin'; 'Hair'; 'All'};
recogindex = {'RecognitionRate', 'StandardDeviation'};
T = table(rm',rstd','RowNames',regionname , 'VariableNames',recogindex)

% 10 cross validation


