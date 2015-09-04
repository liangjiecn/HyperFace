function [g, num] = GenerateFilters_1D( Size, Ratio)
% Size, the filter size
% Ratio: the ratio between frequency and the span of Gaussian

% gama = yita = ratio * sqrt(2)
% sigma = ratio/F0;

if nargin<2
    Btheta = pi/4;
    Ratio =  sqrt(2*log(2))/(2*pi*tan(Btheta/2));
end
Fmax = 1/4;
Fspace = 2;
NumFreqs = 4;
counter = 0;
for i=0:NumFreqs-1
    F = Fmax/(Fspace^i);
    counter = counter + 1;
    %function g = gfcreatefilter_3D( F0, theta, phi, ratio, size )
    g{counter} = gfcreatefilter_1D( F, Size);    
    % if theta =0, the values of Phi doesn't matter
end
num = counter;