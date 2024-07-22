
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue: public virtual ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Queue()=default;

  /* ************************************************************************ */

  Queue<Data> &operator=(const Queue<Data> &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Queue<Data> &operator=(Queue<Data> &&) noexcept = delete; // Move assignment of abstract types is not possible.


  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const Queue<Data> &)const noexcept = delete; // Comparison of abstract types is not possible.
  virtual bool operator!=(const Queue<Data> &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Head() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data & Head() = 0; // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data HeadNDequeue() = 0; // (concrete function must throw std::length_error when empty)
  virtual void Enqueue(const Data &) noexcept = 0; // Copy of the value

  virtual void Enqueue(Data &&) noexcept = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
