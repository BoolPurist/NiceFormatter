//
// Created by nicegraphic on 3/17/22.
//

#include "Token.h"

namespace NiceGraphic
{
  bool Token::IsPlaceHolder() const
  {
    return placeHolderIndex > -1;
  }

  bool Token::IsRightNotLeftAligned() const
  {
    return padding > 0;
  }
}