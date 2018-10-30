#include "singleton_fis.h"
#include <functional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr size_t SUPPORTED_VERSION = 1;

class JsonFISReader {
public:
  JsonFISReader(const string &json_fis);
  SingletonFIS read();
  unordered_map<size_t, vector<double>> get_vars_range();
  vector<vector<double>> get_cons_range();
  vector<size_t> get_n_labels_per_cons();

private:
  void ensure_version_is_supported(size_t version);
  vector<double> scale_lvs_to01(double var_min, double var_max,
                                const vector<double> &p_points);

private:
  json jfis;
};
