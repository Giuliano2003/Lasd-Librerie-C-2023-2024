
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec:public virtual Queue<Data>,virtual protected Vector<Data> {
  // Must extend Queue<Data>,
  //             Vector<Data>

private:

  // ...

protected:

  unsigned long head = 0;

  unsigned long tail = 0;

  using Vector<Data>::elem;

  using Vector<Data>::size;

  using Vector<Data>::Resize;

  using Queue<Data>::operator==;

  using Queue<Data>::operator!=;

  using Queue<Data>::operator=;



  //using Container::size;

public:

  // Default constructor
  QueueVec(){
    this->Resize(4,0);
  }

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> &) noexcept; // A stack obtained from a TraversableContainer
  QueueVec(MappableContainer<Data> &&) noexcept; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data> &) noexcept;

  // Move constructor
  QueueVec(QueueVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec<Data> & operator=(const QueueVec<Data> &) noexcept;

  // Move assignment
  QueueVec<Data> &operator=(QueueVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data> &)const noexcept;
  bool operator!=(const QueueVec<Data> &)const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data & Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data &dat) noexcept override; // Override Queue member (copy of the value)
  void Enqueue(Data && dat) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty() const noexcept override; // Override Container member

  unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void Expand();
  void Reduce();
  void Resize(unsigned long,unsigned long);
};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
