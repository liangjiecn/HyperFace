function [probeset, galleryset] = buildGalleryProbe(faceinfor)
% build gallery and probe data
faceinfor = sortrows(faceinfor, 1);
[subject,ia,ic] = unique(faceinfor(:,1));
facesubject = cell(length(subject),1);
probeset = [];
galleryset = [];
for i = 1: length(facesubject)
    index = find(ic == i);
    facesubject{i} = faceinfor(index,:);
    facesession = facesubject{i};
    [session,ia,ics] = unique(facesession(:,2));
    % if there is only one session, skip this subject. Otherwise,
    % there is will be no corresponding gallery data
    if length(session) == 1 
        continue;
    end
    randonnum = randi(length(session),1);
    indexproble = find(ics==randonnum);
    indexgallery = find(ics~=randonnum);
    probe = facesession(indexproble,:);
    probeset = cat(1, probeset, probe);
    gallery = facesession(indexgallery,:);
    galleryset = cat(1, galleryset, gallery);
end
