#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include "linguisticvariable.h"
#include <vector>

using namespace std;

class Antecedent {
public:
  Antecedent(const LinguisticVariable &lv, size_t mf_index)
      : lv(lv), mf_index(mf_index){};

  double fuzzify(double in_value) const {
    return lv.fuzzify(mf_index, in_value);
  }

  friend std::ostream &operator<<(std::ostream &stream, const Antecedent &ant) {
    stream << ant.lv << " label: " << ant.mf_index;
    return stream;
  }

public:
  const LinguisticVariable lv;
  const size_t mf_index;
};

#endif // ANTECEDENT_H
