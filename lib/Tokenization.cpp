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

  Token ProcessNextPlaceHolder(size_t& currentPosition,
    const std::string& symbolSequence,
    size_t& countFoundUnNumbered
  )
  {
    Token placeHolderToken{};
    std::string placeHolderNumber{};
    bool found1Digit{};

    ThrowIfLeadingZero(currentPosition, symbolSequence);

    // To extract numbered placeholders some parsing for is needed.
    for (
      size_t i_symbol_placeholder{currentPosition};
      i_symbol_placeholder < symbolSequence.size();
      i_symbol_placeholder++
      )
    {
      auto currentSymbol = symbolSequence.at(i_symbol_placeholder);

      if (currentSymbol == kClosePlaceHolderSymbol)
      {
        currentPosition = i_symbol_placeholder;

        if (found1Digit)
        {
          // This loop ensures that only digits where appended to placeHolderNumber
          // This should not fail because of invalid_argument exception.
          placeHolderToken.placeHolderIndex = std::stoi(placeHolderNumber);
        }
        else
        {
          placeHolderToken.placeHolderIndex = countFoundUnNumbered;
          countFoundUnNumbered++;
        }

        return placeHolderToken;
      }
      else if (std::isdigit(currentSymbol))
      {
        found1Digit = true;
        placeHolderNumber += currentSymbol;
      }
      else
      {
        ThrowNoDigitInPlaceHolder(currentSymbol);
      }
    }

    // Should not reach end of format with no found closing '}'
    ThrowMissingCloseSymbol();
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