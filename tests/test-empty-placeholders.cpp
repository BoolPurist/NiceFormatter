//
// Created by nicegraphic on 3/15/22.
//

#include <catch2/catch.hpp>
#include <string>
#include "../lib/Format.h"

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

TEST_CASE("Empty placeholder combined with numbered ones. ")
{
  const std::string givenFormat{
    "User is {0} To: {}.{}@{}.com, Subject: {3}"
  };
  const std::string givenUserName{"Max"};
  const std::string givenLastName{"Ulf"};
  const std::string givenCompany{"company"};
  const std::string givenSubject{"work"};

  const std::string expected{
    "User is Max To: Max.Ulf@company.com, Subject: work"
  };

  const std::string actual{
    NiceGraphic::Format(
      givenFormat,
      givenUserName,
      givenLastName,
      givenCompany,
      givenSubject
      )
  };

  REQUIRE(actual == expected);
}

