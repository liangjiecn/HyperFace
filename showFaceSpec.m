%draw face spectra based on subject and date
% close all,
clear,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p); 
cd(pathstr);
addpath(pathstr);
faceDataPath = '..\data\hsface\UWA-FSRD\UWA-FSRD';
%cd(faceDataPath);
filename = fullfile(faceDataPath,'reconface.mat');
faceinfor = importdata(filename);
% show spectra for each subject
indregion = 3; % there are totally 6 regions
indsubject = 1;
numsubject = 3;
figure, hold all;
facespe = []; % 
faceinfor = sortrows(faceinfor, 1);
oldsubject = faceinfor{1,1}; % first date 
for i = 1: length(faceinfor)
    newsubject = faceinfor{i,1};
    if ~strcmp(oldsubject, newsubject)
       oldsubject = newsubject;
       facespe = [];
       if (indsubject == numsubject)
           break;
       end
       indsubject = indsubject + 1;
       hold off;
       figure,
       hold all,
    end
    s1 = faceinfor{i,4}(:,indregion);
    s1 = s1/norm(s1);
    plot(400:0.5:1000,s1);  
end

%show spectra for each date
facedate = sortrows(faceinfor, -2); % face infor sortted based on date
olddate = facedate{1,2}; % first date 
figure, hold all;
inddate = 1;
indface = 1;
numdate = 3;
for i = 1: length(facedate)
    newdate = facedate{i,2};
    if ~strcmp(olddate, newdate)
       olddate = newdate;
       facespe = [];
       if (inddate == numdate)
           break;
       end
       inddate = inddate + 1;
       indface = 1;
       hold off;
       figure,
       hold all,
    end
    s1 = facedate{i,4}(:,indregion);
    s1 = s1/norm(s1);
    plot(400:0.5:1000,s1);  
end


