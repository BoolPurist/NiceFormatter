//
// Created by nicegraphic on 3/15/22.
//

#ifndef NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_
#define NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_

#include <string>
#include <vector>
#include "Token.h"
#include "InvalidFormat.h"
#include <cassert>

namespace NiceGraphic::Internal::Format
{
  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize);

  Token ProcessNextLiteral(
    size_t &currentPosition,
    const std::string &symbolSequence
  );

  Token ProcessNextPlaceHolder(size_t& currentPosition,
    const std::string& symbolSequence,
    size_t& countFoundUnNumbered
  );

  void ThrowIfLeadingZero(size_t inspectSpot, const std::string &symbolSequence);
  void ThrowNoDigitInPlaceHolder(char noDigitSymbol);
  void ThrowMissingCloseSymbol();

}

#endif //NICEFORMATPRINT_9A1F93C5F6E34954AEFAF4199A75A973_TOKENIZATION_H_
