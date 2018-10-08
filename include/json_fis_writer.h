#include "singleton_fis.h"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

class JsonFISWriter {
    public:
      JsonFISWriter(const SingletonFIS &fis, string &json_output)
          : fis{fis}, json_output{json_output} {};

      virtual void write() {
            json_output = "hello from JsonFISWriter::write()";
            // create an empty structure (null)
            json j;

            // add a number that is stored as double (note the implicit
            // conversion of j to an object)
            j["pi"] = 3.141;
            json_output = j.dump();
      };

    protected:
      SingletonFIS fis;
      string &json_output;
};
