#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int main (int argc, char* argv[]) {

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
    vector<int> labels0, labels;

/********************  training here    **************************/

map < pair <int, int>, double>  traning_map_C0; // key is index:vallue, value is prob
map < pair <int, int>, double>  traning_map_C1;

for(int row = 0; row < train_records.size(); row++)
{
    //cout << "In Loop: "<< row << endl;

    for(int i = 1; i<= max_idx; i++)
    {
        double P_C0_X = 1, P_C1_X = 1;
        int x1=0, x0=0;
        pair<int, int> mypair = make_pair(i, train_records[row][i]);
        //cout << i <<  " ++ " << train_records[row][i] << " " ;
        if(traning_map_C0.find(mypair)!=traning_map_C0.end())
        {
            continue;
        }
        //cout << "New pair is " << mypair.first << " " << mypair.second << endl;

        for(int j = 0; j < train_records.size(); j++)
        {
            if(train_records[j][i] == train_records[row][i] && train_records[j][0] == 1)
                x1++;
            else if(train_records[j][i] == train_records[row][i] && train_records[j][0] == -1)
                x0++;
        }
        if(x0==0) x0=1;
        if(x1==0) x1=1;
        P_C0_X =(double)x0/C0;
        P_C1_X =(double)x1/C1;
        //cout << x0 << " " << x1 << endl;
        traning_map_C0[mypair] = P_C0_X;
        traning_map_C1[mypair] = P_C1_X;
        if(traning_map_C1[mypair] == 0)
            cout << "BAD 0 VALUE" << endl;
        if(traning_map_C0[mypair] == 0)
            cout << "BAD 0 VALUE" << endl;

    }
    //cout << traning_map_C0.size() << endl;
}



/********************  testing the training set here    **************************/
for(int row = 0; row < train_records.size(); row++)
{
    //cout << "In Loop: "<< row << endl;
    double P_C0_X = 1, P_C1_X = 1;
    for(int i = 1; i<= max_idx; i++)
    {
        pair<int, int> mypair = make_pair(i, train_records[row][i]);
        if(traning_map_C0.find(mypair) == traning_map_C0.end())
        {
            continue;
        }

        //if(P_C0_X == 0)
            //cout << "BAD 0 VALUE" << endl;
        //if(P_C1_X == 0)
            //cout << "BAD 0 VALUE" << endl;
        P_C0_X*=traning_map_C0[mypair];
        P_C1_X*=traning_map_C1[mypair];
        //cout <<"idx " << i << "val " << test_records[row][i] << endl;
        //cout << P_C0_X << " *** " << P_C1_X << endl;

    }
    //cout << P_C0_X << " *** " << P_C1_X << endl;
    P_C0_X*=P_C0;
    P_C1_X*=P_C1;
    //cout << P_C0_X << " *** " << P_C1_X << endl;
    labels0.push_back(P_C0_X>P_C1_X ? -1:1);

}

int TP0 = 0, FP0 = 0, TN0 = 0, FN0 = 0;
for(int row = 0; row < labels0.size(); row++)
{
    if(train_records[row][0] == 1 && labels0[row] == 1)
        TP0++;
    else if(train_records[row][0] == -1 && labels0[row] == -1)
        TN0++;
    else if(train_records[row][0] == -1 && labels0[row] == 1)
        FP0++;
    else if(train_records[row][0] == 1 && labels0[row] == -1)
        FN0++;

}
/*
cout << "Correct labels: " << true_pos << endl;
cout << "Total labels: " << labels.size() << endl;
cout << "Correct ratio: " << (double)true_pos/labels.size() << endl;*/
cout << "Confusion Matrix for training: "<< endl;
cout << "true positive, false negative, false positive, true negative" << endl;
cout << TP0 << " " <<FN0 << " " << FP0 << " " << TN0 << endl;
cout << "Accuracy ratio: " << (double)(TP0+TN0)/labels0.size() << endl;




/********************  testing the test set here    **************************/

for(int row = 0; row < test_records.size(); row++)
{
    //cout << "In Loop: "<< row << endl;
    double P_C0_X = 1, P_C1_X = 1;
    for(int i = 1; i<= max_idx; i++)
    {
        pair<int, int> mypair = make_pair(i, test_records[row][i]);
        if(traning_map_C0.find(mypair) == traning_map_C0.end())
        {
            continue;
        }

        //if(P_C0_X == 0)
            //cout << "BAD 0 VALUE" << endl;
        //if(P_C1_X == 0)
            //cout << "BAD 0 VALUE" << endl;
        P_C0_X*=traning_map_C0[mypair];
        P_C1_X*=traning_map_C1[mypair];
        //cout <<"idx " << i << "val " << test_records[row][i] << endl;
        //cout << P_C0_X << " *** " << P_C1_X << endl;

    }
    //cout << P_C0_X << " *** " << P_C1_X << endl;
    P_C0_X*=P_C0;
    P_C1_X*=P_C1;
    //cout << P_C0_X << " *** " << P_C1_X << endl;
    labels.push_back(P_C0_X>P_C1_X ? -1:1);

}

/********************  Confusion Matrix *********************/
int TP = 0, FP = 0, TN = 0, FN = 0;
for(int row = 0; row < labels.size(); row++)
{
    if(test_records[row][0] == 1 && labels[row] == 1)
        TP++;
    else if(test_records[row][0] == -1 && labels[row] == -1)
        TN++;
    else if(test_records[row][0] == -1 && labels[row] == 1)
        FP++;
    else if(test_records[row][0] == 1 && labels[row] == -1)
        FN++;

}
/*
cout << "Correct labels: " << true_pos << endl;
cout << "Total labels: " << labels.size() << endl;
cout << "Correct ratio: " << (double)true_pos/labels.size() << endl;*/
cout << endl;
cout << "Confusion Matrix for testing: "<< endl;
cout << "true positive, false negative, false positive, true negative" << endl;
cout << TP << " " <<FN << " " << FP << " " << TN << endl;
cout << "Accuracy ratio: " << (double)(TP+TN)/labels.size() << endl;

return 0;
}
