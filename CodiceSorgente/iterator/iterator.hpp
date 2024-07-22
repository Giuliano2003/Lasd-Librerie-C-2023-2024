
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  Iterator<Data> &operator=(const Iterator<Data> &) = delete;
  Iterator<Data> &operator=(Iterator<Data> &&) = delete;

  // Comparison operators are disabled for abstract types
  bool operator==(const Iterator<Data> &) const noexcept = delete;
  bool operator!=(const Iterator<Data> &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator*() const = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator:public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  using Iterator<Data>::operator*;

public:

  // Destructor
  virtual ~MutableIterator()= default;

  /* ************************************************************************ */

  MutableIterator<Data> &operator=(const MutableIterator<Data> &) = delete;
  MutableIterator<Data> &operator=(MutableIterator<Data> &&) = delete;

  // Comparison operators are disabled for abstract types
  bool operator==(const MutableIterator<Data> &) const noexcept = delete;
  bool operator!=(const MutableIterator<Data> &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator:public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:
  virtual ~ForwardIterator() = default;

  // Copy and move assignment are disabled for abstract types
  ForwardIterator<Data> &operator=(const ForwardIterator<Data> &) = delete;
  ForwardIterator<Data> &operator=(ForwardIterator<Data> &&) = delete;

  // Comparison operators are disabled for abstract types
  bool operator==(const ForwardIterator<Data> &) const noexcept = delete;
  bool operator!=(const ForwardIterator<Data> &) const noexcept = delete;

  // Specific member functions

  // Increment operator to move the iterator forward
  virtual ForwardIterator<Data> &operator++() = 0; // The concrete function must throw std::out_of_range when terminated
};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator:public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  ResettableIterator<Data> &operator=(const ResettableIterator<Data> &) = delete;
  ResettableIterator<Data> &operator=(ResettableIterator<Data> &&) = delete;

  // Comparison operators are disabled for abstract types
  bool operator==(const ResettableIterator<Data> &) const noexcept = delete;
  bool operator!=(const ResettableIterator<Data> &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
