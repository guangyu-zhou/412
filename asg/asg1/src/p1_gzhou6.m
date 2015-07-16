A=importdata('./data/data/data.online.scores','\t');
mid=A(:,2,:);
mids=sort(mid);
min=mids(1)
n=length(mids);
max=mids(n)
Q1=mids(n/4)
Median=mids(n/2)
Q3=mids(n*3/4)
mean=sum(mids)/n

maxMode=0;noModes=1;
for i=1:n
    mode=0;
    for j=i:n
        if mids(i)==mids(j)
            mode=mode+1;
        end
    end
    if mode>maxMode && mode~=0
        maxMode=mode;% 83?
        noModes = 1;
%         Modes=Modes(1);
        Modes(noModes)=mids(i);
    elseif mode==maxMode
        Modes(noModes)=mids(i);
        noModes=noModes+1;
    end
end
noModes
Modes
Modes=Modes(1:noModes)


% cnt = 1, mode=
% for i=1:n
%     if mids(i)~= mids(i+1)
        

sumDiff=0;
for i=1:n
    sumDiff=sumDiff+(mids(i)-mean)*(mids(i)-mean);
end
expVar=sumDiff/(n-1)

            
