//
// Created by nicegraphic on 3/14/22.
//

#include "InvalidFormat.h"

namespace NiceGraphic
{

  InvalidFormat::InvalidFormat(const std::string &givenErrorMsg)
  : errorMsg{givenErrorMsg.c_str()}
  {}

  InvalidFormat::~InvalidFormat() {}

  const char *InvalidFormat::what() const throw()
  {
    return errorMsg.c_str();
  }
}