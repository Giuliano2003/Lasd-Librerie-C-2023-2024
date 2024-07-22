
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec:public virtual MutableBinaryTree<Data> {
  // Must extend MutableBinaryTree<Data>

protected:
  using BinaryTree<Data>::size;

  using typename BinaryTree<Data>::Node;
  
  using typename MutableBinaryTree<Data>::MutableNode;
  

  struct NodeVec : public virtual lasd::MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode


  friend class BinaryTreeVec<Data>;

  private:

    // ...

  protected:

    // ...

  public:

    Data element;

    unsigned long indexNode;

    Vector<NodeVec *> *vectorNode = nullptr; 

    NodeVec() = default;

    NodeVec(const Data &, unsigned long,Vector<NodeVec*> *);

    NodeVec(Data &, unsigned long,Vector<NodeVec*>*);

    virtual ~NodeVec() = default;

    Data &Element() noexcept override{
      return this->element;
    }             // Mutable access to the element (concrete function should not throw exceptions)
    const Data &Element() const noexcept override{
      return this->element;
    }; // Immutable access to the element (concrete function should not throw exceptions)

    bool HasLeftChild() const noexcept override
    {
      return (indexNode * 2 + 1) <= (this->vectorNode->Size() - 1);
    }

    bool HasRightChild() const noexcept override
    {
      return (indexNode * 2 + 2) <= (this->vectorNode->Size() - 1);
    }

    MutableNode &LeftChild() override
    {
      if (!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

      return *(this->vectorNode->operator[](indexNode * 2 + 1));
    }

    MutableNode &RightChild() override
    {
      if (!HasRightChild())
        throw std::out_of_range("Access to an empty child.");

      return *(this->vectorNode->operator[](indexNode * 2 + 2));
    }

    const Node &LeftChild() const override
    {
      if (!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

      return *(this->vectorNode->operator[](indexNode * 2 + 1));
    }

    const Node &RightChild() const override
    {
      if (!HasRightChild())
        throw std::out_of_range("Access to an empty child.");
      return *(this->vectorNode->operator[](indexNode * 2 + 2));
    }
  };

private:
  Vector<NodeVec *> *treevector = nullptr; // un puntatore ad un vettore di nodi

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&) noexcept; // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data> &&); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data> &) noexcept;

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data> &) noexcept;

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data> &) const noexcept;
  bool operator!=(const BinaryTreeVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Node &Root() const override
  {
      if(size != 0)
        return *(this->treevector->operator[](0));
      throw std::length_error("Albero Vuoto !");
  } // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode &Root() override
  {
    if (size != 0)
      return *(this->treevector->operator[](0));
    throw std::length_error("Albero Vuoto !");
  } // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  using typename MappableContainer<Data>::MapFun;

  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
