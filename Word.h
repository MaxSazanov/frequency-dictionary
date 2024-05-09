#ifndef WORD_H
#define WORD_H

#include <cstddef>
#include <iosfwd>
#include <string>

struct Word
{
  std::string str_;

  bool operator==(const Word& other) const;
};

std::ostream& operator<<(std::ostream& out, Word& value);
std::istream& operator>>(std::istream& in, Word& value);

#endif //WORD_H