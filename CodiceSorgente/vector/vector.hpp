#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../container/container.hpp"
#include "../container/linear.hpp"

namespace lasd
{

  template <typename Data>
  class Vector :public virtual ResizableContainer,public virtual LinearContainer<Data>
  {
    // Must extend LinearContainer<Data>
  private:
  public:
    // Default constructor
    Vector() = default;
    // Specific constructor
    Vector(const unsigned long initialSize);// A vector with a given initial dimension
    Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer
  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&& ) noexcept;
  /* ************************************************************************ */
  virtual ~Vector() noexcept;

  // Copy assignment
  Vector<Data>&operator=(const Vector<Data> &);

  // Move assignment
  Vector<Data>& operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const Vector<Data> &)const noexcept;
  bool operator!=(const Vector<Data> &)const  noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const unsigned long) override; // Override ResizableContainer member

  /* ************************************************************************ */

   // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long ) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  //const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  //Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  //const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  //Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
 
  protected:
    Data *elem = nullptr;
    using Container::size;
};

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector:public virtual Vector<Data>,public virtual SortableLinearContainer<Data>
  {
    // Must extend Vector<Data>,
    //             SortableLinearContainer<Data>

  private:
  protected:
    using Container::size;
  public:
    
    // Default constructor
    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    SortableVector(const unsigned long) noexcept; // A vector with a given initial dimension
    SortableVector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
    SortableVector(MappableContainer<Data>&&) noexcept; // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    SortableVector(const SortableVector<Data> &)noexcept;

    // Move constructor
    SortableVector(SortableVector<Data> &&)noexcept;

    /* ************************************************************************ */

    // Destructor
    ~SortableVector()=default;

    /* ************************************************************************ */

    // Copy assignment
    SortableVector<Data>& operator=(const SortableVector<Data> &) noexcept;

    // Move assignment
    SortableVector<Data>& operator=(SortableVector<Data> &&) noexcept;

  };

  /* ************************************************************************** */

};
#include"vector.cpp"
#endif
