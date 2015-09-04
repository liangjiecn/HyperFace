%%extract spatial spectral feature from hyperspectral data using 3D garbor
%%wavelet
function feature = GarborWavelet_3D( datacube, sizeofFilter)

numofPixel = numel(datacube);
feature = zeros(num_filters, numofPixel);
for i=1:num_filters  
    convolved = conv3fft( datacube, filters{i}, 'same');
    mags = abs(convolved);
    vector = reshape(mags, 1,numofPixel);
    feature(i,:) = vector; 
end
