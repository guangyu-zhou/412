#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>


#include "parse.h"
#include "fptree.h"
using namespace std;

bool mycompare (pair<int,int> i, pair<int,int> j) {return (i.second >  j.second);}
bool mycompare2 (pair <vector <int>, int> i, pair <vector <int>, int> j) {return (i.second >  j.second);}
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
    int min_support = 100;

    ifstream fin("topic-0.txt");
    //ifstream fin("FPpractice_test.txt");
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
            C1[vec[i]] = 1;
    }
// done with C1
// L1
    map<int,int> L1 = C1;
    //map<int,int>::iterator it;
    //cout << "C1 size: " << C1.size() << endl;
    for(it = C1.begin(); it != C1.end(); it++)
    {
        if(it->second < min_support)
        {
            L1.erase(it->first);
        }

    }
    //cout << "L1 size: "  << L1.size() << endl;

    vector<pair<int,int> > sorted_L(L1.begin(), L1.end());
    sort(sorted_L.begin(),sorted_L.end(),mycompare);
    //cout << "sorted_L size: "  <<  sorted_L.size() << endl;

/* sort topic based on L1 */
/*** HAVE TO REMOVE SMALL FREC!!!!   ***/
    vector <vector <int> > topic_table;
    ifstream fin2("topic-0.txt");
    //ifstream fin2("FPpractice_test.txt");
    integer = 0;
    while(getline(fin2, curLine))
    {
        vector <int> topic_row;
        stringstream stream(curLine);
        while(stream >> integer){

            if(L1.find(integer)!=L1.end())  // > min_sup
            {
                //cout << "num is " << integer  << "cnt is " << L1[integer] << endl;
                topic_row.push_back(integer);
            }
        }
        if(topic_row.size()!=0)
            topic_table.push_back(topic_row);
    }
    fin2.close();

    for(int rows = 0; rows < topic_table.size(); rows++)
    {
        sort(topic_table[rows].begin(), topic_table[rows].end(), MyComparator(L1));
    }


/*** --------------------  print table -----------------------*/
 /*   cout << "T size is " << topic_table.size() << "\n";
    for(int rows = 0; rows < 10; rows++)
    {
        for(int i = 0; i < topic_table[rows].size(); i++)
            cout << "  no " << topic_table[rows][i] << "  cnt: " << L1[topic_table[rows][i]];
        cout << endl;
    }
    //cout << "out?" << endl;

/***/


/* insert tree (table, root) */
    vector< pair< vector <int> ,int> > freq_patterns_vec;
    map <vector <int>, int>  freq_patterns;
    FP_tree mytree;
    mytree.insert(topic_table, sorted_L, L1, freq_patterns);
    map <vector <int>, int>::iterator iter;
    for(iter = freq_patterns.begin(); iter!= freq_patterns.end(); iter++)
    {
        pair< vector <int> ,int> mypair;
        mypair.first = iter->first;
        mypair.second = iter->second;
        freq_patterns_vec.push_back(mypair);
    }
    sort(freq_patterns_vec.begin(),freq_patterns_vec.end(),mycompare2);
    /*** my own test:
    vector <vector <int> > myowntable;
    vector <int> r1;
    vector <int> r2;
    r1.push_back(4);r1.push_back(3);r1.push_back(2);
    r2.push_back(3);
    myowntable.push_back(r1);myowntable.push_back(r2);
    vector<pair<int,int> > my_L;
    pair<int,int> p1,p2,p3;
    p1.first = 3;p1.second = 2;
    p2.first = 4;p2.second = 1;
    p3.first = 2;p3.second = 1;
    my_L.push_back(p1);
    my_L.push_back(p2);
    my_L.push_back(p3);
    mytree.insert(myowntable, my_L); */




    /*
    for(int rows = 0 ; rows < 10; rows++)
    {
        queue<int> dumpQ;
        for(int i = 0; i < topic_table[rows].size(); i++)
        {
            dumpQ.push(topic_table[rows][i]);
        }

        mytree.insert(dumpQ, mytree.root);
        mytree.printtree(mytree.root);

    }*/


// print out the freq into file

    ofstream fout;
    fout.open ("pattern-0.txt");
    map<int, string> vocab_map = parse();
    for(int i = 0; i < freq_patterns_vec.size(); i++)
    {

        cout << "Support # " << freq_patterns_vec[i].second << "  ";
        cout << "Freq Pattern: ";
        for(int j = 0; j < freq_patterns_vec[i].first.size(); j++)
            cout << vocab_map[freq_patterns_vec[i].first[j]]<<" ";
        cout << endl;
    }
    for(int i = 0; i < freq_patterns_vec.size(); i++)
    {

        fout << freq_patterns_vec[i].second << " ";
        for(int j = 0; j < freq_patterns_vec[i].first.size(); j++)
            fout << vocab_map[freq_patterns_vec[i].first[j]]<<" ";
        fout << endl;
    }
    fout.close();
    //cout << "1584 is " << vocab_map[1584] <<" with count: " << endl;
    return 0;



}

