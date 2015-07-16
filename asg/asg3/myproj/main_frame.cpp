#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

bool mycompare (pair<int,int> i, pair<int,int> j) {return (i.second >  j.second);}

int main(){
    vector<int> vec;

    ifstream fin("topic-0.txt");
    int integer = 0;
    string curLine;
    while(getline(fin, curLine))
    {
        stringstream stream(curLine);
        while(stream >> integer)
            vec.push_back(integer);

    }
    fin.close();

    map<int,int> C1;
    map<int,int>::iterator it;
    for(int i = 0; i < vec.size(); i++)
    {
        it = C1.find(vec[i]);
        if(it!=C1.end()) // find!
            it->second++;
        else
            C1[vec[i]] = 0;
    }

    vector<pair<int,int> > dumpVec(C1.begin(), C1.end());
    sort(dumpVec.begin(),dumpVec.end(),mycompare);

    /*for (it=C1.begin(); it!=C1.end(); ++it)
        if(it->second!=0)
            std::cout << it->first << " => " << it->second << '\n';*/
    for(int i = 0; i < dumpVec.size(); i++)
    {
        if(dumpVec[i].second > 10)
            cout << dumpVec[i].first <<" " <<dumpVec[i].second << endl;

    }

    ofstream fout;
    fout.open ("example.txt");
    for(int i = 0; i < dumpVec.size(); i++)
    {
        //if(dumpVec[i].second > 10)
            fout << dumpVec[i].first <<" " <<dumpVec[i].second << endl;

    }
    fout.close();
    return 0;



}

