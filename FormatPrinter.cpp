//
// Created by nicegraphic on 3/11/22.
//

#include "FormatPrinter.h"

namespace NiceGraphic
{

  FormatPrinter::FormatPrinter(
    std::vector<Token> &&formatTemplate,
    std::vector<PlaceholderPosition> &&positionsToInsert
    ) : formatTemplate{std::move(formatTemplate)}
    , positionsToInsert{std::move(positionsToInsert)} {}

  void FormatPrinter::ThrowIfTooManyArgs()
  {
    printIndex++;
    if ( printIndex >= positionsToInsert.size() )
    {
      throw std::runtime_error("Too many argument for printing");
    }
  }
  void FormatPrinter::ThrowIfNotEqualArgsNumber()
  {
    ThrowIfTooManyArgs();
    int endIndex = printIndex + 1;
    if (endIndex != positionsToInsert.size())
    {
      throw std::runtime_error("Not right amount of arguments were given");
    }
  }

  std::ostringstream FormatPrinter::GetMergeBetweenFormatAndVars()
  {
    std::ostringstream merge{};

    for(const auto &token : formatTemplate)
    {
      merge << token.value;
    }

    return merge;
  }

}