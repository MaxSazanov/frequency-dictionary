#include <iostream>
#include <fstream>
#include "Word.h"
#include "WordHash.h"
#include "HashTable.h"
#include "FrequencyDictionary.h"

int main()
{

  std::ifstream in1("input.txt");
  Word curr{};

  FrequencyDictionary frequencyDictionary(2);
  if (in1.is_open())
  {
    while (!in1.eof())
    {
      in1 >> curr;
      frequencyDictionary[curr] += 1;
    }
  }
  in1.close();
  std::cout << frequencyDictionary[Word{"cata"}] << '\n' << frequencyDictionary[Word{"sergey"}] << '\n';

  FrequencyDictionary frequencyDictionary2(frequencyDictionary);
  frequencyDictionary2.insert(Word{"cata"});
  std::cout << frequencyDictionary2[Word{"cata"}] << '\n';

  for (Pair< Word, int >& pair : frequencyDictionary2)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << frequencyDictionary2[Word{"cata"}] << '\n' << frequencyDictionary2[Word{"sergey"}] << '\n';

  frequencyDictionary2[Word{"sergey"}] = 50;
  frequencyDictionary2[Word{"cata"}] = 20;
  frequencyDictionary2[Word{"man"}] = 10;
  frequencyDictionary2[Word{"repapa"}] = 5;
  frequencyDictionary2.getThreeMostFrequent();
  std::cout << '\n';
  frequencyDictionary2[Word{"man"}] = 100;

  frequencyDictionary2.getThreeMostFrequent();
  std::cout << '\n';

  std::cout << frequencyDictionary2.erase(Word{"sergey"}) << '\n';

  frequencyDictionary2.getThreeMostFrequent();
  std::cout << '\n';

  FrequencyDictionary frequencyDictionary3(100);
  frequencyDictionary3.getThreeMostFrequent();
  /*
  std::ifstream in("input.txt");
  HashTable< Word, int, WordHash > dictionary(2);

  if (in.is_open())
  {
    while (!in.eof())
    {
      in >> curr;
      dictionary[curr] += 1;
    }
  }
  in.close();

  HashTable< Word, int, WordHash > frequencyDictionary2(dictionary);

  std::cout << dictionary.insert(Word{"cata"}, 0).second << '\n';

  for (Pair< Word, int >& pair : dictionary)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << frequencyDictionary2[Word{"cata"}] << '\n' << frequencyDictionary2[Word{"sergey"}] << '\n';
  HashTable< Word, int, WordHash > frequencyDictionary3(std::move(dictionary));
  std::cout << frequencyDictionary3[Word{"cata"}] << '\n' << frequencyDictionary3[Word{"sergey"}] << '\n';
*/
  return 0;
}
