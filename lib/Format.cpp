
#include "Format.h"

namespace NiceGraphic::Internal::Format
{
  using namespace std::literals;

  using LocationPlaceholders_t = std::map<size_t , std::vector<size_t>>;
  using PlacholdersSeq_t = std::vector<PlaceholderPosition>;

  LocationPlaceholders_t LocatePlaceHolders(const std::vector<Token> &where);
  PlacholdersSeq_t TurnIntoSortedSeq(LocationPlaceholders_t &toTurn);

  Token ProcessNextLiteral(
    size_t &currentPosition,
    const std::string &symbolSequence
  );

  Token ProcessNextPlaceHolder(size_t& currentPosition,
    const std::string& symbolSequence,
    size_t& countFoundUnNumbered);

  void ThrowIfWrongArgNumber(int argNumber, int placeHolderNumber);
  void ThrowMissingPlaceholderId(size_t missingNumber);


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
        ThrowMissingPlaceholderId(i_supposedNumber);
      }
    }
    return  sortedPlaceSeq;
  }

  LocationPlaceholders_t LocatePlaceHolders(const std::vector<Token> &where)
  {
    LocationPlaceholders_t foundPlaceHolders{};

    for (size_t i_token{0}; i_token < where.size(); i_token++)
    {
      const auto &currentToken = where.at(i_token);
      if (currentToken.IsPlaceHolder())
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

  PlacholdersSeq_t TurnIntoSortedSeq(LocationPlaceholders_t &toTurn)
  {
    PlacholdersSeq_t unsortedSeq{};

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

  void ThrowMissingPlaceholderId(size_t missingNumber)
  {
    const std::string errorMessage{
      "Placeholder id ("s + std::to_string(missingNumber) +
        ") is missing."s
    };

    throw InvalidFormat(errorMessage);
  }

  void ThrowIfWrongArgNumber(int argNumber, int placeHolderNumber)
  {
    if (argNumber != placeHolderNumber)
    {
      std::ostringstream errorMsg;
      errorMsg << "Number of given variadic arguments are not correct.\n"
               << "Number of variadic arguments: (" << argNumber << ").\n"
               << "Format expects (" << placeHolderNumber << ") arguments. \n";
      throw InvalidFormat(errorMsg.str());
    }
  }


}