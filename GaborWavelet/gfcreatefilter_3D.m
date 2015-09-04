
% in 2D, alpha, beta,  alpha = beta = 1/(sqrt(2) *sigma)
% f0/alpha = gama, f0/beta = yita  --> ratio = f0*sigma = gama/sqrt(2) = yita/sqrt(2)
%  
function g = gfcreatefilter_3D( F0, theta, phi, ratio, size )

% gama = yita = ratio * sqrt(2)
ratio = 1;
sigma = ratio/F0;

% theta is the angle between F0 and w(z) axis,  
% phi is the angle between projection of F0 in u-v(x-y) plane and the u(x) axis
U0 = F0 * sin(theta) * cos(phi);
V0 = F0 * sin(theta) * sin(phi);
W0 = F0 * cos(theta);



if length(size)>1,
  nx=size(1);
  ny=size(2);
  nz=size(3);
else
  nx=size;
  ny=size;
  nz=size;
end;

if mod(nx,2)>0,
  tx=-((nx-1)/2):(nx-1)/2;
else
  tx=-(nx/2):(nx/2-1);
end;

if mod(ny,2)>0,
  ty=-((ny-1)/2):(ny-1)/2;
else
  ty=-(ny/2):(ny/2-1);
end;

if mod(nz,2)>0
  tz=-((nz-1)/2):(nz-1)/2;
else
  tz=-(nz/2):(nz/2-1);
end;

[X,Y,Z]=meshgrid(tx,ty,tz);

prefix = 1/( ((2*pi).^1.5) * sigma.^3 );
gaussian = prefix * exp(-(X.^2 + Y.^2 + Z.^2)/(2*sigma.^2));
modulate = exp(1i*2*pi*(U0*X + V0*Y + W0*Z));

g = gaussian .* modulate;

%g = g - mean2(real(g));
