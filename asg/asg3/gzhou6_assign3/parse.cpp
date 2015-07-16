#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "parse.h"

using namespace std;
map<int, string> parse()
{
    map<int, string> mymap;
    ifstream fin("vocab.txt");
    int integer = 0;
    string curLine;
    while(getline(fin, curLine))
    {
        stringstream stream(curLine);
        string delimiter = "\t";
        size_t pos = 0;
        int id = 0;
        string token;
        if((pos = curLine.find(delimiter)) != string::npos) {
            stream >> id;
            token = curLine.substr(pos + delimiter.size());
            //cout << id << " " <<token << endl;
            mymap[id] = token;
        }
    }
    fin.close();
    return mymap;


}
