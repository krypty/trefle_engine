#include "trilv.h"
#include "linear_interpolation.h"

TriLV::TriLV(const vector<double> &p_points) : LinguisticVariable() {
  in_values = p_points;

  const auto n_labels = static_cast<unsigned short>(p_points.size());

  for (size_t i = 0; i < n_labels; i++) {
    auto v = vector<double>(n_labels, 0.0);
    v[i] = 1.0;
    mf_values.push_back(v);
  }
}
