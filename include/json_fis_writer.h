#include "singleton_fis.h"
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
                  // const vector<vector<double>> &vars_range,
                  string &json_output)
        : fis{fis}, n_true_labels{n_true_labels},
          n_labels_per_cons{n_labels_per_cons}, json_output{json_output} {};

    virtual void write() {
        json_output = "hello from JsonFISWriter::write()";

        json j_out;
        j_out["version"] = TFF_VERSION;
        j_out["n_labels"] = n_true_labels;
        j_out["n_labels_per_cons"] = n_labels_per_cons;

        cout << "used vars" << endl;
        auto used_vars_indices = fis.get_used_vars();
        for (auto &v_idx : used_vars_indices) {
            cout << "v idx " << v_idx << endl;
        }

        j_out["vars_used"] = used_vars_indices;

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

        json_output = j_out.dump();
    };

  protected:
    SingletonFIS fis;
    const size_t n_true_labels;
    string &json_output;
    const vector<size_t> n_labels_per_cons;
};
