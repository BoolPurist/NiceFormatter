//
// Created by nicegraphic on 3/14/22.
//

#include <catch2/catch.hpp>
#include "../Format.h"

TEST_CASE( "Test case with 0, 1 placeholders", "[Valid]" )
{
  const int x{ 5 };
  const int y{ 20 };
  const std::string expected{"(5,20)"};

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  REQUIRE(output == expected);
}

TEST_CASE( "Test case with 2x0, 1, 2  placeholders", "[Valid]" )
{
  const std::string arrow{ ">>" };
  const std::string face{ "*_*" };
  const std::string smile{ ":)" };
  const std::string expected{" >> *_* >> :) "};

  const std::string output = NiceGraphic::Format(
    " {0} {1} {0} {2} ",
      arrow,
      face,
      smile
    );
  REQUIRE(output == expected);
}