
namespace lasd {

/* ************************************************************************** */

// Specific member functions of PreOrderMappableContainer

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun mapFunction) {
    this->PreOrderMap(mapFunction);
}

/* ************************************************************************** */

// Specific member functions of PostOrderMappableContainer

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun mapFunction) {
    this->PostOrderMap(mapFunction);
}

/* ************************************************************************** */

// Specific member functions of InOrderMappableContainer

template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun mapFunction) {
    this->InOrderMap(mapFunction);
}

/* ************************************************************************** */

// Specific member functions of BreadthMappableContainer

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun mapFunction) {
    this->BreadthMap(mapFunction);
}

/* ************************************************************************** */

}
