//
// Created by nicegraphic on 3/14/22.
//

#include <catch2/catch.hpp>
#include "../Format.h"

TEST_CASE( "Test case with 2 placeholders", "[Valid]" )
{
  const int x{ 5 };
  const int y{ 20 };

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  REQUIRE(output == "(5,20)");
}