//
// Created by nicegraphic on 3/11/22.
//



#include "../Format.h"



int main()
{
  const int x{5};
  const int y{20};

  const std::string output = NiceGraphic::Format("({0},{1})", x, y);
  std::cout << output << std::endl;

}