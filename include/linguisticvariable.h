#ifndef LINGUISTICVARIABLE_I_H
#define LINGUISTICVARIABLE_I_H

#include <iostream>
#include <vector>

using namespace std;

class LinguisticVariable {
public:
  double fuzzify(size_t mf_index, double in_value) const;
  friend std::ostream &operator<<(std::ostream &out,
                                  const LinguisticVariable &lv);

public:
  vector<double> in_values;
  vector<vector<double>> mf_values;

protected:
  LinguisticVariable() {} // make this class abstract because only derived
                          // classes can call this ctor
};

#endif // LINGUISTICVARIABLE_I_H
