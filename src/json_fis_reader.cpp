#include "json_fis_reader.h"
#include "default_fuzzy_rule.h"
#include "fuzzy_rule.h"
#include "linguisticvariable.h"
#include "trilv.h"
#include <sstream>

using namespace std;

JsonFISReader::JsonFISReader(const string &json_fis) {
  jfis = json::parse(json_fis);
}

SingletonFIS JsonFISReader::read() {
  auto version = jfis["version"];
  ensure_version_is_supported(version);

  // Parse linguistic variables
  unordered_map<string, const vector<double>> jlvs =
      jfis["linguistic_variables"];

  unordered_map<size_t, LinguisticVariable> lvs;
  for (auto &jlv : jlvs) {
    auto var_idx = jlv.first;
    auto p_points = jlv.second;

    auto var_min = jfis["vars_range"][var_idx][0];
    auto var_max = jfis["vars_range"][var_idx][1];

    p_points = scale_lvs_to01(var_min, var_max, p_points);

    TriLV tri_lv(p_points);
    lvs[stoi(var_idx)] = tri_lv;
  }

  // Parse rules
  vector<FuzzyRule> rules;
  for (auto &jrule : jfis["rules"]) {
    // antecedents
    vector<pair<size_t, Antecedent>> ants;
    for (auto &jant : jrule[0]) {
      auto var_idx = static_cast<size_t>(stoi(jant[0].get<string>()));
      size_t mf_idx = jant[1];
      Antecedent ant(lvs.at(var_idx), mf_idx);
      ants.push_back(make_pair(var_idx, ant));
    }

    // consequents
    vector<double> cons = jrule[1];
    rules.emplace_back(ants, cons);
  }
  DefaultFuzzyRule default_rule{jfis["default_rule"]};

  SingletonFIS fis(rules, default_rule);
  return fis;
}

void JsonFISReader::ensure_version_is_supported(size_t version) {
  if (version == SUPPORTED_VERSION) {
    return;
  }

  stringstream ss;
  ss << "Unsupported tff version " << SUPPORTED_VERSION;
  auto msg = ss.str();
  cerr << msg << endl;
  throw invalid_argument(msg);
}

vector<double> JsonFISReader::scale_lvs_to01(double var_min, double var_max,
                                             const vector<double> &p_points) {
  const size_t p_points_size = p_points.size();

  vector<double> scaled_lvs(p_points_size);
  for (size_t i = 0; i < p_points_size; i++) {
    const auto scaled_p_point = (p_points[i] - var_min) / (var_max - var_min);
    scaled_lvs[i] = scaled_p_point;
  }

  return scaled_lvs;
}

unordered_map<size_t, vector<double>> JsonFISReader::get_vars_range() {
  cout << jfis << endl;
  // TODO create map<size_t,

  unordered_map<size_t, vector<double>> vars_range;
  unordered_map<string, vector<double>> vars_range_str = jfis["vars_range"];

  for (auto &var_range : vars_range_str) {
    auto var_name = var_range.first;
    auto var_idx = static_cast<size_t>(stoi(var_name));
    vector<double> range = std::move(var_range.second);

    vars_range.emplace(make_pair(var_idx, range));
  }
  return vars_range;
}

vector<vector<double>> JsonFISReader::get_cons_range() {
  return jfis["cons_range"];
}

vector<size_t> JsonFISReader::get_n_labels_per_cons() {
  return jfis["n_labels_per_cons"];
}

// std::function<vector<vector<double>>(const vector<vector<double>> &)>
// JsonFISReader::get_scale_back_cons_func() {
//
//   return [=](const vector<vector<double>> &observations) {
//     const size_t obs_size = observations.size();
//     const size_t cons_size = observations[0].size();
//
//     cout << "helllllllo" << endl;
//     cout << json_fis << endl;
//     auto jfis = json::parse(json_fis);
//     const vector<int> n_labels_per_cons = jfis["n_labels_per_cons"];
//
//     vector<vector<double>> scaled_observations(obs_size);
//
//     for (size_t j = 0; j < obs_size; j++) {
//       auto observation = observations[j];
//       auto scaled_observation = scaled_observations[j];
//
//       for (size_t i = 0; i < cons_size; i++) {
//         // -1 because y is in [0, cons_n_labels-1]
//         // auto yolo = n_labels_per_cons[i] - 1;
//         // scaled_observation[i] =
//         //     observation[i] / (jfis["n_labels_per_cons"][i] - 1);
//
//         // double cons_min = jfis["cons_range"][i][0];
//         // double cons_max = jfis["cons_range"][i][1];
//         //
//         // // from [0, 1] to [cons_min, cons_max]
//         // scaled_observation[i] =
//         //     scaled_observation[i] * (cons_max - cons_min) + cons_min;
//       }
//     }
//     return scaled_observations;
//   };
// }
