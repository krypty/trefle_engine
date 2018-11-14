#include "singleton_fis.h"
#include "omp.h"
#include <algorithm>

SingletonFIS::SingletonFIS(const vector<FuzzyRule> &rules,
                           const DefaultFuzzyRule &default_rule)
    : rules(rules), default_rule(default_rule) {

  // Regroup rules and default rule into one container
  vector<const FuzzyRule *> all_rules = convertVecToVecPtr(rules);
  all_rules.push_back(&default_rule);
}

vector<vector<double>>
SingletonFIS::predict(const vector<vector<double>> &observations) {
  vector<vector<double>> y_pred(observations.size(), vector<double>{});

  const long long n = observations.size();
#pragma omp parallel for
  for (long long i = 0; i < n; i++) {
    y_pred[i] = predict_observation(observations[i]);
  }
  return y_pred;
}
vector<double>
SingletonFIS::predict_observation(const vector<double> &observation) {
  // 1. Fuzzify the inputs
  // 2. Apply fuzzy operator
  // 3. Implicate the rules
  // 4. Handle default rule
  // 5. Aggregation and defuzzification

  // initial value can be set to 0 because activation values are in [0, 1]
  double max_ant_activation = 0.0;

  // rows=rules, cols=implicated cons per rule
  vector<vector<double>> rules_implicated_cons;
  rules_implicated_cons.reserve(all_rules.size());

  vector<double> rules_activation;

  for (auto &rule : rules) {
    auto fuzzified_inputs = rule.fuzzify(observation); // (1)

    double ant_activation = rule.activate(fuzzified_inputs); // (2)
    max_ant_activation = max(max_ant_activation, ant_activation);

    vector<double> implicated_cons = rule.implicate(ant_activation); // (3)

    rules_activation.push_back(ant_activation);
    rules_implicated_cons.push_back(std::move(implicated_cons));
  }

  // Handle default fuzzy rule
  double default_rule_act = 1.0 - max_ant_activation;
  // cout << "def rule act " << default_rule_act << endl;

  vector<double> implicated_cons_def_rule =
      default_rule.implicate(default_rule_act);

  rules_activation.push_back(default_rule_act);
  rules_implicated_cons.push_back(implicated_cons_def_rule);

  // Aggregation and defuzzification (actually only defuzzification
  // is done in the case of singleton systems)
  vector<double> defuzzified_outputs =
      defuzzify(rules_activation, rules_implicated_cons);

  return defuzzified_outputs;
}

vector<double>
SingletonFIS::defuzzify(const vector<double> &rules_activation,
                        const vector<vector<double>> &implicated_cons) {
  const size_t n_rules = implicated_cons.size();
  const size_t n_cons = implicated_cons[0].size();
  vector<double> defuzzified_outputs;

  for (size_t j = 0; j < n_cons; j++) {
    double numerator = 0.0;
    // denominator is never 0 because default rule activation is always > 0
    double denominator = 0.0;

    for (size_t i = 0; i < n_rules; i++) {
      double rule_act = rules_activation[i];
      numerator += implicated_cons[i][j];
      denominator += rule_act;
    }

    defuzzified_outputs.push_back(numerator / denominator);
  }
  return defuzzified_outputs;
}

set<size_t> SingletonFIS::get_used_vars() {
  set<size_t> vars_used_indices;
  for (auto &r : rules) {
    for (auto &ant : r.ants) {
      vars_used_indices.insert(ant.first);
    }
  }
  return vars_used_indices;
}

template <typename T>
vector<const T *> SingletonFIS::convertVecToVecPtr(const vector<T> &source) {
  vector<const T *> target(source.size());
  transform(source.begin(), source.end(), target.begin(),
            [](const T &t) { return &t; });
  return target;
}
