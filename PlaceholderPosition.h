//
// Created by nicegraphic on 3/11/22.
//

#ifndef NICEFORMATPRINT_PLACEHOLDERPOSITION_H_
#define NICEFORMATPRINT_PLACEHOLDERPOSITION_H_

#include <vector>

struct PlaceholderPosition
{
  int index{};
  std::vector<size_t> positions;

  PlaceholderPosition(int index,const std::vector<size_t>& toTake);
  static bool Compare(const PlaceholderPosition &left, const PlaceholderPosition &right);
};

#endif //NICEFORMATPRINT_PLACEHOLDERPOSITION_H_
