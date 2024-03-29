#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H

#include "antecedent.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class FuzzyRule {
public:
  FuzzyRule(const vector<pair<size_t, Antecedent>> &ants,
            const vector<double> &cons)
      : ants(ants), cons(cons){};

  vector<double> fuzzify(const vector<double> &observation) const;
  double activate(const vector<double> &fuzzified_inputs) const;
  vector<double> implicate(double antecedent_activation) const;

  friend std::ostream &operator<<(std::ostream &ss, const FuzzyRule &fr) {
    ss << "fuzzy rule: ants [";
    for (auto &ant : fr.ants) {
      ss << "v" << ant.first << " " << ant.second << ", ";
    }
    ss << "] cons[";
    for (auto &c : fr.cons) {
      ss << c << ", ";
    }
    ss << "]";
    return ss;
  }

public:
  const vector<pair<size_t, Antecedent>> ants;
  const vector<double> cons;

protected:
  // we choose to use the minimum fuzzy operator.
  inline double fuzzy_operator(double op1, double op2) const {
    return std::min(op1, op2);
  }

  inline double implication_method(double ant_act, double cons) const {
    // As we use a singleton fuzzy inference system, the implication method is
    // defined as product between the antecedent's activation (i.e. a number
    // in [0, 1]) and the consequent's value. This will restrict the effect of
    // the consequent. It can be viewed as "let's use <ant_act> percent of the
    // consequent value"
    return ant_act * cons;
  }
};

#endif // FUZZY_RULE_H
