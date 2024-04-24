#ifndef STRING_H
#define STRING_H

#include <cstddef>

struct SimpleString
{
  char* str_;
  std::size_t capacity_;
  std::size_t size_ = 0;

  void reserve(std::size_t size);
  void insert(char ch);
};

#endif //STRING_H