

function [out] = conv3fft(z1,z2,shape)

z1x=size(z1,1);
z1y=size(z1,2);
z1z=size(z1,3);
        
z2x=size(z2,1);
z2y=size(z2,2);
z2z=size(z2,3);

if ((nargin==3)&&(isa(shape,'char'))) 
    z1_f = fftn(z1,[z1x+z2x-1 z1y+z2y-1 z1z+z2z-1]);
    z2_f = fftn(z2,[z1x+z2x-1 z1y+z2y-1 z1z+z2z-1]);
    
    if strcmp(shape,'same')
       
        if any(any(any(imag(z1))))||any(any(any(imag(z2))))
            out = ifftn(z1_f .* z2_f);
        else
            out = real(ifftn(z1_f .* z2_f));
        end
        
        
        px=((z2x-1)+mod((z2x-1),2))/2;
        py=((z2y-1)+mod((z2y-1),2))/2;
        pz=((z2z-1)+mod((z2z-1),2))/2;
        
        out=out(px+1:px+z1x,py+1:py+z1y, pz+1:pz+z1z);
        return;
    end
    
    if strcmp(shape,'full')
        
        if any(any(any(imag(z1))))||any(any(any(imag(z2))))
            out = ifftn(z1_f .* z2_f);
        else
            out = real(ifftn(z1_f .* z2_f));
        end
        
        return;
    end
    
    if strcmp(shape,'valid')

        if ((z1x<z2x)||(z1y<z2y)||(z1z<z2z))
            out=[];
            return;
        else
        end
        if any(any(any(imag(z1))))||any(any(any(imag(z2))))
            out = ifftn(z1_f .* z2_f);
        else
            out = real(ifftn(z1_f .* z2_f));
        end
        
        px=z2x;
        py=z2y;
        pz=z2z;
        
        out=out(px:px+z1x-z2x,py:py+z1y-z2y,pz:pz+z1z-z2z);
        return;
    end
end

clear('z1_f','z2_f');