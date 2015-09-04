%draw face spectra based on subject and date
close all,
clear,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p); 
cd(pathstr);
addpath(pathstr);
faceDataPath = '..\data\hsface\UWA-FSRD\UWA-FSRD';
cd(faceDataPath);
numofSubject = 40;
sf = zeros(1201,6);
if exist('faceinfor.mat', 'file')
    load('faceinfor.mat');
else
%% get face data from the UWA-FSRD database
subjectlist = dir('0*');  % subject includes "0"
faceindex = 1;
faceinfor = cell(325,4);
for i = 1: length(subjectlist) % save the file name of sessions from each person 
   subjectname = subjectlist(i).name;
   cd(subjectname);
   datalist = dir('*-*'); % data includes "-"
   for j = 1:length(datalist)
       dataname = datalist(j).name;
       cd(dataname);
       sessionlist = dir('s*');
       for k = 1:length(sessionlist)
          sessionname = sessionlist(k).name;
          cd(sessionname);
          regionlist = dir('*.TRM');
          for r = 1:6 % six regions 
              %!!! some folders have 10 .TRM files.
              regionname = regionlist(r).name;
              stru = importdata(regionname);
              sf(:,r) = stru.data(353:1553,2);
          end
          faceinfor{faceindex,4}= sf;
          faceinfor{faceindex,1}= subjectname;
          faceinfor{faceindex,2}= dataname;
          faceinfor{faceindex,3}= sessionname;
          faceindex = faceindex + 1;
          cd ..
       end
       cd ..      
   end
   cd ..
   disp(i);
end
faceinfor = faceinfor(1:faceindex-1,:);
save('faceinfor.mat', 'faceinfor');
end

