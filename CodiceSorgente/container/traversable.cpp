
namespace lasd {

/* ************************************************************************** */

// Specific member functions of TraversableContainer

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
    this->Traverse(
        [foldFunction, &accumulator](const Data& data) -> void {
            accumulator = foldFunction(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;
    this->Traverse(
        [&data, &exists](const Data& dat) -> void {
            if (data == dat) {exists = true;}
        }
    );
    return exists;
}

/* ************************************************************************** */

// Specific member functions of PreOrderTraversableContainer

template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
    this->PreOrderTraverse(
        [foldFunction, &accumulator](const Data& data) -> void {
            accumulator = foldFunction(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun travFunction) const {
    this->PreOrderTraverse(travFunction);
}

/* ************************************************************************** */

// Specific member functions of PostOrderTraversableContainer

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
    this->PostOrderTraverse(
        [foldFunction, &accumulator](const Data& data) -> void {
            accumulator = foldFunction(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun travFunction) const {
    this->PostOrderTraverse(travFunction);
}

/* ************************************************************************** */

// Specific member functions of InOrderTraversableContainer

template <typename Data>
template <typename Accumulator>
inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
    this->InOrderTraverse(
        [foldFunction, &accumulator](const Data& data) -> void {
            accumulator = foldFunction(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun travFunction) const {
    this->InOrderTraverse(travFunction);
}

/* ************************************************************************** */

// Specific member functions of BreadthTraversableContainer

template <typename Data>
template <typename Accumulator>
inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
    this->BreadthTraverse(
        [foldFunction, &accumulator](const Data& data) -> void {
            accumulator = foldFunction(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun travFunction) const {
    this->BreadthTraverse(travFunction);
}

}
