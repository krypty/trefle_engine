#include "linguisticvariable.h"
#include "linear_interpolation.h"
#include <sstream>

double LinguisticVariable::fuzzify(size_t mf_index, double in_value) const {
  return LinearInterpolation::interp(in_values, mf_values[mf_index], in_value);
}

std::ostream &operator<<(std::ostream &out, const LinguisticVariable &lv) {
  // Since operator<< is a friend of the Point class, we can access Point's
  // members directly.

  const auto vec_to_str = [](const vector<double> &vec) {
    std::stringstream ss;
    for (const auto &v : vec) {
      ss << v << ",";
    }
    string str = ss.str();
    str.pop_back(); // remove trailing ","
    return str;
  };

  out << "LV: in_values[" << vec_to_str(lv.in_values) << "] mf_values[";

  for (auto &mf : lv.mf_values) {
    out << "[" << vec_to_str(mf) << "], ";
  }
  out << "]";
  return out;
}
