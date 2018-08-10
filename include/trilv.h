#ifndef TRILV_H
#define TRILV_H

#include "linguisticvariable.h"

#include <vector>

using namespace std;

class TriLV : public LinguisticVariable {
public:
  TriLV(const vector<double> &p_points);
};

#endif // TRILV_H
