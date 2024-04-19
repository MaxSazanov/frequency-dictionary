#ifndef WORD_HASH_H
#define WORD_HASH_H

struct WordHash
{
  std::size_t operator()(const Word& word) const noexcept;
};

#endif //WORD_HASH_H