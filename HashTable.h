#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <exception>
#include <vector>
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
    HashTable();
    explicit HashTable(std::size_t capacity);
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable();

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    friend class HashTableIterator< Key, Value, Hash >;
    using iterator = HashTableIterator< Key, Value, Hash >;
    using const_iterator = HashTableIterator< Key, const Value, Hash >;

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    std::pair< iterator, bool > insert(const Key& key, const Value& value = Value());
    Value& operator[](const Key& key);
    bool erase(const Key& key);
    void rehash(std::size_t count);
  private:
    using Bucket = LinkedList< Pair< Key, Value > >;
    Bucket* table_;
    std::size_t bucketCapacity_;
    std::size_t loadFactor_;

    std::size_t getHash(const Key& key) const requires requires (std::size_t hash)
    {
      hash = Hash{}(key);
    };
  };

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::HashTable():
    loadFactor_(0),
    bucketCapacity_(0),
    table_(nullptr)
  {}

  template< class Key, class Value, class Hash >
  void HashTable< Key, Value, Hash >::rehash(std::size_t count)
  {
    HashTable< Key, Value, Hash > temp(count);
    for (Pair< Key, Value >& pair : *this)
    {
      auto res = temp.insert(pair.key_, pair.value_);
    }
    bucketCapacity_ = temp.bucketCapacity_;
    std::swap(this->table_, temp.table_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >& HashTable< Key, Value, Hash >::operator=(HashTable&& other) noexcept
  {
    if (this != &other)
    {
      bucketCapacity_ = other.bucketCapacity_;
      loadFactor_ = other.loadFactor_;
      table_ = std::move(other.table_);
    }
    return *this;
  }

  template<class Key, class Value, class Hash>
  HashTable<Key, Value, Hash>::HashTable(HashTable&& other) noexcept:
    bucketCapacity_(other.bucketCapacity_),
    loadFactor_(other.loadFactor_),
    table_(nullptr)
  {
    std::swap(table_, other.table_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >& HashTable< Key, Value, Hash >::operator=(const HashTable& other)
  {
    if (this != &other)
    {
      HashTable< Key, Value, Hash > temp(other.bucketCapacity_);
      for (int i = 0; i < bucketCapacity_; ++i)
      {
        temp.table_[i] = other.table_[i];
      }
      bucketCapacity_ = other.bucketCapacity_;
      loadFactor_ = other.loadFactor_;
      std::swap(table_, temp.table_);
    }
    return *this;
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::HashTable(const HashTable& other) :
    bucketCapacity_(other.bucketCapacity_),
    loadFactor_(other.loadFactor_),
    table_(nullptr)
  {
    HashTable< Key, Value, Hash > temp(other.bucketCapacity_);
    for (int i = 0; i < bucketCapacity_; ++i)
    {
      temp.table_[i] = other.table_[i];
    }

    std::swap(table_, temp.table_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::~HashTable()
  {
    delete[] table_;
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::const_iterator HashTable< Key, Value, Hash >::cend() const
  {
    return HashTable::const_iterator(table_ + bucketCapacity_, table_ + bucketCapacity_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::const_iterator HashTable< Key, Value, Hash >::cbegin() const
  {
    return HashTable::const_iterator(table_, table_ + bucketCapacity_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::iterator HashTable< Key, Value, Hash >::end()
  {
    return HashTable::iterator(table_ + bucketCapacity_, table_ + bucketCapacity_);
  }

  template< class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::iterator HashTable< Key, Value, Hash >::begin()
  {
    return HashTable::iterator(table_, table_ + bucketCapacity_);
  }

  template< class Key, class Value, class Hash >
  bool HashTable< Key, Value, Hash >::erase(const Key& key)
  {
    return table_[getHash(key)].remove(Pair{key, 0});;
  }

  template < class Key, class Value, class Hash >
  HashTable< Key, Value, Hash >::HashTable(std::size_t capacity):
    bucketCapacity_(capacity),
    loadFactor_(0)
  {
    table_ = new Bucket[bucketCapacity_];
  }

  template < class Key, class Value, class Hash >
  std::pair< HashTableIterator< Key, Value, Hash >, bool > HashTable< Key, Value, Hash >::insert(const Key& key, const Value& value)
  {
    if (bucketCapacity_ - loadFactor_ <= 0)
    {
      rehash(bucketCapacity_ * 2);
    }
    std::size_t hash = getHash(key);
    Bucket& bucket = table_[hash];
    const auto& insertionResult = bucket.insert(Pair{key, value});
    if (insertionResult.second)
    {
      ++loadFactor_;
    }
    iterator hashTableIt = HashTableIterator< Key, Value, Hash >(table_ + hash, table_ + bucketCapacity_, insertionResult.first);
    return {hashTableIt, insertionResult.second};
  }

  template < class Key, class Value, class Hash >
  std::size_t HashTable< Key, Value, Hash >::getHash(const Key& key) const requires requires (std::size_t hash)
  {
    hash = Hash{}(key);
  }
  {
    return Hash{}(key) % bucketCapacity_;
  }

  template < class Key, class Value, class Hash >
  Value& HashTable< Key, Value, Hash >::operator[](const Key& key)
  {
    Bucket& bucket = table_[getHash(key)];
    for (Pair< Key, Value >& pair : bucket)
    {
      if (key == pair.key_)
      {
        return pair.value_;
      }
    }
    return insert(key).first->value_;
  }
}

#endif //HASH_TABLE_H