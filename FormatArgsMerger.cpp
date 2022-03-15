//
// Created by nicegraphic on 3/11/22.
//

#include "FormatArgsMerger.h"

namespace NiceGraphic
{

  FormatArgsMerger::FormatArgsMerger(
    std::vector<Token> &&formatTemplate,
    std::vector<PlaceholderPosition> &&positionsToInsert
    )
    : formatTemplate{std::move(formatTemplate)}
    , positionsToInsert{std::move(positionsToInsert)}
    {}

  std::ostringstream FormatArgsMerger::GetMergeBetweenFormatAndVars()
  {
    std::ostringstream merge{};

    for(const auto &token : formatTemplate)
    {
      merge << token.value;
    }

    return merge;
  }

}