%% calculate the recognition rate of CMU hyerpsectral faces data 
% use the 3D Gabor LDP method to calculate the recognition rate with respect to 
% time variation
%% initial the function path and variables
clear,
close all,
p = mfilename('fullpath');
[pathstr,name,ext] = fileparts(p);
cd(pathstr);
addpath(genpath(pathstr));
addpath(genpath('..\common'));
faceDataPath = '..\data\hsface\CMUSimple';

numofSubject = 47;
subImageSize= [8, 8, 8]; % subregions for build histograms
order = 2; % LDP order
numofGabor = 52;
sizeofGarbor = 39;
[filters] = GenerateFilters_3D(sizeofGarbor); 
numofBins = 8*8*7*16*3;
num_filters = 13;
combinedFeature = zeros(numofBins, num_filters);
faceInfo = cell(47,1);
% count faces per person
subjectSet = dir([faceDataPath,'\','04*']);
for i = 1: 47
    faceInfo{i} = dir([faceDataPath, '\', subjectSet(i).name, '\', 'session*_ns.mat']);
end

%% extract 3DGLDP feature for each face
faceDataName = fullfile(pathstr, 'temp', [name, '_temp.mat']);
if exist(faceDataName, 'file');
    load(faceDataName);
else 
faceData = cell(200,2); % the total number of faces is not sure
indexofFace = 1;  
for indexofSubject = 1:47
    subjectInfor = faceInfo{indexofSubject};
    numofstruct = length(subjectInfor);
    indexofstruct = 1;
    while(indexofstruct <= numofstruct) 
         structname = getfield(subjectInfor,{indexofstruct}, 'name');
         facename = [faceDataPath, '\', subjectSet(indexofSubject).name, '\', structname];
         face = importdata(facename);
         face = double(face(:,:,8:end-2));
         parfor indexofGabor = 1:num_filters % extract Gabor features 
            convolved = conv3fft( face, filters{indexofGabor}, 'same');
            gaborFace = abs(convolved);
            ngaborFace = normalise(gaborFace, 'percent', 0.999);
            ngaborFace = uint8(ngaborFace*255);
            % extract 3D LDP features 
            [hist] = mex3DLDP(ngaborFace, subImageSize, order);  
            combinedFeature(:,indexofGabor) = hist;
         end    
         faceData{indexofFace,1} = str2double(subjectSet(indexofSubject).name);  
         faceData{indexofFace,2} = reshape(combinedFeature, 1, num_filters*numofBins);  
         indexofstruct = indexofstruct + 1; 
         indexofFace = indexofFace + 1;  
    end
    disp(indexofSubject);
end
faceData = faceData(1:indexofFace - 1,:); % prune the empty cell
save(faceDataName, 'faceData');
end

%% set up gallery and probe datasets and recognition test
facemap = cell2mat(faceData(1:end, 1));
for test = 1:10
    indexofProbe = 1;
    for indexofSubject = 1: 47
        subjectname = subjectSet(indexofSubject).name;
        class = find(facemap == str2double(subjectname));
        if isempty(class)
            continue;
        end
        randomNum = randi(length(class),1,1) ;
        galleryIndex{indexofSubject,1} = class(randomNum);
        class(randomNum) = [];
        if isempty(class)
            continue;
        end
        probeIndex{indexofProbe,1} = class;
        indexofProbe = indexofProbe + 1;
    end
    mgalleryIndex = cell2mat(galleryIndex);
    mprobeIndex = cell2mat(probeIndex);
    galleryData = faceData(mgalleryIndex, :);
    probeData = faceData(mprobeIndex, :);
    numofProbe = length(probeData);
    % classification
    measure = zeros(numofProbe, numofSubject);
    for i = 1:numofProbe % proble
        for j = 1:numofSubject %gallery
            measure(i,j) = HistIntersection(probeData{i,2}', galleryData{j,2}');
        end
    end
    [~,nearestNeighbour] = max(measure,[],2);
    recognition = cell2mat(probeData(:,1)) == cell2mat(galleryData(nearestNeighbour,1));
    index = recognition == 1;
    truePositive = probeData(index,1);
    numofRecognition = sum(recognition);
    r(test) = numofRecognition/numofProbe;
    disp(test);
end
disp(r);
mu = mean(r);
sigma = std(r);
resultsname = fullfile(pathstr, 'results', [name, '.mat']);
save(resultsname, 'r', 'mu', 'sigma');

