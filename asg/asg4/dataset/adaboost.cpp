#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
//#include "naive_bayes.cpp"
#include "naive_bayes_boost.cpp"
#define k 10

using namespace std;
int getRanWithWight(vector<double>& choice_weight, double random)
{
    //std::srand(std::time(0));

    double sum_of_weight = 0;
    int num_choices = choice_weight.size();
    for(int i=0; i<num_choices; i++) {
       sum_of_weight += choice_weight[i];
    }
    double rnd = random;
    //cout << "rand: " << rnd << endl;
    for(int i=0; i<num_choices; i++) {
      if(rnd < choice_weight[i])
      {
          //cout << "i: " << i << endl;
          return i;
      }

      rnd -= choice_weight[i];
    }
    cout << "Wrong here" << endl;
}


void adaboost(vector<vector <int> > & train_records, vector< vector<int> > & test_records, int max_idx)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution(0.0,1.0);

    //cout << "some random numbers between 0.0 and 100.0: " << endl;




    vector<double > weights(train_records.size());
    vector< vector<int> > M_labels, M_labels_test;
    vector<double> alphas;
    for(int i = 0; i < train_records.size(); i++)
        weights[i] = (double)1/train_records.size();
    for(int round = 0; round < k; round++)
    {
        vector<vector <int>  > samples;
        vector<int> labels, labels_test;
        for(int i = 0; i < train_records.size(); i++)
        {
            //cout << generator << " " <<distribution(generator) << endl;
            int rand_idx = getRanWithWight(weights, distribution(generator));
            //cout << "rand_idx is " << rand_idx << endl;
            samples.push_back(train_records[rand_idx]);
        }
        naive_bayes_boost(samples, train_records, test_records, max_idx, labels, labels_test);

        M_labels.push_back(labels);
        M_labels_test.push_back(labels_test);

        double err_rate = 0;

        /* step 3 */
        for(int i = 0; i< samples.size(); i++)
        {
            if(labels[i]!=train_records[i][0])    // PIAZZA PROBLEM
                err_rate+=weights[i]*1;
        }
        if(err_rate > 0.5)
            continue;
        //cout  <<" err_rate " << err_rate << endl;

        double alpha = log((1-err_rate)/err_rate);
        alphas.push_back(alpha);
        /* step 4 */
        double sum_weight = 0;
        for(int i = 0; i< samples.size(); i++)
        {
            if(labels[i]==train_records[i][0])  // PIAZZA PROBLEM, original: sample
                weights[i] = weights[i]*err_rate/(1-err_rate);
            sum_weight+=weights[i];
        }
        /* normalize */
        //cout  <<" sum_weight " << sum_weight << endl;
        for(int i = 0; i< samples.size(); i++)
        {
            weights[i]/=sum_weight;
        }

    }

    /* final step: */
    vector<double> labels_combined(train_records.size());
    for(int round = 0 ; round < k ; round++)
    {
        for(int i = 0 ; i < train_records.size(); i++)
        {
            labels_combined[i]+= (double)alphas[round]*M_labels[round][i];
        }
        //cout << "inside " << round << endl;
    }

    for(int i = 0 ; i < train_records.size(); i++)
    {
        //cout << "labels_combined " << labels_combined[i] << endl;
        if(labels_combined[i]>0)
            labels_combined[i] = 1;
        else
            labels_combined[i] = -1;
        //cout << "labels_combined now " << labels_combined[i] << endl;
    }

    vector<double> labels_combined_test(test_records.size());
    for(int round = 0 ; round < k ; round++)
    {
        for(int i = 0 ; i < test_records.size(); i++)
        {
            labels_combined_test[i]+= (double)alphas[round]*M_labels_test[round][i];
        }
    }

    for(int i = 0 ; i < test_records.size(); i++)
    {
        //cout << "labels_combined_test " << labels_combined_test[i] << endl;
        if(labels_combined_test[i]>0)
            labels_combined_test[i] = 1;
        else
            labels_combined_test[i] = -1;
        //cout << "labels_combined now " << labels_combined[i] << endl;
    }

    int TP0 = 0, FP0 = 0, TN0 = 0, FN0 = 0;
    for(int row = 0; row < labels_combined.size(); row++)
    {
        if(train_records[row][0] == 1 && labels_combined[row] == 1)
            TP0++;
        else if(train_records[row][0] == -1 && labels_combined[row] == -1)
            TN0++;
        else if(train_records[row][0] == -1 && labels_combined[row] == 1)
            FP0++;
        else if(train_records[row][0] == 1 && labels_combined[row] == -1)
            FN0++;

    }

    cout << "Confusion Matrix for training: "<< endl;
    cout << "true positive, false negative, false positive, true negative" << endl;
    cout << TP0 << " " <<FN0 << " " << FP0 << " " << TN0 << endl;
    cout << "Accuracy ratio: " << (double)(TP0+TN0)/labels_combined.size() << endl;



    int TP = 0, FP = 0, TN = 0, FN = 0;
    for(int row = 0; row < labels_combined_test.size(); row++)
    {
        if(test_records[row][0] == 1 && labels_combined_test[row] == 1)
            TP++;
        else if(test_records[row][0] == -1 && labels_combined_test[row] == -1)
            TN++;
        else if(test_records[row][0] == -1 && labels_combined_test[row] == 1)
            FP++;
        else if(test_records[row][0] == 1 && labels_combined_test[row] == -1)
            FN++;

    }

    cout << endl;
    cout << "Confusion Matrix for testing: "<< endl;
    cout << "true positive, false negative, false positive, true negative" << endl;
    cout << TP << " " <<FN << " " << FP << " " << TN << endl;
    cout << "Accuracy ratio: " << (double)(TP+TN)/labels_combined_test.size() << endl << endl;


}
