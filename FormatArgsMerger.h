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
  class FormatArgsMerger
  {

   public:
    FormatArgsMerger(
        std::vector<Token> &&formatTemplate,
        std::vector<PlaceholderPosition> &&positionsToInsert
      );

    template<typename HasOutStreamOperator>
    void InsertFormatVars(const HasOutStreamOperator& lastToPrint);

    template<typename HasOutStreamOperator,typename... ArgsHaveOutStreamOperator>
    void InsertFormatVars(
        const HasOutStreamOperator &toWrite,
        const ArgsHaveOutStreamOperator&... restToWrite
      );

    std::ostringstream GetMergeBetweenFormatAndVars();

   private:
    std::vector<Token> formatTemplate;
    std::vector<PlaceholderPosition> positionsToInsert;
    std::ostringstream placeholderBuffer{};
    int printIndex{};

    template <typename HasOutStreamOperator>
    void InsertArgIntoFormat(const HasOutStreamOperator &toWrite);

  };

}

#include "FormatPrinter.tpp"
#endif //NICEFORMATPRINT_FORMATPRINTER_H_
