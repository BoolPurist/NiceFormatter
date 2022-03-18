//
// Created by nicegraphic on 3/14/22.
//

#ifndef NICEFORMATPRINT_FORMATPRINTER_TPP_
#define NICEFORMATPRINT_FORMATPRINTER_TPP_

#include "FormatArgsMerger.h"

namespace NiceGraphic::Internal::Format
{
  template<typename HasOutStreamOperator>
  void FormatArgsMerger::InsertFormatVars(const HasOutStreamOperator& lastToPrint)
  {
    InsertArgIntoFormat(lastToPrint);
  }

  template<typename HasOutStreamOperator,typename... ArgsHaveOutStreamOperator>
  void FormatArgsMerger::InsertFormatVars(
    const HasOutStreamOperator &toWrite,
    const ArgsHaveOutStreamOperator&... restToWrite
  )
  {
    InsertArgIntoFormat(toWrite);
    InsertFormatVars(restToWrite...);
  }

  template <typename HasOutStreamOperator>
  std::string FormatArgsMerger::CreateInsertValue(
      const PlaceholderPosition& placesToFill,
      const HasOutStreamOperator& toWrite
    )
  {
    const auto& currentToken = formatTemplate.at(
      placesToFill.positions.at(0)
    );

    placeholderBuffer << toWrite;
    if (currentToken.HasPadding())
    {
      auto valueLength = static_cast<int>(placeholderBuffer.str().size());
      auto absolutePadding = std::abs(currentToken.padding);
      auto toPadAmount = static_cast<size_t>(std::max(0, absolutePadding - valueLength));

      if (currentToken.IsRightNotLeftAligned())
      {
        ClearBuffer();
        placeholderBuffer << std::string(toPadAmount, ' ') << toWrite;
      }
      else
      {
        placeholderBuffer << std::string(toPadAmount, ' ');
      }
    }

    std::string valueToInsert{placeholderBuffer.str()};
    ClearBuffer();

    return valueToInsert;
  }

  template <typename HasOutStreamOperator>
  void FormatArgsMerger::InsertArgIntoFormat(const HasOutStreamOperator &toWrite)
  {
    const auto& placesToFill = positionsToInsert.at(printIndex);

    const auto& valueToInsert = CreateInsertValue(placesToFill, toWrite);

    for (const auto& i_fill : placesToFill.positions)
    {
      formatTemplate.at(i_fill).value = valueToInsert;
    }

    printIndex++;
  }

}

#endif //NICEFORMATPRINT_FORMATPRINTER_TPP_
