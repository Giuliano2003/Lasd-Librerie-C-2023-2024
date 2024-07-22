
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"


#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
//#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree:public virtual PreOrderTraversableContainer<Data>,public virtual PostOrderTraversableContainer<Data>,
public virtual InOrderTraversableContainer<Data>,public virtual BreadthTraversableContainer<Data> { 
private:

  // ...

protected:

  // ...

public:

  

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node &) const noexcept; // Comparison of abstract types is possible, but is not visible.
    inline bool operator!=(const Node &) const noexcept; // Comparison of abstract types is possible, but is not visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node& operator=(Node &&) = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const  Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  BinaryTree<Data> &operator=(const BinaryTree<Data> &) = delete;
  BinaryTree<Data> &operator=(BinaryTree<Data> &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data> &) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree<Data> &) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const  override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  void InOrderTraverse(TraverseFun) const  override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  void BreadthTraverse(TraverseFun) const  override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions, if necessary!
  void PreOrderTraverse(TraverseFun,const Node &) const;
  void PostOrderTraverse(TraverseFun,const Node &) const;
  void InOrderTraverse(TraverseFun,const Node &) const;
  void BreadthTraverse(TraverseFun,const Node &) const;
};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree: 
public virtual ClearableContainer, 
public virtual BinaryTree<Data>, 
public virtual PreOrderMappableContainer<Data>, 
public virtual PostOrderMappableContainer<Data>, 
public virtual InOrderMappableContainer<Data>, 
public virtual BreadthMappableContainer<Data>
{
  // Must extend ClearableContainer,
  //             BinaryTree<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>,
  //             InOrderMappableContainer<Data>,
  //             BreadthMappableContainer<Data>

private:

  // ...

protected:


public:

  using BinaryTree<Data>::Root;

  

  struct MutableNode:public virtual lasd::BinaryTree<Data>::Node {
    
    // Must extend Node

    using BinaryTree<Data>::Node::LeftChild;
    using BinaryTree<Data>::Node::RightChild;
    using BinaryTree<Data>::Node::Element;
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    MutableNode &operator=(MutableNode &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode &operator=(MutableNode &&) = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  MutableBinaryTree<Data> &operator=(const MutableBinaryTree<Data> &) = delete;
  MutableBinaryTree<Data> &operator=(MutableBinaryTree<Data> &&) = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode&  Root() =0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  void InOrderMap(MapFun) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member



protected:

  // Auxiliary functions, if necessary!
  void PreOrderMap(MapFun, MutableNode &);
  void PostOrderMap(MapFun, MutableNode &);
  void InOrderMap(MapFun, MutableNode &);
  void BreadthMap(MapFun,MutableNode *);
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator:public virtual ForwardIterator<Data>,public virtual ResettableIterator<Data> {
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:
  
protected:
  lasd::StackVec<const typename lasd::BinaryTree<Data>::Node *> stklst;

  typename lasd::BinaryTree<Data>::Node const *first = nullptr;

public:
  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data> &) noexcept;

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator<Data> &operator=(const BTPreOrderIterator<Data> &) noexcept;

  // Move assignment
  BTPreOrderIterator<Data> &operator=(BTPreOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data> &) const noexcept;

  // Move assignment
  bool operator!=(const BTPreOrderIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data &operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> &operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator:public virtual MutableIterator<Data>,public virtual BTPreOrderIterator<Data>
{
  // Must extend MutableIterator<Data>,
  //             BTPreOrderIterator<Data>

private:
  // ...

protected:
  using BTPreOrderIterator<Data>::stklst;

public:
  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data> &mbt) : BTPreOrderIterator<Data>(mbt)
  {}
  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data> &it) noexcept:BTPreOrderIterator<Data>(it){}

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data> &&it) noexcept : BTPreOrderIterator<Data>(std::move(it)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator(){
    stklst.Clear();
  };

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator<Data> &it){
      BTPreOrderIterator<Data>::operator=(it);
      return *this;
  }

  // Move assignment
  BTPreOrderMutableIterator &operator=(BTPreOrderMutableIterator<Data> &&it)
  {
    BTPreOrderIterator<Data>::operator=(std::move(it));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(BTPreOrderMutableIterator<Data> &it) const noexcept{
    return BTPreOrderIterator<Data>::operator==(it);
  }
  bool operator!=(BTPreOrderMutableIterator<Data> &it) const noexcept{
    return BTPreOrderIterator<Data>::operator==(std::move(it));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override {
    if(!stklst.Empty())
    {
        return const_cast<Data &>(stklst.Top()->Element());
    } else {
      throw std::out_of_range("L'iteratore è terminato");
    }
  }; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,virtual public ResettableIterator<Data>
{ // Must extend ForwardIterator<Data>

private:

protected:
  void getMostLeftLeaf(const struct BinaryTree<Data>::Node &);
  const struct BinaryTree<Data>::Node *current = nullptr;
  const struct BinaryTree<Data>::Node *root = nullptr;
  StackVec<struct BinaryTree<Data>::Node const *> stk;

public:
  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator &);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator &operator=(const BTPostOrderIterator &);

  // Move assignment
  BTPostOrderIterator &operator=(BTPostOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator &) const noexcept;
  bool operator!=(const BTPostOrderIterator &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data &operator*() const  override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> &operator++() override; // (throw std::out_of_range when terminated)

  void Reset() noexcept override;
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator:public virtual MutableIterator<Data>,public virtual BTPostOrderIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTPostOrderIterator<Data>

private:

  // ...

protected:

  using BTPostOrderIterator<Data>::stk;

public:
   BTPostOrderMutableIterator(MutableBinaryTree<Data> &mbt) : BTPostOrderIterator<Data>(mbt)
  {
  }
  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data> &it) noexcept : BTPostOrderIterator<Data>(it) {}

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data> &&it) noexcept : BTPostOrderIterator<Data>(std::move(it)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator()
  {
    stk.Clear();
  };

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator &operator=(BTPostOrderMutableIterator<Data> &it)
  {
    BTPostOrderIterator<Data>::operator=(it);
    return *this;
  }

  // Move assignment
  BTPostOrderMutableIterator &operator=(BTPostOrderMutableIterator<Data> &&it)
  {
    BTPostOrderIterator<Data>::operator=(std::move(it));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(BTPostOrderMutableIterator<Data> &it) const noexcept
  {
    return BTPostOrderIterator<Data>::operator==(it);
  }
  bool operator!=(BTPostOrderMutableIterator<Data> &it) const noexcept
  {
    return BTPostOrderIterator<Data>::operator==(std::move(it));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data &operator*() override
  {
    if (!stk.Empty())
    {
      return const_cast<Data &>(stk.Top()->Element());
    }
    else
    {
      throw std::out_of_range("L'iteratore è terminato");
    }
  }; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator:public virtual ForwardIterator<Data>,public virtual ResettableIterator<Data> {
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:


protected:
  //using typename BinaryTree<Data>::Node;
  lasd::StackLst<const typename lasd::BinaryTree<Data>::Node *> stklst;
  typename lasd::BinaryTree<Data>::Node const  *first = nullptr;
  void searchLeftMostNode(const typename lasd::BinaryTree<Data>::Node &);

public:
  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data> &) noexcept;

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator<Data> &operator=(const BTInOrderIterator<Data> &) noexcept;

  // Move assignment
  BTInOrderIterator<Data> &operator=(BTInOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data> &) const noexcept;

  // Move assignment
  bool operator!=(const BTInOrderIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data &operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator<Data> &operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator:public virtual MutableIterator<Data>,public virtual BTInOrderIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTInOrderIterator<Data>

private:

  // ...

protected:

  using BTInOrderIterator<Data>::stklst;

public:
  BTInOrderMutableIterator(MutableBinaryTree<Data> &mbt) : BTInOrderIterator<Data>(mbt)
  {
  }
  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data> &it) noexcept : BTInOrderIterator<Data>(it) {}

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data> &&it) noexcept : BTInOrderIterator<Data>(std::move(it)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator()
  {
    stklst.Clear();
  };

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator &operator=(BTInOrderMutableIterator<Data> &it)
  {
    BTInOrderIterator<Data>::operator=(it);
    return *this;
  }

  // Move assignment
  BTInOrderMutableIterator &operator=(BTInOrderMutableIterator<Data> &&it)
  {
    BTInOrderIterator<Data>::operator=(std::move(it));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(BTInOrderMutableIterator<Data> &it) const noexcept
  {
    return BTInOrderIterator<Data>::operator==(it);
  }
  bool operator!=(BTInOrderMutableIterator<Data> &it) const noexcept
  {
    return BTInOrderIterator<Data>::operator==(std::move(it));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data &operator*() override
  {
    if (!stklst.Empty())
    {
      return const_cast<Data &>(stklst.Top()->Element());
    }
    else
    {
      throw std::out_of_range("L'iteratore è terminato");
    }
  }; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator:public virtual ForwardIterator<Data>,public virtual ResettableIterator<Data> {
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

protected:
  //using typename BinaryTree<Data>::Node;
  lasd::QueueVec<const typename lasd::BinaryTree<Data>::Node *> queuelst;
  typename lasd::BinaryTree<Data>::Node const * first = nullptr;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data> &) noexcept;

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator<Data>& operator=(const BTBreadthIterator<Data> &) noexcept;

  // Move assignment
  BTBreadthIterator<Data>& operator=(BTBreadthIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data> &) const noexcept;

  // Move assignment
  bool operator!=(const BTBreadthIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator:public virtual MutableIterator<Data>,public virtual BTBreadthIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTBreadthIterator<Data>

private:

  // ...

protected:

  using BTBreadthIterator<Data>::queuelst;

public:
  BTBreadthMutableIterator(MutableBinaryTree<Data> &mbt) : BTBreadthIterator<Data>(mbt)
  {
  }
  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data> &it) noexcept : BTBreadthIterator<Data>(it) {}

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data> &&it) noexcept : BTBreadthIterator<Data>(std::move(it)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator()
  {
    queuelst.Clear();
  };

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator &operator=(BTBreadthMutableIterator<Data> &it)
  {
    BTBreadthIterator<Data>::operator=(it);
    return *this;
  }

  // Move assignment
  BTBreadthMutableIterator &operator=(BTBreadthMutableIterator<Data> &&it)
  {
    BTBreadthIterator<Data>::operator=(std::move(it));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(BTBreadthMutableIterator<Data> &it) const noexcept
  {
    return BTBreadthIterator<Data>::operator==(it);
  }
  bool operator!=(BTBreadthMutableIterator<Data> &it) const noexcept
  {
    return BTBreadthIterator<Data>::operator==(std::move(it));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data &operator*() override
  {
    if (!queuelst.Empty())
    {
      return const_cast<Data &>(queuelst.Head()->Element());
    }
    else
    {
      throw std::out_of_range("L'iteratore è terminato");
    }
  }; 
};

/* ************************************************************************** */

};

#include "binarytree.cpp"

#endif
