//
// Created by nicegraphic on 3/11/22.
//

#ifndef NICEFORMATPRINT_PLACEHOLDERPOSITION_H_
#define NICEFORMATPRINT_PLACEHOLDERPOSITION_H_

#include <vector>
#include <cstddef>

struct PlaceholderPosition
{
  size_t index{};
  std::vector<size_t> positions;

  PlaceholderPosition(size_t index, const std::vector<size_t>& toTake);
  static bool Compare(const PlaceholderPosition &left, const PlaceholderPosition &right);
};

#endif //NICEFORMATPRINT_PLACEHOLDERPOSITION_H_
