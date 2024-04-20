#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <exception>
#include "Pair.h"
#include "LinkedList.h"
#include "HashTableIterator.h"

using namespace List;

namespace Table
{
  template < class Key, class Value, class Hash = std::hash< Key > >
  class HashTable
  {
  public:
    explicit HashTable(size_t size);
    HashTable(const HashTable& table) = delete;
    HashTable(HashTable&& table) = delete;
    HashTable& operator=(const HashTable& src) = delete;
    HashTable& operator=(HashTable&& src) = delete;

    friend class HashTableIterator< Key, Value, Hash >;
    using iterator = HashTableIterator< Key, Value, Hash >;
    using const_iterator = HashTableIterator< Key, const Value, Hash >;

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    std::pair<Value&, bool> insert(const Key& key, const Value& value = Value());
    Value& operator[](const Key& key);
    bool erase(const Key& key);

  private:
    using Bucket = LinkedList<Pair<Key, Value>>;
    Bucket* table;
    std::size_t bucketCount;

    std::size_t getHash(const Key& key) const requires requires (std::size_t hash)
    {
      hash = Hash{}(key);
    };
  };

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::const_iterator HashTable<Key, Value, Hash>::cend() const
  {
    return HashTable::const_iterator(table + bucketCount, table + bucketCount);
  }

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::const_iterator HashTable<Key, Value, Hash>::cbegin() const
  {
    return HashTable::const_iterator(table, table + bucketCount);
  }

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::iterator HashTable<Key, Value, Hash>::end()
  {
    return HashTable::iterator(table + bucketCount, table + bucketCount);
  }

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::iterator HashTable<Key, Value, Hash>::begin()
  {
    return HashTable::iterator(table, table + bucketCount);
  }

  template<class Key, class Value, class Hash>
  bool HashTable<Key, Value, Hash>::erase(const Key& key)
  {
    return table[getHash(key)].remove(Pair{key, 0});;
  }

  template < class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::HashTable(std::size_t size):
    bucketCount(size)
  {
    table = new Bucket[bucketCount];
  }

  template < class Key, class Value, class Hash >
  std::pair<Value&, bool> HashTable< Key, Value, Hash >::insert(const Key& key, const Value& value)
  {
    Bucket& bucket = table[getHash(key)];
    const auto& insertionResult = bucket.insert(Pair{key, value});
    return std::pair<Value&, bool>((*insertionResult.first).value_, insertionResult.second);
  }

  template < class Key, class Value, class Hash >
  std::size_t HashTable< Key, Value, Hash >::getHash(const Key& key) const requires requires (std::size_t hash)
  {
    hash = Hash{}(key);
  }
  {
    return Hash{}(key) % bucketCount;
  }

  template < class Key, class Value, class Hash >
  Value& HashTable< Key, Value, Hash >::operator[](const Key& key)
  {
    Bucket& bucket = table[getHash(key)];
    for (Pair<Key, Value>& pair : bucket)
    {
      if (key == pair.key_)
      {
        return pair.value_;
      }
    }
    return insert(key).first;
  }
}

#endif //HASH_TABLE_H