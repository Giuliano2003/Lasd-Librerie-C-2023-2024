#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack:public virtual ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  Stack<Data> &operator=(const Stack<Data> &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Stack<Data> &operator=(Stack<Data> &&) noexcept = delete; // Move assignment of abstract types is not possible.

  bool operator==(const Stack<Data> &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Stack<Data> &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Top() const  = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data & Top() = 0; // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Pop()= 0; // (concrete function must throw std::length_error when empty)
  virtual Data TopNPop() = 0; // (concrete function must throw std::length_error when empty)
  virtual void Push(const Data &) noexcept = 0; // Copy of the value
  virtual void Push(Data &&) noexcept = 0; // Move of the value


};

/* ************************************************************************** */

}

#endif
