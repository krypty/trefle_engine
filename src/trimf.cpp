#include "linear_interpolation.h"

#include "trimf.h"

TriMF::TriMF(double p0, double p1, double p2)
    : MembershipFunction_I(vector<double>{p0, p1, p2},
                           vector<double>{0, 1, 0}) {}

double TriMF::fuzzify(double in_value) {
  return LinearInterpolation::interp(_in_values, _mf_values, in_value);
}
