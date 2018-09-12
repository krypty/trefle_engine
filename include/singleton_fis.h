#ifndef SINGLETON_FIS_H
#define SINGLETON_FIS_H

#include "default_fuzzy_rule.h"
#include "fuzzy_rule.h"

#include <iostream>
#include <vector>

using namespace std;

class SingletonFIS {
public:
  SingletonFIS(const vector<FuzzyRule> &rules,
               const DefaultFuzzyRule &default_rule);

  vector<vector<double>> predict(const vector<vector<double>> &observations);

private:
  vector<double> predict_observation(const vector<double> &observation);
  vector<double> defuzzify(const vector<double> &rules_activation,
                           const vector<vector<double>> &implicated_cons);

  template <typename T>
  vector<const T *> convertVecToVecPtr(const vector<T> &source);

private:
  const vector<FuzzyRule> rules;
  const DefaultFuzzyRule default_rule;
  vector<FuzzyRule *> all_rules;
};
#endif // SINGLETON_FIS_H
