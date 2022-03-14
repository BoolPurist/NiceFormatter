//
// Created by nicegraphic on 3/14/22.
//

#ifndef NICEFORMATPRINT_INVALID_FORMAT_H_
#define NICEFORMATPRINT_INVALID_FORMAT_H_

#include <exception>
#include <string>

namespace NiceGraphic
{
  class InvalidFormat : public std::exception
  {
   public:
    InvalidFormat(const std::string &givenErrorMsg);
    virtual ~InvalidFormat();
    virtual const char* what() const throw();
   private:
    const std::string errorMsg;
  };
}

#endif //NICEFORMATPRINTs_INVALID_FORMAT_H_
