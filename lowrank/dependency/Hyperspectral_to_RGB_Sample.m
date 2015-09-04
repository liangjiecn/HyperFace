function Hyperspectral_to_RGB_Sample(Im,ind,titlename)
%
if nargin < 2
    ind = 1;
end

load CSS_RPI.mat
if size(Im,3) == 57
    CSS(:,1) = interp1([400:10:720],rgbCMF{1}(:,ind),[420:5:700]);
    CSS(:,2) = interp1([400:10:720],rgbCMF{2}(:,ind),[420:5:700]);
    CSS(:,3) = interp1([400:10:720],rgbCMF{3}(:,ind),[420:5:700]);
elseif  size(Im,3) == 29
    CSS(:,1) = interp1([400:10:720],rgbCMF{1}(:,ind),[420:10:700]);
    CSS(:,2) = interp1([400:10:720],rgbCMF{2}(:,ind),[420:10:700]);
    CSS(:,3) = interp1([400:10:720],rgbCMF{3}(:,ind),[420:10:700]);
elseif  size(Im,3) == 26
    CSS(:,1) = interp1([400:10:720],rgbCMF{1}(:,ind),[450:10:700]);
    CSS(:,2) = interp1([400:10:720],rgbCMF{2}(:,ind),[450:10:700]);
    CSS(:,3) = interp1([400:10:720],rgbCMF{3}(:,ind),[450:10:700]);   
end

%white balance
CSS(:,1) =  CSS(:,1)/max(CSS(:,1)); 
CSS(:,2) =  CSS(:,2)/max(CSS(:,2));
CSS(:,3) =  CSS(:,3)/max(CSS(:,3));

[row col band] = size(Im);
TempR = zeros(size(Im));
for i = 1:row
    for j = 1:col
        TempR(i,j,:) = CSS(:,1);
    end
end

TempG = zeros(size(Im));
for i = 1:row
    for j = 1:col
        TempG(i,j,:) = CSS(:,2);
    end
end

TempB = zeros(size(Im));
for i = 1:row
    for j = 1:col
        TempB(i,j,:) = CSS(:,3);
    end
end

RGB = zeros(row,col,3);
RGB(:,:,1) = sum(Im.*TempR,3);
RGB(:,:,2) = sum(Im.*TempG,3);
RGB(:,:,3) = sum(Im.*TempB,3);

%absolute scale
maxval = max(RGB(:));
RGB(:,:,1) = RGB(:,:,1)/maxval;
RGB(:,:,2) = RGB(:,:,2)/maxval;
RGB(:,:,3) = RGB(:,:,3)/maxval;

figure; imshow(RGB); title(titlename);
axis equal;
end