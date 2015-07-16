#ifndef ADABOOST_H
#define ADABOOST_H

#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "naive_bayes_boost.h"

int getRanWithWight(std::vector<double>& choice_weight, double random);
void adaboost(std::vector<std::vector <int> > & train_records, std::vector< std::vector<int> > & test_records, int max_idx);
#endif