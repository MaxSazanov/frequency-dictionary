#include <utility>
#include <stdexcept>
#include "SimpleString.h"

void SimpleString::reserve(std::size_t capacity)
{
  if (capacity <= capacity_)
  {
    throw std::logic_error("WRONG_CAPACITY");
  }

  capacity_ *= 2;
  char* temp = new char[capacity]{'\0'};
  for (int i = 0; i != size_; ++i)
  {
    temp[i] = str_[i];
  }
  std::swap(str_, temp);
  delete[] temp;
}

void SimpleString::insert(char ch)
{
  if (size_ + 1 == capacity_)
  {
    reserve(capacity_ * 2);
  }
  str_[size_] = ch;
  ++size_;
}