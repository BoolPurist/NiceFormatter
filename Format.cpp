
#include "Format.h"

namespace NiceGraphic::Internal::Format
{

  using LocationPlaceholders = std::map<size_t , std::vector<size_t>>;
  using PlacholdersSeq = std::vector<PlaceholderPosition>;

  LocationPlaceholders LocatePlaceHolders(const std::vector<Token> &where);
  PlacholdersSeq TurnIntoSortedSeq(LocationPlaceholders &toTurn);
  Token ProcessNextLiteral(
    size_t &currentPosition,
    const std::string &symbolSequence
  );

  Token ProcessNextPlaceHolder(
    size_t &currentPosition,
    const std::string &symbolSequence
  );

  const char kOpenPlaceHolderSymbol = '{';
  const char kClosePlaceHolderSymbol = '}';

  std::vector<Token> FormatTokenizer(const std::string& formatToTokenize)
  {
    std::vector<Token> tokens{};

    size_t formatSize{formatToTokenize.size()};
    if (formatSize == 0)
    {
      return tokens;
    }

    bool expectsLiteral{true};

    for(size_t i_symbol{0}; i_symbol < formatSize; i_symbol++)
    {
      Token newToken{};

      if (expectsLiteral)
      {
        newToken = ProcessNextLiteral(i_symbol, formatToTokenize);

        assert(!newToken.isPlaceHolder);
        assert(newToken.placeHolderIndex < 0);

        tokens.push_back(newToken);
        expectsLiteral = false;
      }
      else
      {
        // expects placeholder symbol
        newToken = ProcessNextPlaceHolder(i_symbol, formatToTokenize);

        assert(newToken.value.empty());
        assert(newToken.isPlaceHolder);
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

  Token ProcessNextPlaceHolder(
      size_t &currentPosition,
      const std::string &symbolSequence
    )
  {
    Token placeHolderToken{};
    placeHolderToken.isPlaceHolder = true;

    std::string placeHolderNumber{};

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
        // This loop ensures that only digits where appended to placeHolderNumber
        // This should not fail because of invalid_argument exception.
        placeHolderToken.placeHolderIndex = std::stoi(placeHolderNumber);
        return placeHolderToken;
      }
      else if (std::isdigit(currentSymbol))
      {
        placeHolderNumber += currentSymbol;
      }
      else
      {
        throw std::runtime_error("non digit based placeholder id.");
      }
    }

    // Should not reach end of format with no found closing '}'
    throw std::runtime_error("No closing symbol.");
  }

  std::vector<PlaceholderPosition> GetPlaceHolderLocation(
      const std::vector<Token> &toInspect
    )
  {
    auto foundPlaceHolders = LocatePlaceHolders(toInspect);
    auto sortedPlaceSeq = TurnIntoSortedSeq(foundPlaceHolders);

    // Checks if between placeholder ids is a gap.
    // Example caller ->
    // (hello {2}as as{1}a{0}axx{5}xx, var0, var1, var2, var3, var4, var5)
    // Here is the placeholder {4} missing
    for(
        size_t i_supposedNumber{0};
        i_supposedNumber < sortedPlaceSeq.size();
        i_supposedNumber++
      )
    {
      if (sortedPlaceSeq.at(i_supposedNumber).index != i_supposedNumber)
      {
        throw std::runtime_error("Placeholder ids are not ascending without gaps");
      }
    }

    return  sortedPlaceSeq;
  }

  void ThrowIfWrongArgNumber(int argNumber, int placeHolderNumber)
  {
    if (argNumber != placeHolderNumber)
    {
      std::ostringstream errorMsg;
      errorMsg << "Number of given variadic arguments are not correct.\n"
               << "Number of variadic arguments: (" << argNumber << ").\n"
               << "Format expects (" << placeHolderNumber << ") arguments. \n";
      throw Invalid_format(errorMsg.str());
    }
  }

  LocationPlaceholders LocatePlaceHolders(const std::vector<Token> &where)
  {
    LocationPlaceholders foundPlaceHolders{};

    for (size_t i_token{0}; i_token < where.size(); i_token++)
    {
      const auto &currentToken = where.at(i_token);
      if (currentToken.isPlaceHolder)
      {
        auto it = foundPlaceHolders.find(currentToken.placeHolderIndex);
        if (it != foundPlaceHolders.end())
        {
          it->second.push_back(i_token);
        }
        else
        {
          foundPlaceHolders.insert(std::pair(
              currentToken.placeHolderIndex,
              std::vector<size_t>{i_token}
              )
            );
        }

      }

    }

    return foundPlaceHolders;
  }

  PlacholdersSeq TurnIntoSortedSeq(LocationPlaceholders &toTurn)
  {
    PlacholdersSeq unsortedSeq{};

    for(const auto &[index, positions] : toTurn)
    {
      PlaceholderPosition newElement{index, positions};
      unsortedSeq.push_back(newElement);
    }

    std::sort(
        unsortedSeq.begin(),
        unsortedSeq.end(),
        PlaceholderPosition::Compare
      );

    return unsortedSeq;
  }

}