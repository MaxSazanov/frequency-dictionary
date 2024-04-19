#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <exception>
#include "LinkedList.h"

using namespace List;

template < class Key, class T, class Hash = std::hash< Key > >
class HashTable
{
public:
  explicit HashTable(size_t size);
  HashTable(const HashTable& table) = delete;
  HashTable(HashTable&& table) = delete;
  HashTable& operator=(const HashTable& src) = delete;
  HashTable& operator=(HashTable&& src) = delete;

  std::pair<T&, bool> insert(const Key& key, const T& value = T());
  T& operator[](const Key& key);
  bool erase(const Key& key);

private:
  struct Pair
  {
    Key key_;
    T value_;

    bool operator==(const Pair& other) const;
  };

  LinkedList<Pair>* table;
  std::size_t bucketCount;

  std::size_t getHash(const Key& key) const requires requires (std::size_t hash)
  {
    hash = Hash{}(key);
  };
};

template<class Key, class T, class Hash>
bool HashTable<Key, T, Hash>::erase(const Key& key)
{
  return table[getHash(key)].remove(Pair{key, 0});;
}

template < class Key, class T, class Hash >
bool HashTable< Key, T, Hash >::Pair::operator==(const HashTable::Pair& other) const
{
  return key_ == other.key_;
}

template < class Key, class T, class Hash >
HashTable< Key, T, Hash >::HashTable(std::size_t size):
  bucketCount(size)
{
  table = new LinkedList<Pair>[bucketCount];
}

template < class Key, class T, class Hash >
std::pair<T&, bool> HashTable< Key, T, Hash >::insert(const Key& key, const T& value)
{
  LinkedList<Pair>& bucket = table[getHash(key)];
  auto insertionResult = bucket.insert(Pair{key, value});
  return std::pair<T&, bool>((*insertionResult.first).value_, insertionResult.second);
}

template < class Key, class T, class Hash >
std::size_t HashTable< Key, T, Hash >::getHash(const Key& key) const requires requires (std::size_t hash)
{
  hash = Hash{}(key);
}
{
  return Hash{}(key) % bucketCount;
}

template < class Key, class T, class Hash >
T& HashTable< Key, T, Hash >::operator[](const Key& key)
{
  LinkedList<Pair>& bucket = table[getHash(key)];
  for (Pair& pair : bucket)
  {
    if (key == pair.key_)
    {
      return pair.value_;
    }
  }
  return insert(key).first;
}

#endif //HASH_TABLE_H