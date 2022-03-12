#ifndef NICEFORMATPRINT_LIBRARY_H
#define NICEFORMATPRINT_LIBRARY_H

#include <string>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>
#include <sstream>

#include "Token.h"
#include "PlaceholderPosition.h"
#include "FormatPrinter.h"

namespace NiceGraphic::Internal::Format
{
  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize);

  std::vector<PlaceholderPosition> GetPlaceHolderLocation(
    const std::vector<Token> &toInspect
  );

  void ThrowIfWrongArgNumber(int argNumber, int placeHolderNumber);
}

namespace NiceGraphic
{

  /// Summary: Allows to insert variadic arguments into format string
  /// Param format: Is the template to be merged with variadic arguments.
  /// Params variadicArgs: Variables to be inserted in format.
  /// Format denotes a position for a variadic argument with {<Positive number>}
  /// Example: Format("({0},{1})", 2, 4) => (2,4)
  /// Precondition variadic arguments have a output stream operator operator.
  template<typename... ArgsHaveOutStreamOperator>
  std::string Format(
      const std::string &format,
      ArgsHaveOutStreamOperator... variadicArgs
    )
  {
    using namespace Internal::Format;


    auto tokens = FormatTokenizer(format);
    std::vector<PlaceholderPosition> position = GetPlaceHolderLocation(
        tokens
      );

    const auto numberOfFoundPlaceholders = position.size();
    const auto numberOfArgs = sizeof...(variadicArgs);

    ThrowIfWrongArgNumber(
        numberOfArgs,
        numberOfFoundPlaceholders
      );

    FormatPrinter printer{
      std::move(tokens),
      std::move(position)
    };

    printer.InsertFormatVars(variadicArgs...);
    return printer.GetMergeBetweenFormatAndVars().str();
  }

}

#endif //NICEFORMATPRINT_LIBRARY_H
