#include "fuzzy_rule.h"

vector<double> FuzzyRule::fuzzify(const vector<double> &observation) const {
  vector<double> fuzzified_ants;
  // for (const std::pair<size_t, Antecedent> &ant : ants) {
  for (const std::pair<size_t, Antecedent> &ant : ants) {
    double in_value = observation[ant.first];
    double fuzzified_value = ant.second.fuzzify(in_value);
    fuzzified_ants.push_back(fuzzified_value);
  }
  return fuzzified_ants;
}
double FuzzyRule::activate(const vector<double> &fuzzified_inputs) const {
  double ant_act = fuzzified_inputs[0];

  // apply the fuzzy operator using a sliding window of size 2
  for (size_t i = 1; i < fuzzified_inputs.size(); i++) {
    ant_act = fuzzy_operator(ant_act, fuzzified_inputs[i]);
  }
  return ant_act;
}

vector<double> FuzzyRule::implicate(double ant_act) const {
  vector<double> implicated_cons;
  implicated_cons.reserve(cons.size());

  for (auto &cons_value : cons) {
    implicated_cons.push_back(implication_method(ant_act, cons_value));
  }
  return implicated_cons;
}
