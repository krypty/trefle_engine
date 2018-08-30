#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H

#include "antecedent.h"
#include <vector>

using namespace std;

class FuzzyRule {
public:
  FuzzyRule(const vector<pair<size_t, Antecedent>> &ants,
            const vector<double> &cons)
      : ants(ants), cons(cons){};

  vector<double> fuzzify(const vector<double> &observation);
  double activate(const vector<double> &fuzzified_inputs);
  vector<double> implicate(double antecedent_activation);

  friend std::ostream &operator<<(std::ostream &ss, const FuzzyRule &fr) {
    ss << "fuzzy rule: ants [";
    for (auto &ant : fr.ants) {
      ss << "v" << ant.first << " " << ant.second << ", ";
    }
    cout << "] cons[";
    for (auto &c : fr.cons) {
      ss << c << ", ";
    }
    ss << "]";
    return ss;
  }

protected:
  // we choose to use the minimum fuzzy operator.
  inline double fuzzy_operator(double op1, double op2) { return min(op1, op2); }

  inline double implication_method(double ant_act, double cons) {
    // As we use a singleton fuzzy inference system, the implication method is
    // defined as product between the antecedent's activation (i.e. a number
    // in [0, 1]) and the consequent's value. This will restrict the effect of
    // the consequent. It can be viewed as "let's use <ant_act> percent of the
    // consequent value"
    return ant_act * cons;
  }
  const vector<pair<size_t, Antecedent>> ants;
  const vector<double> cons;
};

#endif // FUZZY_RULE_H
