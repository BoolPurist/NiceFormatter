//
// Created by nicegraphic on 3/17/22.
//

#include "../lib/Format.h"
#include <catch2/catch.hpp>

TEST_CASE("Right padding for a placeholder")
{
  const std::string givenFormat{"{,10}{,10}"};

  const std::string givenCity{"New York"};
  const int givenPopulation{100000};

  const std::string expected{"  New York    100000"};

  const std::string actual{
    NiceGraphic::Format(givenFormat, givenCity, givenPopulation)
  };

  REQUIRE(expected == actual);
}

TEST_CASE("Left padding for a placeholder")
{
  const std::string givenFormat{"{,-10} {,-10}"};

  const std::string givenCity{"New York"};
  const int givenPopulation{100000};

  const std::string expected{"New York   100000    "};

  const std::string actual{
    NiceGraphic::Format(givenFormat, givenCity, givenPopulation)
  };

  REQUIRE(expected == actual);
}
