#include <iostream>
#include <fstream>
#include "Word.h"
#include "WordHash.h"
#include "HashTable.h"
#include "FrequencyDictionary.h"

// using namespace Table;

int main()
{
  std::ifstream in1("input.txt");
  Word curr{};
  FrequencyDictionary frequencyDictionary(100);
  if (in1.is_open())
  {
    while (!in1.eof())
    {
      in1 >> curr;
      frequencyDictionary[curr] += 1;
    }
  }
  in1.close();

  HashTable< Word, int, WordHash > frequencyDictionary2(frequencyDictionary);
  std::cout << frequencyDictionary2.insert(Word{"cata"}, 0).second << '\n';

  for (Pair< Word, int >& pair : frequencyDictionary)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << frequencyDictionary2[Word{"cata"}] << '\n' << frequencyDictionary[Word{"sergey"}] << '\n';

  frequencyDictionary[Word{"sergey"}] = 50;
  frequencyDictionary[Word{"cata"}] = 20;
  frequencyDictionary[Word{"man"}] = 10;
  frequencyDictionary.getThreeMostFrequent(std::cout);
  /*
  std::ifstream in("input.txt");
  HashTable< Word, int, WordHash > dictionary(100);

  if (in.is_open())
  {
    while (!in.eof())
    {
      in >> curr;
      dictionary[curr] += 1;
    }
  }

  HashTable< Word, int, WordHash > frequencyDictionary2(dictionary);
  in.close();

  std::cout << dictionary.insert(Word{"cata"}, 0).second << '\n';

  for (Pair< Word, int >& pair : dictionary)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << frequencyDictionary2[Word{"cata"}] << '\n' << dictionary[Word{"sergey"}];
   */

  return 0;
}
