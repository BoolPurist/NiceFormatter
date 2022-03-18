//
// Created by nicegraphic on 3/15/22.
//

#include <catch2/catch.hpp>

#include "../lib/Format.h"
#include "../lib/InvalidFormat.h"

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

TEST_CASE("Wrong number of arguments for numbered and empty placeholders.")
{
  const std::string givenFormat{"({},{}) <==> ({0},{1})"};

  SECTION("Providing too few args. 1 instead of 2.")
  {
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(givenFormat, 1),
      NiceGraphic::InvalidFormat
    );
  }
  SECTION("Providing too many args. 4 instead of 2.")
  {
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(givenFormat, 1, 2, 3, 4),
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

TEST_CASE("Invalid placeholder number with leading zeros.")
{

  const int correctPlaceHolderValue{1};
  SECTION("Testing with only zeros in placeholder number.")
  {
    std::string wrongFormat{">>{00000}<<"};
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(wrongFormat, correctPlaceHolderValue),
      NiceGraphic::InvalidFormat
    );
  }
  SECTION("Testing with leading zeros in placeholder number.")
  {
    std::string wrongFormat{">>{00022}<<"};
    REQUIRE_THROWS_AS(
      NiceGraphic::Format(wrongFormat, correctPlaceHolderValue),
      NiceGraphic::InvalidFormat
    );
  }

}

TEST_CASE("Invalid format with letter after number.")
{
  const std::string wrongFormat{"aaa{0}a{1a}aa"};

  REQUIRE_THROWS_AS(
    NiceGraphic::Format(wrongFormat, 1, 2),
    NiceGraphic::InvalidFormat
  );
}

TEST_CASE("Testing invalid format for padding")
{
  using namespace std::literals;
  auto invalidFormat = GENERATE(
      ">>{0,,}<<"s,
      ">>{0,2,}<<"s,
      ">>{0,01}<<"s,
      ">>{0,a}<<"s,
      ">>{0,2a}<<"s,
      ">>{0,a2}<<"s
    );

  INFO("Given invalid format "s + invalidFormat);
  REQUIRE_THROWS_AS(
      NiceGraphic::Format(invalidFormat, 1),
      NiceGraphic::InvalidFormat
    );
}

