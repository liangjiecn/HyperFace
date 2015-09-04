

function [out] = conv1fft(z1,z2,shape)
z1x=size(z1,1);       
z2x=size(z2,1);
if ((nargin==3)&&(isa(shape,'char'))) 
    z1_f = fft(z1,[z1x+z2x-1]);
    z2_f = fft(z2,[z1x+z2x-1]);
    if strcmp(shape,'same')
       
        if any(any(any(imag(z1))))||any(any(any(imag(z2))))
            out = ifftn(z1_f .* z2_f);
        else
            out = real(ifftn(z1_f .* z2_f));
        end       
        px=((z2x-1)+mod((z2x-1),2))/2;    
        out=out(px+1:px+z1x);
        return;
    end 
end

clear('z1_f','z2_f');