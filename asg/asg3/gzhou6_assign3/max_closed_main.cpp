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

bool check_closed(vector <int> itemset_Y, vector <int> itemset_X, map <vector <int>, int> & fp_dict)
{
    if(includes(itemset_Y.begin(), itemset_Y.end(), itemset_X.begin(), itemset_X.end())) // Y is super, X is sub
    {

        /*
        cout << "superset: " << endl;
        for(auto & i : itemset_Y )
        {
            cout<< i << " ";
            i++;
        }
        cout << "sub set: " << endl;
        for(auto & i : itemset_X )
        {
            cout<< i << " ";
            i++;
        }
        cout << endl;
        */
        if(fp_dict[itemset_X] = fp_dict[itemset_Y])
        {
            cout << "Y superset: " << endl;
            for(auto & i : itemset_Y )
            {
                cout<< i << " ";
                i++;
            }
            cout << "Y support: " << fp_dict[itemset_Y] << endl;
            cout << "sub set: " << endl;
            for(auto & i : itemset_X )
            {
                cout<< i << " ";
                i++;
            }
            cout << "X support: " << fp_dict[itemset_X] << endl;
            cout << endl;
            return false;
        }

    }
    return true;

}



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

    map<int, string> vocab_map = parse();
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

    /*** closed ***/
    vector< pair< vector <int> ,int> > closed_freq_patterns_vec;
    for(int i = 0; i < freq_patterns_vec.size(); i++)
    {
        //sort((freq_patterns_vec[i].first).begin(),(freq_patterns_vec[i].first).end());
        vector <int> itemset_X = freq_patterns_vec[i].first;
        bool flag = 0;
        //cout << "----" << freq_patterns[freq_patterns_vec[i].first] << endl;
        for(int j = i+1; j < freq_patterns_vec.size(); j++)
        {
            vector <int> itemset_Y = freq_patterns_vec[j].first;
            //cout << "----X----" << freq_patterns[freq_patterns_vec[i].first] << endl;
            //cout << "----Y----" << freq_patterns[freq_patterns_vec[j].first] << endl;
            //if(check_closed(itemset_Y, itemset_X, freq_patterns));

            if(includes(itemset_Y.begin(), itemset_Y.end(), itemset_X.begin(), itemset_X.end())) // Y is super, X is sub
            {
                //cout << "----X in----" << freq_patterns[freq_patterns_vec[i].first] << endl;
                //cout << "----Y in----" << freq_patterns[freq_patterns_vec[j].first] << endl;
                /***
                cout << "Y superset: " << endl;
                for(auto & i : itemset_Y )
                {
                    cout<< i << " ";
                    i++;
                }
                cout << "Y support: " << freq_patterns[freq_patterns_vec[j].first] << endl;
                cout << "sub set: " << endl;
                for(auto & i : itemset_X )
                {
                    cout<< i << " ";
                    i++;
                }
                cout << "X support: " << freq_patterns[freq_patterns_vec[i].first] << endl;
                cout << endl; ***/
                if(freq_patterns[freq_patterns_vec[j].first] == freq_patterns[freq_patterns_vec[i].first])
                {
                    flag = 1;
                    break;
                }

            }
        }
        if(!flag)
        {
            closed_freq_patterns_vec.push_back(make_pair(freq_patterns_vec[i].first, freq_patterns_vec[i].second));
        }
            //cout << vocab_map[freq_patterns_vec[i].first[j]]<<" ";
        //cout << endl;
    }

    /*** max ***/
    vector< pair< vector <int> ,int> > max_freq_patterns_vec;
    for(int i = 0; i < freq_patterns_vec.size(); i++)
    {
        //sort((freq_patterns_vec[i].first).begin(),(freq_patterns_vec[i].first).end());
        vector <int> itemset_X = freq_patterns_vec[i].first;
        bool flag = 0;
        //cout << "----" << freq_patterns[freq_patterns_vec[i].first] << endl;
        for(int j = i+1; j < freq_patterns_vec.size(); j++)
        {
            vector <int> itemset_Y = freq_patterns_vec[j].first;
            //cout << "----X----" << freq_patterns[freq_patterns_vec[i].first] << endl;
            //cout << "----Y----" << freq_patterns[freq_patterns_vec[j].first] << endl;
            //if(check_closed(itemset_Y, itemset_X, freq_patterns));

            if(includes(itemset_Y.begin(), itemset_Y.end(), itemset_X.begin(), itemset_X.end())) // Y is super, X is sub
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            max_freq_patterns_vec.push_back(make_pair(freq_patterns_vec[i].first, freq_patterns_vec[i].second));
        }
            //cout << vocab_map[freq_patterns_vec[i].first[j]]<<" ";
        //cout << endl;
    }


// print out the freq into file

    ofstream fout1, fout2;
    fout1.open ("closed-0.txt");
    fout2.open("max-0.txt");

    for(int i = 0; i < closed_freq_patterns_vec.size(); i++)
    {

        fout1 << closed_freq_patterns_vec[i].second << " ";
        for(int j = 0; j < closed_freq_patterns_vec[i].first.size(); j++)
            fout1 << vocab_map[closed_freq_patterns_vec[i].first[j]]<<" ";
        fout1 << endl;
    }
    fout1.close();

    for(int i = 0; i < max_freq_patterns_vec.size(); i++)
    {

        fout2 << max_freq_patterns_vec[i].second << " ";
        for(int j = 0; j < max_freq_patterns_vec[i].first.size(); j++)
            fout2 << vocab_map[max_freq_patterns_vec[i].first[j]]<<" ";
        fout2 << endl;
    }
    fout2.close();
    //cout << "1584 is " << vocab_map[1584] <<" with count: " << endl;
    return 0;



}

