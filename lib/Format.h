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
#include "FormatArgsMerger.h"
#include "InvalidFormat.h"
#include "FormatArgsMerger.h"
#include "Tokenization.h"


namespace NiceGraphic
{
  /// Allows to insert variadic arguments into a format string.
  /// Precondition: Variadic arguments have to got an output stream operator.
  /// @param format Is the template to be merged with variadic arguments.
  /// It denotes a position for a variadic argument with a {Positive number}
  /// @param variadicArgs Variables to be inserted in the format.
  /// @example Format("({0},{1})", 2, 4) => (2,4)
  template<typename... ArgsHaveOutStreamOperator>
  std::string Format(
    const std::string &format,
    const ArgsHaveOutStreamOperator&... variadicArgs
  );

}

namespace NiceGraphic::Internal::Format
{
  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize);

  std::vector<PlaceholderPosition> GetPlaceHolderLocation(
    const std::vector<Token> &toInspect
  );

  void ThrowIfWrongArgNumber(int argNumber, int placeHolderNumber);
}

#include "Format.tpp"

#endif //NICEFORMATPRINT_LIBRARY_H
