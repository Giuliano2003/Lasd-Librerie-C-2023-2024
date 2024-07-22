#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst:public virtual Queue<Data>,protected virtual List<Data> {
  // Must extend Queue<Data>,
  //             List<Data>

private:

  // ...

protected:

  using List<Data>::Node;

  using Queue<Data>::operator==;

  using Queue<Data>::operator!=;

  using Queue<Data>::operator=;
  // ...

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> &) noexcept; // A stack obtained from a TraversableContainer
  QueueLst(MappableContainer<Data> &&) noexcept; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data> &) noexcept;

  // Move constructor
  QueueLst(QueueLst<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueLst();

  /* ************************************************************************ */

  // Copy assignment
  QueueLst<Data>& operator=(const QueueLst<Data> &) noexcept;

  // Move assignment
  QueueLst<Data>& operator=(QueueLst<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst<Data>&)const noexcept;
  bool operator!=(const QueueLst<Data> &)const  noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data &) noexcept override; // Override Queue member (copy of the value)
  void Enqueue(Data &&) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  
  using List<Data>::Clear;
protected:

  // Auxiliary functions, if necessary!

};
}
#include"queuelst.cpp"
#endif
