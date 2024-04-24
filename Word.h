#ifndef WORD_H
#define WORD_H

#include <cstddef>
#include <iosfwd>

struct Word
{
  char* str_;

  bool operator==(const Word& other) const;
};

std::ostream& operator<<(std::ostream& out, Word& value);
std::istream& operator>>(std::istream& in, Word& value);

#endif //WORD_H