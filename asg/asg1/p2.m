[data,varnames,casenames] = tblread('./data/data/data.supermarkets.inventories','\t');
row1=data(1,:);
row2=data(2,:);
sum1=0;
for i=1:100
    sum1=sum1+power(abs(row1(i)-row2(i)),1);
end
dist1=nthroot(sum1,1)

sum2=0;
for i=1:100
    sum2=sum2+power(abs(row1(i)-row2(i)),2);
end
dist2=nthroot(sum2,2)

suminf=0;
for i=1:100
    suminf=suminf+power(abs(row1(i)-row2(i)),inf);
end
distinf=nthroot(sum2,inf)

dotprod=0;sum1=0;sum2=0;
for i=1:100
    dotprod=dotprod+row1(i)*row2(i);
    sum1=sum1+power(row1(i),2);
    sum2=sum2+power(row2(i),2);
end
cos=dotprod/abs(sqrt(sum1)*sqrt(sum2))
