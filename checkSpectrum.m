%check whether the low accuracy of spectral profiles is due to the systematic error of spectralmeter or normalization 
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
%% count faces per person
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
save('faceinfor.mat', 'faceinfor');
end

% get statistical results for each date on the same day 
dface = cell(50,1); 
faceinfor = faceinfor(1:322,:);
sface = sortrows(faceinfor, -2); % face infor sortted by date
olddate = sface{1,2};
s1date = [];
% figure, hold all;
inddate = 1;
indface = 1;
for i = 1: length(sface)
    newdate = sface{i,2};
    if ~strcmp(olddate, newdate)
       olddate = newdate;
       dface{inddate} = s1date;
       s1date = [];
       inddate = inddate + 1;
       indface = 1;
       hold off;
%        figure,
       hold all,
    end
    s1 = sface{i,4}(:,1);
    s1 = s1/norm(s1);
    s1date(indface,:) = s1';
    indface = indface + 1;
%     plot(400:0.5:1000,s1);  
end
dface{inddate} = s1date; %when it comes to the last one, it jump out of loop without assigning value 
matface = cell2mat(dface);
[coeff, score, latent] = pca(matface);
% figure, 
scatter3(score(:,1),score(:,2),score(:,3));
axis equal
xlabel('pc1');
ylabel('pc2');
zlabel('pc3');
% figure,
ccdate = corr(matface');
imagesc(ccdate);


oldsubject = faceinfor{1,1};
subjectface = cell(50,1); 
s1subject = [];
figure, hold all;
indsubject = 1;
indface = 1;
for i = 1: length(faceinfor)
    newsubject = faceinfor{i,1};
    if ~strcmp(oldsubject, newsubject) 
       oldsubject = newsubject;
       subjectface{indsubject} = s1subject;
       s1subject = [];
       indsubject = indsubject + 1;
       indface = 1;
%        hold off;
%        figure,
%        hold all,
    end
    s1 = faceinfor{i,4}(:,1);
    s1 = s1/norm(s1);
    s1subject(indface,:) = s1';
    indface = indface + 1;
%     plot(400:0.5:1000,s1);
end
subjectface{indsubject} = s1subject; %when it comes to the last one, it jump out of loop without assigning value 
matface = cell2mat(subjectface);
ccsubject = corr(matface');
% figure,
imagesc(ccsubject);
m1 = ones(size(ccsubject))-eye(size(ccsubject));
ccsubject = ccsubject.* m1;
[~,same] = max(ccsubject,[],2);
results = faceinfor(same,:);
tsubject = strcmp(results(:,1),faceinfor(:,1));
rsubject = sum(tsubject)/length(faceinfor)

tdate = strcmp(results(:,2),faceinfor(:,2));
rdate = sum(tdate)/length(faceinfor)





