C=importdata('./data/data/data.online.scores','\t');
mids=C(:,2,:);
n=length(mids);
mean=sum(mids)/n

sumDiff=0;
for i=1:n
    sumDiff=sumDiff+(mids(i)-mean)*(mids(i)-mean);
end
expVar=sumDiff/(n-1)
expStd=sqrt(expVar)

% Normalization:
midsN =mids;
for i=1:n
    midsN(i)= (mids(i)-mean)/expStd;
end
meanN=sum(midsN)/n
sumDiff=0;
for i=1:n
    sumDiff=sumDiff+(midsN(i)-meanN)*(midsN(i)-meanN);
end
expVarN=sumDiff/(n-1)
score=90;
scoreN= (score-mean)/expStd


            
