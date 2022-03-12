//
// Created by nicegraphic on 3/11/22.
//

#ifndef NICEFORMATPRINT_FORMATPRINTER_H_
#define NICEFORMATPRINT_FORMATPRINTER_H_

#include <sstream>
#include <vector>
#include "Token.h"
#include "PlaceholderPosition.h"

namespace NiceGraphic
{
  class FormatPrinter
  {

   public:
    FormatPrinter(
        std::vector<Token> &&formatTemplate,
        std::vector<PlaceholderPosition> &&positionsToInsert
      );

    template<typename HasOutStreamOperator>
    void InsertFormatVars(const HasOutStreamOperator& lastToPrint)
    {
      InsertArgIntoFormat(lastToPrint);
    }

    template<typename HasOutStreamOperator,typename... ArgsHaveOutStreamOperator>
    void InsertFormatVars(
        const HasOutStreamOperator &toWrite,
        const ArgsHaveOutStreamOperator&... restToWrite
      )
    {
      InsertArgIntoFormat(toWrite);
      InsertFormatVars(restToWrite...);
    }

    std::ostringstream GetMergeBetweenFormatAndVars();

   private:
    std::vector<Token> formatTemplate;
    std::vector<PlaceholderPosition> positionsToInsert;
    std::ostringstream placeholderBuffer{};
    int printIndex{};

    template <typename HasOutStreamOperator>
    void InsertArgIntoFormat(const HasOutStreamOperator &toWrite)
    {
      const auto &toFill = positionsToInsert[printIndex];
      placeholderBuffer << toWrite;
      for (const auto insertIndex : toFill.positions)
      {
        formatTemplate.at(insertIndex).value = placeholderBuffer.str();
      }

      placeholderBuffer.str("");
      placeholderBuffer.clear();

      printIndex++;
    }

  };

}
#endif //NICEFORMATPRINT_FORMATPRINTER_H_
