//
// Created by nicegraphic on 3/14/22.
//

#ifndef NICEFORMATPRINT_FORMATPRINTER_TPP_
#define NICEFORMATPRINT_FORMATPRINTER_TPP_

#include "FormatPrinter.h"

namespace NiceGraphic
{
  template<typename HasOutStreamOperator>
  void FormatPrinter::InsertFormatVars(const HasOutStreamOperator& lastToPrint)
  {
    InsertArgIntoFormat(lastToPrint);
  }

  template<typename HasOutStreamOperator,typename... ArgsHaveOutStreamOperator>
  void FormatPrinter::InsertFormatVars(
    const HasOutStreamOperator &toWrite,
    const ArgsHaveOutStreamOperator&... restToWrite
  )
  {
    InsertArgIntoFormat(toWrite);
    InsertFormatVars(restToWrite...);
  }

  template <typename HasOutStreamOperator>
  void FormatPrinter::InsertArgIntoFormat(const HasOutStreamOperator &toWrite)
  {
    const auto& placesToFill = positionsToInsert.at(printIndex);
    placeholderBuffer << toWrite;
    const auto& valueToInsert = placeholderBuffer.str();

    for (const auto& i_fill : placesToFill.positions)
    {
      formatTemplate.at(i_fill).value = valueToInsert;
    }

    placeholderBuffer.str("");
    placeholderBuffer.clear();

    printIndex++;
  }

}

#endif //NICEFORMATPRINT_FORMATPRINTER_TPP_
