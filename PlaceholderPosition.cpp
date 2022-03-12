//
// Created by nicegraphic on 3/11/22.
//

#include "PlaceholderPosition.h"

PlaceholderPosition::PlaceholderPosition(size_t index, const std::vector<size_t>& toTake)
  : index{index}, positions{toTake} {}

bool PlaceholderPosition::Compare(const PlaceholderPosition &left, const PlaceholderPosition &right)
{
  return left.index < right.index;
}

