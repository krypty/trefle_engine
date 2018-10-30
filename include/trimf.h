#ifndef TRIMF_H
#define TRIMF_H

#include "membershipfunction_i.h"

class TriMF : public MembershipFunction_I {
public:
  TriMF(double p0, double p1, double p2);

  // MembershipFunction_I interface
public:
  double fuzzify(double in_value);
};

#endif // TRIMF_H
