#ifndef TRILV_H
#define TRILV_H

#include <vector>

using namespace std;

class TriLV {
public:
  TriLV(const vector<double> &p_points);
  double fuzzify(size_t mf_index, double in_value);

protected:
  const vector<double> in_values;
  vector<vector<double>> mf_values;
};

#endif // TRILV_H
