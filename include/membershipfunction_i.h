#ifndef MF_H
#define MF_H

#include <iostream>
#include <vector>

using namespace std;

class MembershipFunction_I {
public:
  MembershipFunction_I(const vector<double> &in_values,
                       const vector<double> &mf_values);

  virtual double fuzzify(double in_value) = 0;

  const vector<double> &in_values() { return _in_values; }
  const vector<double> &mf_values() { return _mf_values; }

  virtual ~MembershipFunction_I(){};

protected:
  vector<double> _in_values;
  vector<double> _mf_values;
};

#endif
