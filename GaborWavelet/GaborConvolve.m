


function [Gabor_mags Gabor_phases Gabor_coses] = GaborConvolve( data, filters, num_filters)


for i=1:num_filters
    
    if (num_filters>1)
        g = filters{i};    
    else
        g = filters;
    end
    
    Gabor_Convolved = conv3fft( data, g, 'same' );
    
    Gabor_mags{i} = abs(Gabor_Convolved);
    Gabor_phases{i} = angle(Gabor_Convolved);
    Gabor_coses{i} = real(Gabor_Convolved);
end