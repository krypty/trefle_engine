#ifndef TFF_FIS_WRITER_H
#define TFF_FIS_WRITER_H

#include "json_fis_writer.h"
#include "singleton_fis.h"
#include <fstream>
#include <iostream>

class TffFISWriter {
  public:
    TffFISWriter(const SingletonFIS &fis, size_t n_true_labels,
                 const vector<size_t> &n_cons_per_labels,
                 const vector<size_t> &n_classes_per_cons,
                 const vector<vector<double>> vars_range,
                 const vector<vector<double>> cons_range,
                 const string &filepath)
        : fis{fis}, n_true_labels{n_true_labels},
          n_classes_per_cons{n_classes_per_cons},
          n_cons_per_labels{n_cons_per_labels}, vars_range{vars_range},
          cons_range{cons_range}, filepath{filepath} {};

    virtual void write() {
        JsonFISWriter writer(fis, n_true_labels, n_cons_per_labels,
                             n_classes_per_cons, vars_range, cons_range,
                             json_output);
        writer.write();
        std::ofstream fout(filepath);
        if (fout) {
            fout << json_output;
        } else {
            cerr << "cannot write in " << filepath << endl;
        }
    }

  private:
    const SingletonFIS fis;
    const size_t n_true_labels;
    const vector<size_t> n_cons_per_labels;
    const vector<size_t> n_classes_per_cons;
    const vector<vector<double>> vars_range;
    const vector<vector<double>> cons_range;
    const string &filepath;
    string json_output;
};

#endif // TFF_FIS_WRITER_H
