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

TEST_CASE("Testing complex format with padding")
{
  // This test is based on the example on
  // https://docs.microsoft.com/en-us/dotnet/api/system.string.format?view=net-6.0
  // Under the section "Control spacing"
  const std::string expected{
    R"(  Year      Population

  2013         1025632
  2014         1105967
  2015         1148203
)"};

  auto years = std::array<int, 3>{2013, 2014, 2015};
  auto population = std::array<int, 3>{1025632, 1105967, 1148203};

  auto output = std::ostringstream{};
  output << NiceGraphic::Format("{0,6} {1,15}\n\n", "Year", "Population");
  for (size_t i{0}; i < years.size(); i++)
  {
    output << NiceGraphic::Format("{0,6} {1,15}\n", years[i], population[i]);
  }

  const std::string actual = output.str();
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





