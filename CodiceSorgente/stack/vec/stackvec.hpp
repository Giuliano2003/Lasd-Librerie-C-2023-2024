
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{
template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data>
{
  private:
    // ...

  protected:
  
    unsigned long i = 0;
    using Vector<Data>::size;
    using Vector<Data>::elem;

    // ...

  public:
    // Default constructor
    StackVec()=default;

    /* ************************************************************************ */

    // Specific constructor
    StackVec(const TraversableContainer<Data> &c) : Vector<Data>(c){
      this->i = c.Size();
    }; // A stack obtained from a TraversableContainer
    StackVec(MappableContainer<Data> &&c) : Vector<Data>(c){
      this->i = c.Size();
    };         // A stack obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    StackVec(const StackVec<Data> &stk) : Vector<Data>(stk), i(stk.i){};

    // Move constructor
    StackVec(StackVec<Data> &&stk) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~StackVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    inline StackVec<Data> &operator=(const StackVec<Data> &);

    // Move assignment
    inline StackVec<Data> &operator=(StackVec<Data> &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const StackVec<Data> &) const noexcept;
    bool operator!=(const StackVec<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Stack)

    const Data &Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
    Data &Top() override;             // Override Stack member (non-mutable version; must throw std::length_error when empty)
    void Pop() override;              // Override Stack member (must throw std::length_error when empty)
    Data TopNPop() override;          // Override Stack member (must throw std::length_error when empty)
    void Push(const Data &) noexcept override; // Override Stack member (copy of the value)
    void Push(Data &&) noexcept override;      // Override Stack member (move of the value)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    inline bool Empty() const noexcept override; // Override Container member

    inline unsigned long Size() const noexcept override; // Override Container member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() noexcept override; // Override ClearableContainer member

  protected:
    // Auxiliary functions, if necessary!

    void Expand();
    void Reduce();
};

  /* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
