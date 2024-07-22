
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>


/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  unsigned long operator()(const Data &) const noexcept = 0; // (concrete function should not throw exceptions)
  //Questo operatore mi tira fuori l'hash di Encode

};

/* ************************************************************************** */

template <typename Data>
class HashTable:public virtual lasd::ResizableContainer,public virtual lasd::DictionaryContainer<Data> {
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  unsigned long acst = 1;
  unsigned long bcst = 0;

  unsigned long prime =  1000000016531;
  std::default_random_engine eng = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<unsigned long> dista = std::uniform_int_distribution<unsigned long>(1,prime-1);
  std::uniform_int_distribution<unsigned long> distb = std::uniform_int_distribution<unsigned long>(0, prime - 1);


  static const Hashable<Data> encode;

  unsigned long TABLESIZE = 128; // default
  //adesso devo usare il generatore di numeri random

  HashTable(){
      acst = dista(eng);
      bcst = distb(eng);
      // queste due costanti mi servono per la funzione di hash secondaria che mi mappa per gli indice del vettore
  }

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable<Data>& operator=(const HashTable<Data>&) noexcept = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable<Data> &operator=(HashTable<Data> &&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable<Data> &) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable<Data> &) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  unsigned long HashKey(const unsigned long x) const noexcept{
    return ((((acst*x)+bcst) % prime) % TABLESIZE);  
  };

  unsigned long HashKey(const Data &dat) const noexcept
  {
    return HashKey(encode(dat));
  };
  // posso già farla qui

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
