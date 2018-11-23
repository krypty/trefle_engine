#include "catch.hpp"

using Catch::Matchers::Contains;

#include "fuzzy_labels_generator.h"

TEST_CASE("should raise an exception when asking only one fuzzy label") {
  REQUIRE_THROWS(FuzzyLabelsGenerator::generate(1),
                 Contains("Cannot generate less than 2 labels"));
}

TEST_CASE("generate 2 fuzzy labels") {
  auto labels = FuzzyLabelsGenerator::generate(2);

  REQUIRE(labels.size() == 2);
  REQUIRE(labels[0] == "low");
  REQUIRE(labels[1] == "high");
}

TEST_CASE("generate 4 fuzzy labels") {
  auto labels = FuzzyLabelsGenerator::generate(4);

  REQUIRE(labels.size() == 4);
  REQUIRE(labels[0] == "very low");
  REQUIRE(labels[1] == "low");
  REQUIRE(labels[2] == "medium");
  REQUIRE(labels[3] == "high");
}

TEST_CASE("generate 8 fuzzy labels") {
  auto labels = FuzzyLabelsGenerator::generate(8);

  REQUIRE(labels.size() == 8);
  REQUIRE(labels[0] == "3 very low");
  REQUIRE(labels[1] == "very very low");
  REQUIRE(labels[2] == "very low");
  REQUIRE(labels[3] == "low");
  REQUIRE(labels[4] == "medium");
  REQUIRE(labels[5] == "high");
  REQUIRE(labels[6] == "very high");
  REQUIRE(labels[7] == "very very high");
}
