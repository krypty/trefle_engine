#ifndef DEFAULT_FUZZY_RULE_H
#define DEFAULT_FUZZY_RULE_H

#include "fuzzy_rule.h"

class DefaultFuzzyRule : public FuzzyRule {
public:
  DefaultFuzzyRule(const vector<double> &cons) : FuzzyRule({}, cons) {}
};

#endif // DEFAULT_FUZZY_RULE_H
