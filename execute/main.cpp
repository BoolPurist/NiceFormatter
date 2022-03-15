//
// Created by nicegraphic on 3/11/22.
//
#include "../Format.h"
#include <iostream>
#include <string>

void PrintLine(const std::string& message);
void AssertShortSimple();
void AssertThrowInvalidExpForWrongNbrOfPlaceHolders();
void AssertThrowInvalidExpForWrongFormat();

int main()
{
  std::cout << NiceGraphic::Format("Hello {} from {}", "max", "earth") << std::endl;
}

void PrintLine(const std::string& message)
{
  std::cout << message << std::endl;
}

void AssertShortSimple()
{
  PrintLine("Asserting case normal with okay args.");

  const int x{5};
  const int y{20};

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  PrintLine(output);
}

void AssertThrowInvalidExpForWrongNbrOfPlaceHolders()
{
  using namespace std::literals;

  PrintLine("Asserting case with wrong number of placeholder args.");

  const std::string format = "{0} <==> {1}"s;

  // Call with too few arguments
  try
  {
    NiceGraphic::Format(format, 1);
    assert(false);
  }
  catch(const NiceGraphic::InvalidFormat& error)
  {
    PrintLine(error.what() );
  }

  // Call with too many arguments
  try
  {
    NiceGraphic::Format(format, 1, 2, 3);
    assert(false);
  }
  catch(const NiceGraphic::InvalidFormat& error)
  {
    PrintLine(error.what());
  }
}

void AssertThrowInvalidExpForWrongFormat()
{
  PrintLine("Asserting cases with wrong format");

  std::string currentWrongFormat{"aaa{a}aaa"};

  try
  {
    NiceGraphic::Format("aaa{a}aaa", 1);
    assert(false);
  }
  catch (const NiceGraphic::InvalidFormat& error)
  {
    PrintLine(error.what());
  }
  catch(...)
  {
    assert(false);
  }

  try
  {
    NiceGraphic::Format("aaa{0}a{2}aa", 1);
    assert(false);
  }
  catch (const NiceGraphic::InvalidFormat& error)
  {
    PrintLine(error.what());
  }
  catch(const std::exception& error)
  {
    PrintLine(error.what());
    assert(false);
  }

  try
  {
    NiceGraphic::Format("aaa{234", 1);
    assert(false);
  }
  catch (const NiceGraphic::InvalidFormat& error)
  {
    PrintLine(error.what());
  }
  catch(const std::exception& error)
  {
    PrintLine(error.what());
    assert(false);
  }
}