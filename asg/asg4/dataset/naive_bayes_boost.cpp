#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
void naive_bayes_boost(vector<vector <int> > & samples, vector<vector <int> > & train_records, vector<vector <int> > & test_records,int max_idx, vector<int> &labels_train, vector<int> &labels_test)
{
    map < pair <int, int>, double>  traning_map_C0; // key is index:vallue, value is prob
    map < pair <int, int>, double>  traning_map_C1;



    double P_C0 = 0 , P_C1 = 0;
    int C0 = 0, C1 = 0;
    for(int i = 0; i< samples.size(); i++)
    {
        if(samples[i][0] == 1)
            C1++;
        else
            C0++;
    }
    P_C0 = (double)C0/samples.size();
    P_C1 = (double)C1/samples.size();
    //cout << P_C0 <<" " <<P_C1 << endl;



/********************  training here    **************************/
    for(int row = 0; row < samples.size(); row++)
    {
        //cout << "In Loop: "<< row << endl;

        for(int i = 1; i<= max_idx; i++)
        {
            double P_C0_X = 1, P_C1_X = 1;
            int x1=0, x0=0;
            pair<int, int> mypair = make_pair(i, samples[row][i]);
            //cout << i <<  " ++ " << samples[row][i] << " " ;
            if(traning_map_C0.find(mypair)!=traning_map_C0.end())
            {
                continue;
            }
            //cout << "New pair is " << mypair.first << " " << mypair.second << endl;

            for(int j = 0; j < samples.size(); j++)
            {
                if(samples[j][i] == samples[row][i] && samples[j][0] == 1)
                    x1++;
                else if(samples[j][i] == samples[row][i] && samples[j][0] == -1)
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
            P_C0_X*=traning_map_C0[mypair];
            P_C1_X*=traning_map_C1[mypair];

        }
        //cout << P_C0_X << " *** " << P_C1_X << endl;
        P_C0_X*=P_C0;
        P_C1_X*=P_C1;
        //cout << P_C0_X << " *** " << P_C1_X << endl;
        labels_train.push_back(P_C0_X>P_C1_X ? -1:1);

    }

    int TP0 = 0, FP0 = 0, TN0 = 0, FN0 = 0;
    for(int row = 0; row < labels_train.size(); row++)
    {
        if(train_records[row][0] == 1 && labels_train[row] == 1)
            TP0++;
        else if(train_records[row][0] == -1 && labels_train[row] == -1)
            TN0++;
        else if(train_records[row][0] == -1 && labels_train[row] == 1)
            FP0++;
        else if(train_records[row][0] == 1 && labels_train[row] == -1)
            FN0++;

    }
    /*
    cout << "Confusion Matrix for training: "<< endl;
    cout << "true positive, false negative, false positive, true negative" << endl;
    cout << TP0 << " " <<FN0 << " " << FP0 << " " << TN0 << endl;
    cout << "Accuracy ratio: " << (double)(TP0+TN0)/labels_train.size() << endl;*/



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

            P_C0_X*=traning_map_C0[mypair];
            P_C1_X*=traning_map_C1[mypair];
            //cout <<"idx " << i << "val " << test_records[row][i] << endl;
            //cout << P_C0_X << " *** " << P_C1_X << endl;

        }
        //cout << P_C0_X << " *** " << P_C1_X << endl;
        P_C0_X*=P_C0;
        P_C1_X*=P_C1;
        //cout << P_C0_X << " *** " << P_C1_X << endl;
        labels_test.push_back(P_C0_X>P_C1_X ? -1:1);

    }

    /********************  Confusion Matrix *********************/
    int TP = 0, FP = 0, TN = 0, FN = 0;
    for(int row = 0; row < labels_test.size(); row++)
    {
        if(test_records[row][0] == 1 && labels_test[row] == 1)
            TP++;
        else if(test_records[row][0] == -1 && labels_test[row] == -1)
            TN++;
        else if(test_records[row][0] == -1 && labels_test[row] == 1)
            FP++;
        else if(test_records[row][0] == 1 && labels_test[row] == -1)
            FN++;

    }
    /*
    cout << endl;
    cout << "Confusion Matrix for testing: "<< endl;
    cout << "true positive, false negative, false positive, true negative" << endl;
    cout << TP << " " <<FN << " " << FP << " " << TN << endl;
    cout << "Accuracy ratio: " << (double)(TP+TN)/labels_test.size() << endl;
    cout << "--------------------------------------------------------------------------" << endl;*/

}
