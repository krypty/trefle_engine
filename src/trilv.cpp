#include "trilv.h"
#include "linear_interpolation.h"

TriLV::TriLV(const vector<double> &p_points)
    : in_values(p_points), mf_values(p_points.size()) {

  const auto n_labels = static_cast<unsigned short>(p_points.size());

  for (size_t i = 0; i < n_labels; i++) {
    auto v = vector<double>(n_labels, 0.0);
    v[i] = 1.0;
    mf_values[i] = std::move(v);
  }
}

double TriLV::fuzzify(size_t mf_index, double in_value) {
  return LinearInterpolation::interp(in_values, mf_values[mf_index], in_value);
}
