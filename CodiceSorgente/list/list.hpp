
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */
#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */
namespace lasd {

/* ************************************************************************** */
template <typename Data>
class List:public virtual ClearableContainer,public virtual LinearContainer<Data>,public virtual DictionaryContainer<Data> {
protected :
      using Container::size;
      using TestableContainer<Data>::Exists;
struct Node
{
    // Data
    Data element;
    struct Node *link = nullptr;
    /* ********************************************************************** */

    // Specific constructors
    // ...
    inline Node() = default;
    inline Node(const Data& newelem,struct Node *nextval=nullptr): element(newelem),link(nextval){}
    inline Node(Data &&,struct Node *nextval=nullptr) noexcept;



    /* ********************************************************************** */

    // Copy constructor
    inline Node(const Node & nod) : element(nod.element),link(nod.link){}

    // Move constructor
    inline Node(Node&& nod) noexcept;

    /* ********************************************************************** */

    ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    inline bool operator!=(const Node &) const noexcept;
    /* ********************************************************************** */
  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  List()=default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &other) noexcept; // A list obtained from a TraversableContainer
  List(MappableContainer<Data> && other) noexcept; // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data>&) noexcept;

  // Move constructor
  List(List<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List<Data>& operator=(const List<Data> &) noexcept;

  // Move assignment
  List<Data> &operator=(List<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data>&) const noexcept;
  bool operator!=(const List<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &); // Copy of the value
  void InsertAtFront(Data &&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)
  void InsertAtBack(const Data &); // Copy of the value
  void InsertAtBack(Data &&); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Copy of the value
  bool Insert(Data &&) override; // Move of the value
  bool Remove(const Data &) override;


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const unsigned long) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data &operator[](const unsigned long) override;  // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data &Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data &Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data &Back() override;             // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  //Traverse fun se non ti ricordi prendeva un const Data &

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

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

private:
  
protected:
/*Auxiliary Functions*/

  void PreOrderTraverse(TraverseFun,Node *) const;
  void PostOrderTraverse(TraverseFun, Node *) const;

  void PreOrderMap(MapFun,Node *);
  void PostOrderMap(MapFun,Node *);

};

/* ************************************************************************** */

}

#include"list.cpp"
#endif
