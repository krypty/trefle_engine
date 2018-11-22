#ifndef SINGLETON_FIS_H
#define SINGLETON_FIS_H

#include "default_fuzzy_rule.h"
#include "fuzzy_rule.h"

#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class SingletonFIS {
public:
  SingletonFIS(const vector<FuzzyRule> &rules,
               const DefaultFuzzyRule &default_rule);

  vector<vector<double>> predict(const vector<vector<double>> &observations);

  friend std::ostream &operator<<(std::ostream &ss, const SingletonFIS &fis) {
    ss << "Singleton FIS: " << endl;
    ss << "    fuzzy rules" << endl;
    for (auto &fr : fis.rules) {
      ss << fr << endl;
    }
    ss << "    default fuzzy rule" << endl;
    ss << fis.default_rule << endl;
    return ss;
  }

  set<size_t> get_used_vars();

private:
  vector<double> predict_observation(const vector<double> &observation);
  vector<double> defuzzify(const vector<double> &rules_activation,
                           const vector<vector<double>> &implicated_cons);

public:
  const vector<FuzzyRule> rules;
  const DefaultFuzzyRule default_rule;

private:
  vector<std::reference_wrapper<const FuzzyRule>> all_rules;
};
#endif // SINGLETON_FIS_H
