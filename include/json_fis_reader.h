/*
Historically snprintf() was not included in std::
Microsoft compiler used _snprintf() or sprintf_s() instead.
Therefore CPython uses #define to uniform the call to snprintf
between MS and the rest of the world. See:
https://github.com/python/cpython/blob/e42b705188271da108de42b55d9344642170aa2b/Modules/_decimal/libmpdec/vccompat.h#L41

However, VS 2015+ now support std::snprintf()
see: https://msdn.microsoft.com/en-us/library/2ts7cx93.aspx
Quote: "Beginning with the UCRT in Visual Studio 2015 and Windows 10, 
snprintf is no longer identical to _snprintf. The snprintf function
behavior is now C99 standard compliant."

Since Json for Modern C++ uses std::snprintf()
(which is supported by VS 2015+) we no longer 
need the #define and the compilation fails because 
std::_snprintf() does not exist.

In conclusion we need to undef this #define
to have a similar behaviour in all platforms.

It seems that json for modern c++ fixed this issue though,
but it is not working here, do not know why....: 
https://github.com/nlohmann/json/issues/1337
*/
#ifdef _MSC_VER
  #undef snprintf
#endif

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
