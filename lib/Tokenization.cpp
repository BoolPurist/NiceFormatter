//
// Created by nicegraphic on 3/15/22.
//

#include "Tokenization.h"


namespace NiceGraphic::Internal::Format
{
  using namespace std::literals;

  static const char kOpenPlaceHolderSymbol = '{';
  static const char kClosePlaceHolderSymbol = '}';

  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize)
  {
    std::vector<Token> tokens{};

    size_t formatSize{formatToTokenize.size()};
    if (formatSize == 0)
    {
      return tokens;
    }

    size_t countFoundNumbered{0};
    bool expectsLiteral{true};

    for(size_t i_symbol{0}; i_symbol < formatSize; i_symbol++)
    {
      Token newToken{};

      if (expectsLiteral)
      {
        newToken = ProcessNextLiteral(i_symbol, formatToTokenize);

        assert(!newToken.IsPlaceHolder());
        assert(newToken.placeHolderIndex < 0);

        tokens.push_back(newToken);
        expectsLiteral = false;
      }
      else
      {
        // expects placeholder symbol
        newToken = ProcessNextPlaceHolder(
          i_symbol,
          formatToTokenize,
          countFoundNumbered
        );

        assert(newToken.value.empty());
        assert(newToken.IsPlaceHolder());
        assert(newToken.placeHolderIndex > -1);

        tokens.push_back(newToken);
        expectsLiteral = true;
      }


    }

    return tokens;
  }

  Token ProcessNextLiteral(
    size_t &currentPosition,
    const std::string &symbolSequence
  )
  {
    auto formatSize = symbolSequence.size();
    Token literalToken{};

    for (
      size_t i_symbol_literal{currentPosition};
      i_symbol_literal < formatSize;
      i_symbol_literal++
      )
    {
      const auto& currentSymbol = symbolSequence.at(i_symbol_literal);

      if (currentSymbol == kOpenPlaceHolderSymbol)
      {
        currentPosition = i_symbol_literal;
        return literalToken;
      }
      else
      {
        literalToken.value += currentSymbol;
      }
    }

    // This literal was the last in the format string.
    currentPosition = formatSize - 1;
    return literalToken;
  }

  bool CheckForEndOfPlaceholder(
      const std::string& symbolSequence,
      size_t& currentPosition
    )
  {
    if (
      currentPosition >= symbolSequence.size()
      )
    {
      // Should not reach end of format with no found closing '}'
      ThrowMissingCloseSymbol();
    }

    return symbolSequence.at(currentPosition) == kClosePlaceHolderSymbol;
  }

  std::optional<size_t> ProcessNumber(
      const std::string& symbolSequence,
      size_t& currentPosition,
      Token& placeHolderToken
    )
  {
    ThrowIfLeadingZero(currentPosition, symbolSequence);

    std::string placeHolderNumber{};
    size_t i_symbol_placeholder{currentPosition};

    // To extract numbered placeholders some parsing for is needed.
    for (
        ;
        i_symbol_placeholder < symbolSequence.size();
        i_symbol_placeholder++
      )
    {
      const char currentSymbol = symbolSequence.at(i_symbol_placeholder);

      if (std::isdigit(currentSymbol))
      {
        placeHolderNumber += currentSymbol;
      }
      else
      {
        break;
      }

    }

    currentPosition = i_symbol_placeholder;

    return !placeHolderNumber.empty() ?
      std::optional<size_t>{std::stoi(placeHolderNumber)} :
      std::nullopt;

  }

  void ProcessPlaceHolderNumber(
      const std::string& symbolSequence,
      size_t& currentPosition,
      Token& placeHolderToken,
      size_t& countFoundUnNumbered
    )
  {
    auto possibleNumber = ProcessNumber(
        symbolSequence,
        currentPosition,
        placeHolderToken
      );

    if (!possibleNumber.has_value())
    {
      placeHolderToken.placeHolderIndex = countFoundUnNumbered;
      countFoundUnNumbered++;
    }
    else
    {
      placeHolderToken.placeHolderIndex = possibleNumber.value();
    }

  }

  void ProcessPaddingAmount(
    const std::string& symbolSequence,
    size_t& currentPosition,
    Token& placeHolderToken
    )
  {
    int paddingAmount{};
    int paddingSign{1};

    if (symbolSequence.at(currentPosition) == '-')
    {
      paddingSign *= -1;
      currentPosition++;
    }

    auto possibleNumber = ProcessNumber(
        symbolSequence,
        currentPosition,
        placeHolderToken
      );

    if (!possibleNumber.has_value())
    {
      ThrowNoDigitInPlaceHolder(symbolSequence.at(currentPosition));
    }

    paddingAmount = possibleNumber.value();
    paddingAmount *= paddingSign;

    placeHolderToken.padding = paddingAmount;
  }

  Token ProcessNextPlaceHolder(
    size_t& currentPosition,
    const std::string& symbolSequence,
    size_t& countFoundUnNumbered
  )
  {
    Token placeHolderToken{};

    ProcessPlaceHolderNumber(
        symbolSequence,
        currentPosition,
        placeHolderToken,
        countFoundUnNumbered
      );

    if (CheckForEndOfPlaceholder(symbolSequence, currentPosition))
    {
      return placeHolderToken;
    }

    if (symbolSequence.at(currentPosition++) != ',')
    {
      ThrowMissingCloseSymbol();
    }
    else
    {
      ProcessPaddingAmount(symbolSequence, currentPosition, placeHolderToken);
    }

    return placeHolderToken;
  }

  void ThrowIfLeadingZero(size_t inspectSpot, const std::string &symbolSequence)
  {
    size_t size{symbolSequence.size()};
    size_t nextInspectSpot = inspectSpot + 1;

    if (
      // Leading zero can only be with at least one element ahead before the end
      nextInspectSpot < size &&
        // Found a zero which could be leading zero.
        symbolSequence[inspectSpot] == '0' &&
        // A closing } closes the placeholder anyway.
        // So no leading zero possible.
        symbolSequence[nextInspectSpot] != kClosePlaceHolderSymbol
      )
    {
      throw InvalidFormat(
        "Placeholder id/number should not have a leading zero"
      );
    }

  }


  void ThrowNoDigitInPlaceHolder(char noDigitSymbol)
  {
    std::string errorMessage{
      "("s + noDigitSymbol + ") is not digit for a placeholder argument"s
    };
    throw InvalidFormat(errorMessage);
  }

  void ThrowMissingCloseSymbol()
  {
    // Should not reach end of format with no found closing '}'
    throw InvalidFormat(
      "No closing "s + kClosePlaceHolderSymbol + " found."s
    );
  }



}