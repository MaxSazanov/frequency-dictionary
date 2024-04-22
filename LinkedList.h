#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <algorithm>
#include "Node.h"
#include "LinkedListIterator.h"

namespace List
{
  template < class T >
  class LinkedList
  {
  public:
    LinkedList();
    LinkedList(LinkedList&& other) noexcept;
    LinkedList(const LinkedList& other) = delete;
    ~LinkedList();

    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;
    friend class LinkedListIterator< T >;
    using iterator = LinkedListIterator< T >;
    using const_iterator = LinkedListIterator< const T >;

    LinkedList(std::initializer_list< T > values);
    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list);
    std::pair< iterator, bool > insert(const T& newData);
    bool remove(const T& requiredData);

  private:
    Node<T>* head_;

    Node<T>* searchPrevious(const T& requiredData) const;
    Node<T>* searchFrom(Node< T >* begin, const T& requiredData) const;
    std::pair<iterator, bool> insertAfter(Node< T >* begin, Node< T >* newNode);
  };

  template< class T >
  LinkedList< T >::LinkedList() :
    head_(nullptr)
  {}

  template< class T >
  LinkedList< T >::~LinkedList()
  {
    while (head_)
    {
      Node<T>* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }

  template< class T >
  LinkedList<T>::LinkedList(LinkedList&& other) noexcept:
    head_(other.head_)
  {
    other.head_ = nullptr;
  }

  template< class T >
  LinkedList< T >& LinkedList< T >::operator=(const LinkedList& other)
  {
    if (head_ != nullptr)
    {
      delete this;
    }

    Node< T >* otherCurr = other.head_;
    while (otherCurr != nullptr)
    {
      insert(otherCurr->data_);
      otherCurr = otherCurr->next_;
    }
    return *this;
  }

  template< class T >
  LinkedList< T >& LinkedList< T >::operator=(LinkedList&& other) noexcept
  {
    if (this != &other)
    {
      std::swap(head_, other.head_);
    }

    return *this;
  }

  template < class T >
  LinkedList< T >::LinkedList(std::initializer_list< T > values) :
    head_(new Node< T >)
  {
    std::copy(values.begin(), values.end(), head_);
  }

  template < class T >
  LinkedList< T >::iterator LinkedList< T >::begin()
  {
    return LinkedList::iterator(head_);
  }

  template < class T >
  LinkedList< T >::iterator LinkedList< T >::end()
  {
    return LinkedList::iterator(nullptr);
  }

  template < class T >
  LinkedList< T >::const_iterator LinkedList< T >::cbegin() const
  {
    return LinkedList::const_iterator(head_);
  }

  template < class T >
  LinkedList< T >::const_iterator LinkedList< T >::cend() const
  {
    return LinkedList::const_iterator(nullptr);
  }

  template< class T >
  std::ostream& operator<<(std::ostream& out, const LinkedList< T >& list)
  {
    typename LinkedList< T >::Node* current = list.head_;
    while (current != nullptr)
    {
      out << current->data_ << ' ';
      current = current->next_;
    }
    return out;
  }

  template< class T >
  std::pair< LinkedListIterator< T >, bool > LinkedList< T >::insert(const T& newData)
  {
    auto* newNode = new Node< T >(newData);

    if (!head_)
    {
      head_ = newNode;
      return std::pair(LinkedListIterator< T >(head_), true);
    }
    return insertAfter(head_, newNode);
  }

  template< class T >
  bool LinkedList< T >::remove(const T& requiredData)
  {
    if (head_ == nullptr)
    {
      return false;
    }
    if (head_->data_ == requiredData)
    {
      Node< T >* temp = head_->next_;

      delete head_;
      head_ = temp;

      return true;
    }

    Node< T >* previous = searchPrevious(requiredData);
    if (previous == nullptr)
    {
      return false;
    }

    Node< T >* temp = previous->next_;
    if (temp->next_)
    {
      previous->next_ = temp->next_;
    }
    else
    {
      previous->next_ = nullptr;
    }

    delete temp;
    return true;
  }

  template< class T >
  Node<T>* LinkedList<T>::searchPrevious(const T& requiredData) const
  {
    Node<T>* current = head_;
    Node<T>* next = head_->next_;

    while (next)
    {
      if (next->data_ == requiredData)
      {
        return current;
      }

      current = next;
      next = next->next_;
    }

    return nullptr;
  }

  template< class T >
  Node< T >* LinkedList< T >::searchFrom(Node<T>* begin, const T& requiredData) const
  {
    Node< T >* current = begin;

    while (current)
    {
      if (current->data_ == requiredData)
      {
        return current;
      }

      current = current->next_;
    }

    return nullptr;
  }

  template< class T >
  std::pair<LinkedListIterator< T >, bool> LinkedList< T >::insertAfter(Node< T >* begin, Node< T >* newNode)
  {
    Node< T >* current = begin;
    if (begin->data_ == newNode->data_)
    {
      return std::pair(LinkedListIterator< T >(begin), false);
    }

    while (current->next_ != nullptr)
    {
      if (current->next_->data_ == newNode->data_)
      {
        return std::pair(LinkedListIterator< T >(current->next_), false);
      }
    }

    current->next_ = newNode;
    return std::pair(LinkedListIterator< T >(newNode), true);
  }
}

#endif // !LINKED_LIST_H