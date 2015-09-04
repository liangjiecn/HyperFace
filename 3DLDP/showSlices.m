function showSlices(file)
close all,
if ischar(file)
    datacube = importdata(filename);
else
    datacube = file;
end
[m, n, b] = size(datacube);
co = 1;
for b = 5:5:b
    slice = squeeze(datacube(:,:,b));
    figure(co),
    colormap(gray);
    imagesc(slice);
    title(num2str(400+b*10));
    axis off;
    axis equal;
    co = co+1;
end