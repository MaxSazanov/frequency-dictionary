#ifndef FREQUENCY_DICTIONARY_HPP
#define FREQUENCY_DICTIONARY_HPP

#include "HashTable.h"
#include "Word.h"
#include "WordHash.h"

using namespace Table;

class FrequencyDictionary : public HashTable< Word, int, WordHash >
{
  public:
    explicit FrequencyDictionary(std::size_t size);
    void getThreeMostFrequent(std::ostream& out);
};

#endif //FREQUENCY_DICTIONARY_HPP