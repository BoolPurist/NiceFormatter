//
// Created by nicegraphic on 3/11/22.
//

#ifndef NICEFORMATPRINT_TOKEN_H_
#define NICEFORMATPRINT_TOKEN_H_

#include <string>

namespace NiceGraphic
{
  struct Token
  {
    std::string value{};
    int placeHolderIndex{-1};
    int padding{};

    bool IsPlaceHolder() const;

    bool IsRightNotLeftAligned() const;
  };
}

#endif //NICEFORMATPRINT_TOKEN_H_
