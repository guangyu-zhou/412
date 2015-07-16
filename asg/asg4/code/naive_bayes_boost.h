#ifndef NBB_H
#define NBB_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
void naive_bayes_boost(std::vector<std::vector <int> > & samples, std::vector<std::vector <int> > & train_records, std::vector<std::vector <int> > & test_records,int max_idx, std::vector<int> &labels_train, std::vector<int> &labels_test);

#endif