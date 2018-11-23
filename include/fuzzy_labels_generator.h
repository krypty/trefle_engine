#ifndef FUZZY_LABELS_GENERATOR_H
#define FUZZY_LABELS_GENERATOR_H

#include <sstream>
#include <string>
#include <vector>

class FuzzyLabelsGenerator {

public:
  static std::vector<std::string> generate(size_t n) {
    if (n < 2) {
      throw "Cannot generate less than 2 labels";
    } else if (n == 2) {
      return {"low", "high"};
    } else {
      return generate_more_than_two_labels(n);
    }
  }

private:
  static std::vector<std::string>
  generate_more_than_two_labels(size_t n_labels) {
    auto k = n_labels - 1; // minus one for the "medium" label
    auto k1 = k / 2;
    k = k - k1;

    std::vector<std::string> low_labels;
    low_labels = get_labels(k - 1, "low", low_labels);

    std::string medium_label = "medium";

    std::vector<std::string> high_labels;
    high_labels = get_labels(k1 - 1, "high", high_labels);

    std::vector<std::string> labels;
    labels.reserve(n_labels);

    labels.insert(labels.end(), low_labels.begin(), low_labels.end());
    labels.emplace_back("medium");
    labels.insert(labels.end(), high_labels.rbegin(), high_labels.rend());

    return labels;
  }

  static std::vector<std::string> get_labels(size_t n, std::string prefix,
                                             std::vector<std::string> &labels) {
    std::string new_label;
    if (n == -1) { // base recursion case
      return labels;
    } else if (n > 2) {
      std::stringstream ss;
      ss << n << " very " << prefix;
      new_label = ss.str();
    } else {
      std::stringstream ss;
      for (size_t i = 0; i < n; i++) {
        ss << "very ";
      }
      ss << prefix;
      new_label = ss.str();
    }

    labels.push_back(new_label);
    return get_labels(n - 1, prefix, labels);
  }
};

#endif // FUZZY_LABELS_GENERATOR_H
