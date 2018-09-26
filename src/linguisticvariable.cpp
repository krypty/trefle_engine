#include "linguisticvariable.h"
#include "linear_interpolation.h"
#include <iomanip>
#include <sstream>

double LinguisticVariable::fuzzify(size_t mf_index, double in_value) const {
  return LinearInterpolation::interp(in_values, mf_values[mf_index], in_value);
}

std::ostream &operator<<(std::ostream &ss, const LinguisticVariable &lv) {
  // Since operator<< is a friend of the Point class, we can access Point's
  // members directly.

  const auto vec_to_str = [](const vector<double> &vec) {
    std::stringstream ss;
    for (const auto &v : vec) {
      ss << setprecision(3) << v << ",";
    }
    string str = ss.str();
    str.pop_back(); // remove trailing ","
    return str;
  };

  ss << "LV: in_values[" << vec_to_str(lv.in_values) << "]";
  return ss;
}
