
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"
//#include"../container/dictionary.hpp"
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public lasd::ClearableContainer, virtual public lasd::DictionaryContainer<Data>,
virtual public BinaryTree<Data>, virtual public BinaryTreeLnk<Data>
{
  // Must extend ClearableContainer,
  //             DictionaryContainer<Data>,
  //             BinaryTree<Data>,
  //             BinaryTreeLnk<Data>


private:

  // ...

protected:
  

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using typename BinaryTree<Data>::Node;
  using Container::Size;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data>&) noexcept; // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data> &&); // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data> &) noexcept;

  // Move constructor
  BST(BST<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BST();

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>&operator=(const BST<Data> &) noexcept;

  // Move assignment
  BST<Data> &operator=(BST<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST<Data> &) const noexcept;
  bool operator!=(const BST<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  virtual const Data& Min() const{
    if (this->root == nullptr)
    {
      throw std::length_error("L'albero è vuoto !");
    }
    Data &Min = this->DetachMin(this->root);
    return Min;
  }
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const{
    if (this->root == nullptr)
    {
      throw std::length_error("L'albero è vuoto !");
    }
    Data &Max = this->DetachMax(this->root);
    return Max;
  }
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data &) const ; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data &); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data &) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data &); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const Node& Root() const override{
    if(this->root != nullptr)
    {
        return *this->root;
    }
    throw std::length_error("Albero vuoto !");
  } // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &dat) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear(); // Override ClearableContainer member

protected:
  

  // Auxiliary functions, if necessary!

  NodeLnk* DataNDelete(NodeLnk*) noexcept;

  // type Detach(argument) specifiers;

  Data& DetachMin(NodeLnk*) const noexcept;
  Data& DetachMax(NodeLnk *) const noexcept;

  NodeLnk* Skip2Left(NodeLnk*) noexcept;
  NodeLnk* Skip2Right(NodeLnk*) noexcept;

  const NodeLnk* FindPointerToMin(const NodeLnk *) const noexcept; // Both mutable & unmutable versions
  NodeLnk *FindPointerToMin(NodeLnk *) noexcept; // Both mutable & unmutable versions

  const NodeLnk* FindPointerToMax(const NodeLnk *) const noexcept; // Both mutable & unmutable versions
  NodeLnk *FindPointerToMax(NodeLnk *) noexcept;


  const NodeLnk* FindPointerTo(const NodeLnk *,const Data &) const noexcept; // Both mutable & unmutable versions
  NodeLnk *FindPointerTo(NodeLnk *, const Data &) noexcept; // Both mutable & unmutable versions

  const NodeLnk *FindPointerToPredecessor(const NodeLnk *, const Data &, const NodeLnk *)const noexcept;
  NodeLnk *FindPointerToPredecessor(NodeLnk *, const Data &, NodeLnk *) noexcept;// Both mutable & unmutable versions


  const NodeLnk* FindPointerToSuccessor(const NodeLnk*,const Data&,const NodeLnk*) const noexcept; // Both mutable & unmutable versions
  NodeLnk *FindPointerToSuccessor(NodeLnk *,const Data&,NodeLnk*) noexcept; // Both mutable & unmutable versions

  NodeLnk* InsertHelp(NodeLnk *, const Data &);
  NodeLnk* InsertHelp(NodeLnk *,Data &&);

  NodeLnk* RemoveData(NodeLnk*,const Data&);

  Data& GetDeleteMin(NodeLnk*,NodeLnk*,Data&);
};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
