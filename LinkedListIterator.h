#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H

#include <iterator>
#include "Node.h"

namespace List
{
  template < class T >
  class LinkedList;

  template< class T >
  class LinkedListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class LinkedList< T >;
  public:
    LinkedListIterator(const LinkedListIterator& it);

    using Value_type = T;
    using Reference = Value_type&;
    using Pointer = Value_type*;

    bool operator!=(const LinkedListIterator& other) const;
    bool operator==(const LinkedListIterator& other) const;
    Reference operator*() const;
    Pointer operator->() const;
    LinkedListIterator& operator++();
    LinkedListIterator operator++(int);
  private:
    Node< T >* node_;
    explicit LinkedListIterator(Node< T >* node);
  };

  template< class T >
  LinkedListIterator< T > LinkedListIterator< T >::operator++(int)
  {
    LinkedListIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template< class T >
  LinkedListIterator< T >::Pointer LinkedListIterator< T >::operator->() const
  {
    return &node_->data_;
  }

  template< class T >
  LinkedListIterator< T >::LinkedListIterator(Node< T >* node) :
    node_(node)
  {}

  template< class T >
  LinkedListIterator< T >::LinkedListIterator(const LinkedListIterator& it) :
    node_(it.node_)
  {}

  template< class T >
  bool LinkedListIterator< T >::operator!=(const LinkedListIterator& other) const
  {
    return node_ != other.node_;
  }

  template< class T >
  bool LinkedListIterator< T >::operator==(const LinkedListIterator& other) const
  {
    return node_ == other.node_;
  }

  template< class T >
  LinkedListIterator< T >::Reference LinkedListIterator< T >::operator*() const
  {
    return node_->data_;
  }

  template< typename T >
  LinkedListIterator< T >& LinkedListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }
}

#endif //LINKED_LIST_ITERATOR_H