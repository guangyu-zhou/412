D=readtable('./data/data/iris_data.dat', 'ReadVariableNames',false);
% D= importdata('./data/data/iris2.dat',',');
E=D(1:150,1:4)
E = table2array(E)
[coeff score]= pca(E);
firstBase = score(:,1);
secondBase = score(:,2);
% label
% score_class(:,1)
cell = table2cell(D(:,5))
figure
fig12=gscatter(score(:,1),score(:,2),cell)
figure
fig34=gscatter(score(:,3),score(:,4),cell)


