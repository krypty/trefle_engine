#ifndef FISVIEWER_H
#define FISVIEWER_H

#include "fmt/format.h"
#include "fuzzy_labels_generator.h"
#include "linguisticvariable.h"
#include "observations_scaler.h"
#include "singleton_fis.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class FISViewer {

public:
  FISViewer(const SingletonFIS &fis,
            const unordered_map<size_t, vector<double>> &vars_range)
      : fis(fis), scaler(vars_range) {
    size_t n_true_labels = fis.rules[0].ants[0].second.lv.mf_values.size();
    labels = FuzzyLabelsGenerator::generate(n_true_labels);
  }

  void describe() {
    // FIXME this works because p_positions==n_labels which is a too strong
    // assumption

    std::string out_description;

    for (auto &rule : fis.rules) {
      out_description.append(rule_to_string(rule));
    }
    out_description.append(rule_to_string(fis.default_rule));

    out_description.append("Variables definition\n");
    std::map<size_t, vector<double>> unique_vars;
    for (auto &r : fis.rules) {
      for (auto &ant : r.ants) {
        size_t var_idx = ant.first;
        vector<double> in_values = ant.second.lv.in_values;
        for (size_t i = 0; i < in_values.size(); i++) {
          in_values[i] = scaler.scale(var_idx, in_values[i]);
        }
        unique_vars[var_idx] = in_values;
      }
    }

    std::for_each(unique_vars.begin(), unique_vars.end(),
                  [&out_description](auto var) {
                    out_description.append(fmt::format("v{}:", var.first));
                    for (auto &p_point : var.second) {
                      out_description.append(fmt::format("{:.3f}, ", p_point));
                    }
                    out_description.append("\n");
                  });

    std::cout << out_description << std::endl;
  }

private:
  std::string rule_to_string(const FuzzyRule &rule) {
    std::string out_rule;
    bool is_normal_rule = rule.ants.size() > 0;
    if (is_normal_rule) {
      out_rule.append("IF ");
    }

    for (size_t i = 0; i < rule.ants.size(); i++) {
      auto ant = rule.ants[i];
      size_t var_index = ant.first;
      size_t mf_index = ant.second.mf_index;
      out_rule.append(fmt::format("v{} is {}", var_index, labels[mf_index]));

      if (i < rule.ants.size() - 1) {
        out_rule.append(" AND ");
      }
    }

    if (is_normal_rule) {
      out_rule.append(" THEN [");
    } else {
      out_rule.append("ELSE [");
    }

    for (size_t i = 0; i < rule.cons.size(); i++) {
      auto con = rule.cons[i];
      out_rule.append(fmt::format("{}", con));

      if (i < rule.cons.size() - 1) {
        out_rule.append(", ");
      }
    }
    out_rule.append("]\n");
    return out_rule;
  }

private:
  SingletonFIS fis;
  std::vector<std::string> labels;
  ObservationsScaler scaler;
};

#endif // FISVIEWER_H
