function reconface = reconpca(faceinfor)
% reconstruct spectral data with foundmantal basises using PCA 
k = 8; % assume the rank is equal to 8, the number of primary conponents 
rawmat = cat(2,faceinfor{:,4});
[coeff, score, ~] = pca(rawmat); 
B = score(:,1:k); % m*k
C = coeff(:,1:k);
matTemp = B*C';
reconmat = bsxfun(@plus, matTemp, mean(rawmat));
% check result
plot([400:0.5:1000],rawmat(:,10), [400:0.5:1000],reconmat(:,10), 'r');
reconface = faceinfor;
for i = 1: length(faceinfor)
    spec = reconmat(:,1+(i-1)*6: i*6);
    reconface{i,4} = spec;
end