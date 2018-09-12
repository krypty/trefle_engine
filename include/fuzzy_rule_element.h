#ifndef FRE_H
#define FRE_H

#include "linguisticvariable.h"
#include <string>

using namespace std;

class FuzzyRuleElement {
public:
  FuzzyRuleElement(const LinguisticVariable &lv_name, const string &lv_value,
                   const bool is_not = false);
};

#endif
