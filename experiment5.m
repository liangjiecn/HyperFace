% experiment 5
close all,
datapath = './temp/';
% get all encoded pattern
list = {[datapath 'example1'];[datapath 'example2'];...
           [datapath 'example3'];[datapath 'example4']};
bincodes = cell(4,3);
bincodesSort = cell(4,3);
for i = 1:length(list)
   dataname = list{i};
   for j = 1:3
      switch j
          case 1 
              ldpname = '_ldpX.mat';
          case 2
              ldpname = '_ldpY.mat';
          case 3
              ldpname = '_ldpZ.mat';              
      end
      filename = [dataname, ldpname];
      ldp = importdata(filename);
      [m, n, b] = size(ldp);
      ldp = reshape(ldp, [m*n,b]);
%       figure,
      [counts,x] = imhist(ldp);
      imhist(ldp);
      [a, b] = sort(counts,'descend');
      freq = floor(256*0.1);
      codes = b(1:freq)-1;%from 0 to 255
      bincodes{i,j}= dec2bin(codes,8);
      bincodesSort{i,j} = sortrows(bincodes{i,j});
%       [pks,locs] = findpeaks(imhist(ldp));
      title(filename);
   end
end