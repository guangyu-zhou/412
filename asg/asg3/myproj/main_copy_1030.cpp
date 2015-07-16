#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <queue>

#include "parse.h"
#include "fptree.h"
using namespace std;

bool mycompare (pair<int,int> i, pair<int,int> j) {return (i.second >  j.second);}

struct MyComparator
{
    map<int, int> & mymap;

    MyComparator(map<int, int> & map_val): // copy constructor
        mymap(map_val) {}

    bool operator()(int i1, int i2)
    {
        return mymap[i1] > mymap[i2];
    }
};



int main(){
    vector<int> vec;
    int min_support = 10;

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
// done with C1
// L1
    map<int,int> L1 = C1;
    //map<int,int>::iterator it;
    cout << "C1 size: " << C1.size() << endl;
    for(it = L1.begin(); it != L1.end(); it++)
    {
        if(it->second < min_support)
            L1.erase(it);
    }
    cout << "L1 size: "  << L1.size() << endl;

    vector<pair<int,int> > dumpVec(L1.begin(), L1.end());
    sort(dumpVec.begin(),dumpVec.end(),mycompare);

/* check sorting L1
    for(int i = 0; i < dumpVec.size(); i++)
    {
        if(dumpVec[i].second > min_support)
            cout << dumpVec[i].first <<" with count: " <<dumpVec[i].second << endl;

    } */




/* sort topic based on L1 */
    vector <vector <int> > topic_table;
    ifstream fin2("topic-0.txt");
    integer = 0;
    while(getline(fin2, curLine))
    {
        vector <int> topic_row;
        stringstream stream(curLine);
        while(stream >> integer)
            topic_row.push_back(integer);
        topic_table.push_back(topic_row);
    }
    fin2.close();

    for(int rows = 0; rows < topic_table.size(); rows++)
    {
        sort(topic_table[rows].begin(), topic_table[rows].end(), MyComparator(L1));
    }


/* --------------------  print table -----------------------
    for(int rows = 0; rows < 10; rows++)
        for(int i = 0; i < topic_table[rows].size(); i++)
            cout << "table " << topic_table[rows][i] << "  cnt: " << L1[topic_table[rows][i]]<< endl;
*/

/* insert tree (table, root) */
    FP_tree mytree;
    // cout <<"root id is " << mytree.root->Node_id << endl;
 /*   for(int rows = 0 ; rows < 10; rows++)
    {
        queue<int> dumpQ;
        for(int i = 0; i < topic_table[rows].size(); i++)
        {
            dumpQ.push(topic_table[rows][i]);
        }

        mytree.insert(dumpQ, mytree.root);
        mytree.printtree(mytree.root);

    }
*/
/*simple tb
    int a[2][4] = {{4,3,2,1}, {4,3,2,0}};
    for(int rows = 0 ; rows < 2; rows++)
    {
        queue<int> dumpQ;
        for(int i = 0; i < 4; i++)
        {
            dumpQ.push(a[rows][i]);
        }

        mytree.insert(dumpQ, mytree.root);
        //mytree.printtree(mytree.root);
        cout << "freq is " << mytree.root->children[0]->freq_cnt << "\n";
    } */







// print out the freq into file
    map<int, string> vocab_map = parse();
    ofstream fout;
    fout.open ("example2.txt");
    for(int i = 0; i < dumpVec.size(); i++)
    {
        if(dumpVec[i].second > min_support)
            fout << vocab_map[dumpVec[i].first] <<" with count: " <<dumpVec[i].second << endl;
            //fout << dumpVec[i].first <<" with count: " <<dumpVec[i].second << endl;

    }
    fout.close();
    //cout << "1584 is " << vocab_map[1584] <<" with count: " << endl;
    return 0;



}

