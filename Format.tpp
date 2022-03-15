#ifndef NICE_FORMAT_TEMPLATE_LIBRARY_H
#define NICE_FORMAT_TEMPLATE_LIBRARY_H

#include "Format.h"
#include "FormatArgsMerger.h"

namespace NiceGraphic
{
  template<typename... ArgsHaveOutStreamOperator>
  std::string Format(
    const std::string &format,
    const ArgsHaveOutStreamOperator&... variadicArgs
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

    FormatArgsMerger printer{
      std::move(tokens),
      std::move(position)
    };

    printer.InsertFormatVars(variadicArgs...);
    return printer.GetMergeBetweenFormatAndVars().str();
  }
}

#endif //NICE_FORMAT_TEMPLATE_LIBRARY_H