% D=readtable('./data/data/iris_data.dat', 'ReadVariableNames',false);
D= importdata('./data/data/iris2.dat',',');
E=D(1:150,1:4)
coeff= princomp(E)
% label
% score_class(:,1)
% figure
cell = D(:,5);
coeff_need= coeff(:,1:2);
Et=transpose(E);
Yt=transpose(coeff_need)*Et;
Y=transpose(Yt)
fig12=gscatter(Yt(1,:),Yt(2,:),cell)
% figure
% fig34=gscatter(coeff(:,3),coeff(:,4),cell)
% T= [-1,0,1;1,0,-1]
% coeff= princomp(T)