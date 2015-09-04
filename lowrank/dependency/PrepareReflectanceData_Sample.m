function [Macbeth MacbethCCDC Munsell] = PrepareReflectanceData_Sample(Lb, Ub, interval)

%load data
load Macbeth_380_730_10

%from 420:700
Macbeth = Macbeth.';
Macbeth = Macbeth(5:end-3,:);

%5 interval by interpolation
Temp = zeros(57,size(Macbeth,2));
for i = 1:size(Macbeth,2)
    Temp(:,i) = interp1([420:10:700],Macbeth(:,i),[420:5:700],'cubic');
end
Macbeth = Temp;

%load data
load MacbethCCDC_380_730_10

%from 420:700
MacbethCCDC = MacbethCCDC(5:end-3,:);

%5 interval by interpolation
Temp = zeros(57,size(Macbeth,2));
for i = 1:size(MacbethCCDC,2)
    Temp(:,i) = interp1([420:10:700],MacbethCCDC(:,i),[420:5:700],'cubic');
end
MacbethCCDC = Temp;

%load data
load munsell380_800_1

%from 420:700
Munsell = munsell(41:321,:);

%5 interval
Munsell = Munsell(1:5:end,:);

end
