function [L R obj] = LocalRefinement_GeneralLight_L2_Linear(L, Bases, Data)
maxItr = 20;

temp = max(Data,[],2);
[tempval tempind] = max(temp);

for i = 1:maxItr
    %solve relfectance
    R = Bases*pinv(diag(L)*Bases)*Data;
    
    %clamp values
    R(R<0) = 0; R(R>1) = 1;
    
    %solve L
    L = sum(Data.*R,2)./sum(R.*R,2);
    
    %clamp values
    index = find(L<temp);
    L(index) = temp(index); 
    
    if L(tempind) > tempval
        L(tempind) = tempval;
    end
    
    %the objective value   
    %obj(i) = norm(Data-diag(L)*R,'fro');
end   
obj = norm(Data-diag(L)*R,'fro');
end
