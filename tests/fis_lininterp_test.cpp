#include "catch.hpp"
#include "linear_interpolation.h"

using namespace std;

TEST_CASE("xs and ys should have the same size", "[single-file]") {
  vector<double> xs{1, 2, 3, 4, 5};
  vector<double> ys{10, 20, 30, 40, 50};

  REQUIRE(LinearInterpolation::interp(xs, ys, 3.5) == Approx(35));
  REQUIRE(LinearInterpolation::interp(xs, ys, -100) == Approx(10));
  REQUIRE(LinearInterpolation::interp(xs, ys, 100) == Approx(50));
  REQUIRE(LinearInterpolation::interp(xs, ys, 0) == Approx(10));
}

TEST_CASE("step function ascending", "[single-file]") {
  vector<double> xs{1, 2, 3, 3, 4};
  vector<double> ys{0, 0, 0, 1, 1};

  REQUIRE(LinearInterpolation::interp(xs, ys, 2.9) == Approx(0));
  REQUIRE(LinearInterpolation::interp(xs, ys, 3.0) == Approx(0));
  REQUIRE(LinearInterpolation::interp(xs, ys, 3.1) == Approx(1));
}

TEST_CASE("step function descending", "[single-file]") {
  vector<double> xs{1, 2, 2, 3, 4};
  vector<double> ys{1, 1, 0, 0, 0};

  REQUIRE(LinearInterpolation::interp(xs, ys, 1.9) == Approx(1));
  REQUIRE(LinearInterpolation::interp(xs, ys, 2.0) == Approx(1));
  REQUIRE(LinearInterpolation::interp(xs, ys, 2.1) == Approx(0));
}

TEST_CASE("basic interpolation", "[single-file]") {
  vector<double> xs{1.8, 2.7};
  vector<double> ys{1, 0};

  REQUIRE(LinearInterpolation::interp(xs, ys, 1.7) == Approx(1));
  REQUIRE(LinearInterpolation::interp(xs, ys, 1.8) == Approx(1));
  REQUIRE(LinearInterpolation::interp(xs, ys, 1.9) == Approx(0.888889));
  REQUIRE(LinearInterpolation::interp(xs, ys, 2.6) == Approx(0.111111));
  REQUIRE(LinearInterpolation::interp(xs, ys, 2.7) == Approx(0));
  REQUIRE(LinearInterpolation::interp(xs, ys, 2.8) == Approx(0));
}

