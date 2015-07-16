load carbig
X = [MPG,Acceleration,Displacement,Weight,Horsepower];
varNames = {'MPG'; 'Acceleration'; 'Displacement';'Weight'; 'Horsepower'};
figure
gplotmatrix(X,[],Cylinders,['c' 'b' 'm' 'g' 'r'],[],[],false);
text([.08 .24 .43 .66 .83], repmat(-.1,1,5), varNames,'FontSize',8);
text(repmat(-.12,1,5), [.86 .62 .41 .25 .02], varNames,'FontSize',8, 'Rotation',90);

Cyl468 = ismember(Cylinders,[4 6 8]);
parallelcoords(X(Cyl468,:), 'group',Cylinders(Cyl468), 'standardize','on', 'labels',varNames)

parallelcoords(X(Cyl468,:), 'group',Cylinders(Cyl468), 'standardize','on', 'labels',varNames,  'quantile',.25)

models77 = find((Model_Year==77));
dissimilarity = pdist(zscore(X(models77,:)));
Y = mdscale(dissimilarity,2);
glyphplot(X(models77,:), 'glyph','face', 'centers',Y, ...
          'varLabels',varNames, 'obslabels',Model(models77,:));
title('1977 Model Year');
