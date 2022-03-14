//
// Created by nicegraphic on 3/11/22.
//
#include "../Format.h"
#include <iostream>

void AssertShortSimple();

int main()
{

  AssertShortSimple();
}

void AssertShortSimple()
{
  const int x{5};
  const int y{20};

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  std::cout << output << std::endl;
}