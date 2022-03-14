//
// Created by nicegraphic on 3/11/22.
//
#include "../Format.h"
#include <iostream>

void AssertShortSimple();
void AssertThrowInvalidExpForWrongNbrOfPlaceHolders();

int main()
{
  AssertShortSimple();
  AssertThrowInvalidExpForWrongNbrOfPlaceHolders();
}

void AssertShortSimple()
{
  std::cout << "Asserting case normal case with okay args."
            << std::endl;

  const int x{5};
  const int y{20};

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  std::cout << output << std::endl;
}

void AssertThrowInvalidExpForWrongNbrOfPlaceHolders()
{
  using namespace std::literals;

  std::cout << "Asserting case with wrong number of placeholder args."
            << std::endl;

  const std::string format = "{0} <==> {1}"s;

  // Call with too few arguments
  try
  {
    NiceGraphic::Format(format, 1);
    assert(false);
  }
  catch(const NiceGraphic::Invalid_format& error)
  {
    std::cout << error.what() << std::endl;
  }

  // Call with too many arguments
  try
  {
    NiceGraphic::Format(format, 1, 2, 3);
    assert(false);
  }
  catch(const NiceGraphic::Invalid_format& error)
  {
    std::cout << error.what() << std::endl;
  }
}