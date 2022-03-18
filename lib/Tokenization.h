//
// Created by nicegraphic on 3/15/22.
//

#ifndef NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_
#define NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_

#include <string>
#include <vector>
#include <optional>
#include "Token.h"
#include "InvalidFormat.h"
#include <cassert>

namespace NiceGraphic::Internal::Format
{
  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize);
}

#endif //NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_
