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
    bool isPlaceHolder{};
    std::string value{};
    int placeHolderIndex{-1};
  };
}

#endif //NICEFORMATPRINT_TOKEN_H_
