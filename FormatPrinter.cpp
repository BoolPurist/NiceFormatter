//
// Created by nicegraphic on 3/11/22.
//

#include "FormatPrinter.h"

namespace NiceGraphic
{

  FormatPrinter::FormatPrinter(
    std::vector<Token> &&formatTemplate,
    std::vector<PlaceholderPosition> &&positionsToInsert
    )
    : formatTemplate{std::move(formatTemplate)}
    , positionsToInsert{std::move(positionsToInsert)}
    {}

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