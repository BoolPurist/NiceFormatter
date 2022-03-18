//
// Created by nicegraphic on 3/17/22.
//

#include "../lib/Format.h"
#include <catch2/catch.hpp>

void TestPaddingCityPop(
    const std::string& givenFormat,
    const std::string& cityName,
    size_t population,
    const std::string& expected
  )
{
  const std::string actual{
    NiceGraphic::Format(givenFormat, cityName, population)
  };

  REQUIRE(expected == actual);
}

TEST_CASE("Padding for a placeholder")
{
  const std::string givenCity{"New York"};
  const int givenPopulation{100000};

  SECTION("Left padding with unnumbered placeholder")
  {
    const std::string givenFormat{"{,10} {,10}"};
    const std::string expected{"  New York     100000"};
    TestPaddingCityPop(
        givenFormat,
        givenCity,
        givenPopulation,
        expected
      );
  }
  SECTION("Right padding with unnumbered placeholder")
  {
    const std::string givenFormat{"{,-10} {,-10}"};
    const std::string expected{"New York   100000    "};
    TestPaddingCityPop(
      givenFormat,
      givenCity,
      givenPopulation,
      expected
    );
  }
  SECTION("Left padding with numbered placeholder")
  {
    const std::string givenFormat{"{0,10} {1,10}"};
    const std::string expected{"  New York     100000"};
    TestPaddingCityPop(
      givenFormat,
      givenCity,
      givenPopulation,
      expected
    );
  }
  SECTION("Right padding with numbered placeholder")
  {
    const std::string givenFormat{"{0,-10} {1,-10}"};
    const std::string expected{"New York   100000    "};
    TestPaddingCityPop(
      givenFormat,
      givenCity,
      givenPopulation,
      expected
    );
  }
}





