#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>


#include "parse.h"
#include "fptree.h"
using namespace std;

template <typename T>
void print_vec(vector<T> vec)
{
    for(int i = 0; i < vec.size(); i ++)
        cout << vec[i] << " ";
    cout << endl;
}

bool mycomp (pair<double, vector <string> > i, pair<double, vector <string> > j) {return (i.first >  j.first);}

vector< pair<int, vector <string> > > read_file(string filename)
{
    ifstream fin(filename);
    int integer = 0;
    string cur_string;
    vector< pair<int, vector <string> > > pattern_dict;
    string curLine;
    while(getline(fin, curLine))
    {
        stringstream sstream(curLine);
        vector <string> fp_vec;
        if(sstream >> integer)
        {
            while(sstream >> cur_string)
                fp_vec.push_back(cur_string);
        }
        pattern_dict.push_back(make_pair(integer, fp_vec));

    }
    return pattern_dict;
    fin.close();

}

void write_file( vector< pair<double, vector <string> > >  purity, string filename)
{
    ofstream fout;
    fout.open (filename);

    sort(purity.begin(), purity.end(), mycomp);
    for(int j= 0; j < purity.size(); j++)
    {
        fout << purity[j].first << " " ;
        for(int k = 0; k < purity[j].second.size(); k ++)
            fout << purity[j].second[k] << " ";
        fout << endl;
    }
    fout << endl;


    fout.close();
}

double find_max(vector<double> values)
{
    double curmax = values[0];
    for(int i = 0; i< values.size();i++)
    {
        if(curmax < values[i])
            curmax = values[i];
    }
    return curmax;
}

int f(int topic , vector<string> & pattern);

vector < vector< pair<int, vector <string> > >  > pattern_dict_topics;

int main(){


    string str1 = "pattern-0.txt";
    pattern_dict_topics.push_back(read_file(str1));
    str1 = "pattern-1.txt";
    pattern_dict_topics.push_back(read_file(str1));
    str1 = "pattern-2.txt";
    pattern_dict_topics.push_back(read_file(str1));
    str1 = "pattern-3.txt";
    pattern_dict_topics.push_back(read_file(str1));
    str1 = "pattern-4.txt";
    pattern_dict_topics.push_back(read_file(str1));

/* test print
    for(int i = 0; i < pattern_dict_topics.size(); i++)
    {
        for(int j= 0; j < pattern_dict_topics[i].size(); j++)
        {
            cout << "# " << pattern_dict_topics[i][j].first << " Pattern ";
            print_vec(pattern_dict_topics[i][j].second);

        }
        cout << endl;
    }
    */

// find topic 0 purity

//f(p, 0);
//double purity =
    //log( f(t,p)/abs(D(t)));
int D[5][5];
D[0][0] = 10047;
D[0][1] = 17326;
D[0][2] = 17988;
D[0][3] = 17999;
D[0][4] = 17820;


D[1][1] = 9674;
D[1][2] = 17446;
D[1][3] = 17902;
D[1][4] = 17486;

D[2][2] = 9959;
D[2][3] = 18077;
D[2][4] = 17492;

D[3][3] = 10161;
D[3][4] = 17912;

D[4][4] = 9845;

vector < vector< pair<double, vector <string> > >  > pattern_purity;

    for(int topic = 0; topic < pattern_dict_topics.size(); topic++)
    {
        vector< pair<double, vector <string> > > cur_purity;
        for(int j= 0; j < pattern_dict_topics[topic].size(); j++)
        {
            vector<string> p = pattern_dict_topics[topic][j].second;
            double purity;
            purity = log((double)f(topic,  p) / (double)abs(D[topic][topic]));
            //purity = f(topic,  p);
            //cout << "abs is " << abs(D[topic][topic]);


            vector<double> values;

            for(int t = 0; t < pattern_dict_topics.size(); t++)
            {
                if(t != topic)
                {
                    double val = 0;
                    val = (double)(f(topic, p) + f(t, p))/abs(D[min(t,topic)][max(t,topic)]);
                    //val = (double)(f(topic, p) + f(t, p));
                    values.push_back(val);

                }

            }
            purity-= log((double)find_max(values));
            //if(purity>0)
            cur_purity.push_back(make_pair(purity, pattern_dict_topics[topic][j].second));
            // cout << "purity is " << purity << endl;
            //print_vec(p);
        }
        pattern_purity.push_back(cur_purity);
        //cout << endl;
    }
    write_file(pattern_purity[0], "purity-0.txt");
    write_file(pattern_purity[1], "purity-1.txt");
    write_file(pattern_purity[2], "purity-2.txt");
    write_file(pattern_purity[3], "purity-3.txt");
    write_file(pattern_purity[4], "purity-4.txt");

}
int f(int topic, vector<string> & pattern)
{
    int freq = 0;
    for(int i = 0; i < pattern_dict_topics[topic].size(); i++)
    {
        if(pattern == pattern_dict_topics[topic][i].second)
            freq += pattern_dict_topics[topic][i].first;

    }
    //cout << "Freq is " << freq;
    return freq;

}

