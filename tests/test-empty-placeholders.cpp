//
// Created by nicegraphic on 3/15/22.
//

#include <catch2/catch.hpp>
#include <string>
#include "../Format.h"

TEST_CASE("Empty placeholder only ")
{
  const std::string givenFormat{"To: {}@{}.com"};
  const std::string givenUserName{"example"};
  const std::string givenCompany{"company"};

  const std::string expected{"To: example@company.com"};

  const std::string actual{
    NiceGraphic::Format(givenFormat, givenUserName, givenCompany)
  };

  REQUIRE(actual == expected);
}

