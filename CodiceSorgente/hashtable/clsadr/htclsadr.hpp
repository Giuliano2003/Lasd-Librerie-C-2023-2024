
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include"../../vector/vector.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr:public virtual HashTable<Data> {
  // Must extend HashTable<Data>

private:

    lasd::Vector<lasd::BST<Data>> v;

protected:

  using HashTable<Data>::TABLESIZE;

  using Container::size;



public:

  // Default constructor
  HashTableClsAdr(){
      v.Resize(TABLESIZE);
  }

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const unsigned long &) noexcept; // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data> &) noexcept; // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const unsigned long &, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(const unsigned long &,MappableContainer<Data> &&) noexcept; // A hash table obtained from a MappableContainer
  HashTableClsAdr(MappableContainer<Data> &&) noexcept; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data> &ht);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data> &&ht);

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr(){
    Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr<Data>& operator=(const HashTableClsAdr<Data> &) noexcept;

  // Move assignment
  HashTableClsAdr<Data> &operator=(HashTableClsAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data> &) const noexcept;
  bool operator!=(const HashTableClsAdr<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)


  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(unsigned long) override; // Resize the hashtable to a given size
  
  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() noexcept override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
