#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "adaboost.h"
using namespace std;

int main (int argc, char* argv[]) {

   if(argc!=3)
    {
        cout << "Usage:" << argv[0] << "[ training_file ] [ test_file ]\n" ;
        return 0;
    }

    string line;
    int max_idx = 0;
    int idx_read;
    int value_read;
    long number_lines_train = 0;
    string trainfile(argv[1]);
    string testfile(argv[2]);

    ifstream myfile (trainfile.c_str());
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
            while(line.find(" ")!= line.npos)
            {
                //cout << line.find(":");
                line.erase(0, line.find(" ")+1);
                stringstream stream(line);
                stream >> idx_read;

                if(max_idx < idx_read)
                    max_idx = idx_read;
            }
        }
        //cout << "Max in train file " << max_idx << endl;
        myfile.close();
    }

    else cout << "Unable to open file";


    myfile.open(testfile);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            while(line.find(" ")!= line.npos)
            {
                //cout << line.find(":");
                line.erase(0, line.find(" ")+1);
                stringstream stream(line);
                stream >> idx_read;

                if(max_idx < idx_read)
                    max_idx = idx_read;
            }
        }
        //cout << "Max in test file " << max_idx << endl;
        myfile.close();
    }

    else cout << "Unable to open file";


    vector< vector<int> > train_records;


    myfile.open(trainfile);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<int> row(max_idx+1);
            stringstream stream(line);
            stream >> row[0];
            while(line.find(" ")!= line.npos)
            {
                //cout << line.find(":");
                line.erase(0, line.find(" ")+1);
                stringstream stream1(line);
                stream1 >> idx_read;
                //cout << idx_read << endl;
                line.erase(0, line.find(":")+1);
                stringstream stream2(line);
                stream2 >> value_read;
                //cout << value_read << endl;
                row[idx_read] = value_read;

            }
            /*for(int i = 0; i<row.size(); i++)
                cout << i << ":" << row[i] << endl;*/
            train_records.push_back(row);
        }
        myfile.close();
        //cout << train_records.size() << endl;
    }

    else cout << "Unable to open file";


    vector< vector<int> > test_records;

    myfile.open(testfile);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<int> row(max_idx+1);
            stringstream stream(line);
            stream >> row[0];;
            while(line.find(" ")!= line.npos)
            {
                //cout << line.find(":");
                line.erase(0, line.find(" ")+1);
                stringstream stream1(line);
                stream1 >> idx_read;
                //cout << idx_read << endl;
                line.erase(0, line.find(":")+1);
                stringstream stream2(line);
                stream2 >> value_read;
                //cout << value_read << endl;
                row[idx_read] = value_read;

            }
            test_records.push_back(row);
        }
        myfile.close();
        //cout << test_records.size() << endl;
    }
    else cout << "Unable to open file";



/******************** Read Files above ******************************/



    //naive_bayes(train_records, test_records, max_idx);
    adaboost(train_records, test_records, max_idx);


return 0;
}
