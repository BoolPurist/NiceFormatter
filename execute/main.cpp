//
// Created by nicegraphic on 3/11/22.
//
#include <Format.h>
#include <iostream>
#include <string>
#include <iomanip>      // std::setw

void PrintLine(const std::string& message);
void AssertShortSimple();
void AssertThrowInvalidExpForWrongNbrOfPlaceHolders();
void AssertThrowInvalidExpForWrongFormat();
void Example1();
void Example2();
void Example3();
void Example4();
void Example5();

int main()
{
  Example4();
}

void Example5()
{
  std::cout
    << NiceGraphic::Format("{,-12}{,-8}{,-4}\n{,-12}{,-8}{,-4}", "Name", "Price", "ID", "Computer", "400$", "45")
    << std::endl;
}


void Example4()
{
  std::cout
  << NiceGraphic::Format("{,12}{,8}{,4}\n{,12}{,8}{,4}", "Name", "Price", "ID", "Computer", "400$", "45")
  << std::endl;
}

void Example3()
{
  std::cout << NiceGraphic::Format("An {1} from the {}", "apple", "tree") << std::endl;
}

void Example2()
{
  const std::vector<int> scores{4500, 2000, 1000};
  std::cout << NiceGraphic::Format(
    "1. {}\n2. {}\n3. {}",
    scores.at(0),
    scores.at(1),
    scores.at(2)
    ) << std::endl;

}

void Example1()
{
  const std::pair<int, int> coords{2, 2};
  std::cout << NiceGraphic::Format("({0},{1})", coords.first, coords.second)
            << std::endl;
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