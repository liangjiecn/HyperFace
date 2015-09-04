function in = HistIntersection(H1, H2)
% caluculate the histogram intersection 
% H1, H2 is column vector
in = sum(min([H1,H2],[],2));

