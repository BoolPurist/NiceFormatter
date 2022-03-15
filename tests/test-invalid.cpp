//
// Created by nicegraphic on 3/15/22.
//

#include <catch2/catch.hpp>

#include "../Format.h"
#include "../InvalidFormat.h"

TEST_CASE("Invalid format with one non numbered placeholder")
{
  const std::string wrongFormat{"aaa{a}aaa"};
  REQUIRE_THROWS_AS(
    NiceGraphic::Format(wrongFormat, 0),
    NiceGraphic::InvalidFormat
    );
}

TEST_CASE("Wrong number of arguments for placeholders.")
{
  const std::string givenFormat{"{0} <==> {1}"};

  SECTION("Providing too few args. 1 instead of 2.")
  {
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(givenFormat, 1),
      NiceGraphic::InvalidFormat
      );
  }
  SECTION("Providing too many args. 3 instead of 2.")
  {
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(givenFormat, 1, 2, 3),
      NiceGraphic::InvalidFormat
    );
  }
}

TEST_CASE("Invalid format with missing }.")
{
  const std::string wrongFormat{"aaa{234"};

  REQUIRE_THROWS_AS(
    NiceGraphic::Format(wrongFormat, 1),
    NiceGraphic::InvalidFormat
  );
}

TEST_CASE("Invalid format with missing 1 between 0 and 2 for placeholders.")
{
  const std::string wrongFormat{"aaa{0}a{2}aa"};

  REQUIRE_THROWS_AS(
    NiceGraphic::Format(wrongFormat, 1, 2),
    NiceGraphic::InvalidFormat
  );
}
