#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
using namespace std;

int main () {
    string line;
    int max_idx = 0;
    int idx_read;
    int value_read;
    long number_lines_train = 0;
    string trainfile("./adult.train");
    string testfile("./adult.test");

    ifstream myfile (trainfile);
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
        cout << "Max in train file " << max_idx << endl;
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
        cout << "Max in test file " << max_idx << endl;
        myfile.close();
    }

    else cout << "Unable to open file";


    vector< vector<int> > train_records;


    myfile.open(trainfile);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<int> row(max_idx);
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
            vector<int> row(max_idx);
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





    double P_C0 = 0 , P_C1 = 0;
    int C0 = 0, C1 = 0;
    for(int i = 0; i< train_records.size(); i++)
    {
        if(train_records[i][0] == 1)
            C1++;
        else
            C0++;
    }
    P_C0 = (double)C0/train_records.size();
    P_C1 = (double)C1/train_records.size();
    cout << P_C0 <<" " <<P_C1 << endl;

    vector<double> P_Xi_C0(test_records.size()), P_Xi_C1(test_records.size());
    vector<int> labels;


for(int row = 0; row < test_records.size(); row++)
{
    cout << "In Loop: "<< row << endl;
    double P_C0_X = 1, P_C1_X = 1;
    for(int i = 1; i< max_idx; i++)
    {
        int x_i0 = 0, x_i1 = 0;
        for(int j = 0; j < train_records.size(); j++)
        {
            if(train_records[j][i] == test_records[row][i] && train_records[j][0] == 1)
                x_i1++;
            if(train_records[j][i] == test_records[row][i] && train_records[j][0] == -1)
                x_i0++;
        }
        //cout << " x_i0 " << x_i0 << endl;
        //cout << " x_i1 " << x_i1 << endl;
        P_C0_X*=(double)x_i0/C0;
        P_C1_X*=(double)x_i1/C1;

    }
    P_C0_X*=P_C0;
    P_C1_X*=P_C1;
    //cout << P_C0_X << " *** " << P_C1_X << endl;
    labels.push_back(P_C0_X>P_C1_X ? -1:1);
}
for(int row = 0; row < labels.size(); row++)
{
    cout << "labels: " << labels[row] << endl;
}

  return 0;
}
