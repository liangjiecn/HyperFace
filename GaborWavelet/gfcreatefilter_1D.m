
% in 2D, alpha, beta,  alpha = beta = 1/(sqrt(2) *sigma)
% f0/alpha = gama, f0/beta = yita  --> ratio = f0*sigma = gama/sqrt(2) = yita/sqrt(2)
%  
function g = gfcreatefilter_1D( F0, size )

% gama = yita = ratio * sqrt(2)
ratio = 1;
sigma = ratio/F0;

% theta is the angle between F0 and w(z) axis,  
% phi is the angle between projection of F0 in u-v(x-y) plane and the u(x) axis
U0 = F0;
nx=size;
if mod(nx,2)>0,
  tx=-((nx-1)/2):(nx-1)/2;
else
  tx=-(nx/2):(nx/2-1);
end;

[X]=ndgrid(tx);

prefix = 1/( ((2*pi).^0.5) * sigma.^1 );% not sure if this is right or not?
gaussian = prefix * exp(-(X.^2)/(2*sigma.^2));
modulate = exp(1i*2*pi*(U0*X));
g = gaussian .* modulate;

%g = g - mean2(real(g));
