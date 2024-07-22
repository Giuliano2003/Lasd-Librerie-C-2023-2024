
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk:public virtual lasd::MutableBinaryTree<Data> {
  // Must extend MutableBinaryTree<Data>

protected:
 

  using Container::size;
  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

  
  struct NodeLnk:public virtual lasd::MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

    friend class BinaryTreeLnk<Data>;

    //friend class lasd::BST<Data>;
    Data element;

    NodeLnk *right = nullptr;

    NodeLnk *left = nullptr;

  public:
    // Copy Constructor
    NodeLnk() = default;

    NodeLnk(const Data &value, NodeLnk *right_child = nullptr, NodeLnk *left_child = nullptr) : element(value), right(right_child), left(left_child) {}

    // Move Constructor
    NodeLnk(Data &&value, NodeLnk *right_child = nullptr, NodeLnk *left_child = nullptr) : element(std::move(value)), right(right_child), left(left_child) {}

    // Destructor
    virtual ~NodeLnk() = default;

    const Data &Element() const noexcept override { return element; }
    Data &Element() noexcept override { return element; }

    
    MutableNode& LeftChild()  {
      if (this->left != nullptr)
        return *this->left;
      throw std::out_of_range("Figlio Inesistente !");
    }

    MutableNode& RightChild()  {
      if (this->right != nullptr)
        return *this->right;
      throw std::out_of_range("Figlio Inesistente !");
    }

    bool HasLeftChild() const noexcept override{
        return(this->left != nullptr);
    }

    bool HasRightChild() const noexcept override{
        return(this->right != nullptr);
    }

    const Node& LeftChild() const override{
        if(this->left != nullptr)
          return *this->left;
        throw std::out_of_range("Figlio Inesistente !");
    }

    const Node& RightChild() const override
    {
      if (this->right != nullptr)
        return *this->right;
      throw std::out_of_range("Figlio Inesistente !");
    }
  };
protected:


  NodeLnk* CloneTreeC(NodeLnk *,NodeLnk*) noexcept;
  void CleanTree(NodeLnk *) noexcept;
  void buildComplete(unsigned long,NodeLnk *,const std::vector<Data> &) noexcept;


public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &) noexcept; // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data> &&); // A binary tree obtained from a MappableContainer
  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data> &) noexcept;

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk<Data> &operator=(const BinaryTreeLnk<Data> &);

  // Move assignment
  BinaryTreeLnk<Data> &operator=(BinaryTreeLnk<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data> &) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Node& Root() const override{
      if(this->root == nullptr)
        throw std::length_error("L'albero è vuoto !");
      return *this->root;
  } // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode& Root() override
  {
    if (this->root == nullptr)
      throw std::length_error("L'albero è vuoto !");
    return *this->root;
  } // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member


  protected:
    NodeLnk *root = nullptr;
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
