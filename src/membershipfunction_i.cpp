#include "membershipfunction_i.h"

MembershipFunction_I::MembershipFunction_I(const vector<double> &in_values,
                                           const vector<double> &mf_values)
    : _in_values{in_values}, _mf_values{mf_values} {};

double MembershipFunction_I::fuzzify(double in_value) {
  cout << "TODO alalal" << endl;
  return in_value;
}

MembershipFunction_I::~MembershipFunction_I(){}
