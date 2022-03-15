//
// Created by nicegraphic on 3/14/22.
//

#include <catch2/catch.hpp>
#include "../Format.h"
#include <iostream>

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

struct DummyRecord
{
  int id{0};
  std::string title{};
  double price{};

  explicit DummyRecord() {}
  DummyRecord(int newId, std::string newTitle,double newPrice)
  : id{newId},
  title{newTitle},
  price{newPrice}
  {}

  friend std::ostream& operator<<(std::ostream& os, DummyRecord record)
  {
    return os << "(" << record.id
    << "): , " << record.title
    << " with the price: "  << record.price << "$";
  }
};

TEST_CASE( "Test case with 0  placeholders and DummyRecord", "[Valid]" )
{
  const DummyRecord givenRecord{
    -10,
    "Maker wacker",
    2.5
  };

  const std::string givenFormat{"Record => {0} ..."};
  std::ostringstream bufferHelper{};
  bufferHelper << givenRecord;
  const std::string expected{
    "Record => (-10): , Maker wacker with the price: 2.5$ ..."
  };

  const std::string output = NiceGraphic::Format(
    givenFormat,
    givenRecord
  );
  REQUIRE(expected == output);
  // Record => (-10) , Maker wacker with the price: 2.5$
  // Record => (-10): , Maker wacker with the price: 2.5$
}