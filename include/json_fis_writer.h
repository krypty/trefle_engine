#include "singleton_fis.h"
#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>

// increase this value on breaking changes
#define TFF_VERSION 1

// for convenience
using json = nlohmann::json;
using namespace std;

using AntPairJson = pair<string, size_t>;
using RuleJson = pair<vector<AntPairJson>, vector<double>>;

class JsonFISWriter {
  public:
    JsonFISWriter(const SingletonFIS &fis, size_t n_true_labels,
                  const vector<size_t> &n_labels_per_cons,
                  const vector<vector<double>> &vars_range, string &json_output)
        : fis{fis}, n_true_labels{n_true_labels},
          n_labels_per_cons{n_labels_per_cons}, vars_range{vars_range},
          json_output{json_output} {};

    virtual void write() {
        auto used_vars_indices = fis.get_used_vars();

        json j_out;
        j_out["version"] = TFF_VERSION;
        j_out["n_labels"] = n_true_labels;
        j_out["n_labels_per_cons"] = n_labels_per_cons;

        // Write vars_range
        unordered_map<string, array<double, 2>> vars_range_json;
        for (auto &var : used_vars_indices) {
            array<double, 2> var_range{vars_range[var][0], vars_range[var][1]};
            vars_range_json.emplace(to_string(var), var_range);
        }
        j_out["vars_range"] = vars_range_json;

        // Write linguistic_variables
        unordered_map<string, vector<double>> lvs_json;
        for (auto &rule : fis.rules) {
            vector<AntPairJson> ants_json;
            for (auto &ant : rule.ants) {
                auto var_idx = to_string(ant.first);
                if (lvs_json.find(var_idx) != lvs_json.end()) {
                    continue;
                }
                auto lv_json = scale_back_var(ant.second.lv.in_values,
                                              vars_range[ant.first]);
                lvs_json.emplace(var_idx, lv_json);
            }
        }
        j_out["linguistic_variables"] = lvs_json;

        // Write rules
        vector<RuleJson> rules_json;
        for (auto &rule : fis.rules) {
            vector<AntPairJson> ants_json;
            for (auto &ant : rule.ants) {
                // convert the var index to str because Tff
                // specification says variables must be string
                auto var_idx = to_string(ant.first);
                auto mf_index = ant.second.mf_index;
                ants_json.emplace_back(var_idx, mf_index);
            }

            // TODO scale back cons?
            auto cons_json = rule.cons;

            rules_json.emplace_back(ants_json, cons_json);
        }
        j_out["rules"] = rules_json;

        // TODO: scale back cons
        j_out["default_rule"] = fis.default_rule.cons;

        json_output = j_out.dump();
    };

  private:
    vector<double> scale_back_var(const vector<double> &in_values,
                                  const vector<double> &var_range) {
        vector<double> in_values_scaled(in_values.size());
        transform(in_values.begin(), in_values.end(), in_values_scaled.begin(),
                  [&var_range](double in_value) {
                      return in_value * (var_range[1] - var_range[0]) +
                             var_range[0];
                  });
        return in_values_scaled;
    }

  protected:
    SingletonFIS fis;
    const size_t n_true_labels;
    const vector<size_t> n_labels_per_cons;
    const vector<vector<double>> vars_range;
    string &json_output;
};
