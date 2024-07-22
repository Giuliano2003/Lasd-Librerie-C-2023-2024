
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr:public virtual HashTable<Data> {

protected:
  using HashTable<Data>::TABLESIZE;

  using Container::size;

private:

  lasd::Vector<Data>table;

  lasd::Vector<int>support;// vettore di supporto per memorizzare celle libere e non

  unsigned long hop;


public:

  // Default constructor
  HashTableOpnAdr(){
    table.Resize(this->TABLESIZE);
    support.Resize(this->TABLESIZE);
    hop = (TABLESIZE / 4) + 1; 
  }

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const unsigned long); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(unsigned long, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> &&);// A hash table obtained from a MappableContainer
  HashTableOpnAdr(unsigned long, MappableContainer<Data> &&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data> &ht);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data> &&ht);

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr<Data> &operator=(const HashTableOpnAdr<Data> &ht) noexcept;

  // Move assignment
  HashTableOpnAdr<Data> &operator=(HashTableOpnAdr<Data> &&ht) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data> &ht) const noexcept;
  bool operator!=(const HashTableOpnAdr<Data> &ht) const noexcept;

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

  void Resize(unsigned long) noexcept override; // Resize the hashtable to a given size  // stare attento

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() noexcept override; // Override Container member

protected:

  // Auxiliary member functions

  unsigned long HashKeyC(unsigned long) noexcept; //per indice di hop

  unsigned long Find(unsigned long) noexcept; // cerca la prima cella virtualmente disponibile

  unsigned long FindEmpty(unsigned long,const Data &) const noexcept; // cerca la prima cella fisicamente disponibile
  // type Remove(argument) specifiers; 
  bool isPrime(unsigned long ) const noexcept;

  void init(unsigned long) noexcept;

};



/* ************************************************************************** */

}


#include "htopnadr.cpp"

#endif
