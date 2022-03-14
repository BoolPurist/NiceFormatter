//
// Created by nicegraphic on 3/14/22.
//

#include "Invalid_format.h"

namespace NiceGraphic
{

  Invalid_format::Invalid_format(const std::string &givenErrorMsg)
  : errorMsg{givenErrorMsg}
  {}

  Invalid_format::~Invalid_format() {}

  const char *Invalid_format::what() const throw()
  {
    return errorMsg.c_str();
  }
}