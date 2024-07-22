#include<iostream>
#include<stdexcept>
#include<string.h>
#include"stacklst.hpp"
namespace lasd {
    template <typename Data>
    lasd::StackLst<Data>::StackLst(const StackLst<Data> &other) noexcept:List<Data>::List(other)
    {}
    template <typename Data>
    lasd::StackLst<Data>::StackLst(StackLst<Data> &&other) noexcept:List<Data>::List(std::move(other))
    {
        other.Clear();
    }
    template <typename Data>
    lasd::StackLst<Data>::StackLst(const TraversableContainer<Data> &other) noexcept : List<Data>::List(other)
    {
    }
    template <typename Data>
    lasd::StackLst<Data>::StackLst(MappableContainer<Data> &&other) noexcept : List<Data>::List(std::move(other))
    {
    }
    template <typename Data>
    StackLst<Data> &lasd::StackLst<Data>::operator=(const StackLst<Data> &other) noexcept
    {
        List<Data>::operator=(other);
        return *this;
    }
    template <typename Data>
    StackLst<Data> &lasd::StackLst<Data>::operator=(StackLst<Data> &&other) noexcept
    {
        List<Data>::operator=(std::move(other));
        return *this;
    }
    template <typename Data>
    bool lasd::StackLst<Data>::operator==(const StackLst<Data> &other) const noexcept
    {
        return List<Data>::operator==(other);
    }
    template <typename Data>
    bool lasd::StackLst<Data>::operator!=(const StackLst<Data> &other) const noexcept
    {
        return List<Data>::operator!=(other);
    }
    template<typename Data>
    void lasd::StackLst<Data>::Push(const Data &key) noexcept{
        lasd::List<Data>::InsertAtFront(key);
    }
    template <typename Data>
    void lasd::StackLst<Data>::Push(Data &&key) noexcept
    {
        lasd::List<Data>::InsertAtFront(std::move(key));
    }
    template <typename Data>
    const Data & lasd::StackLst<Data>::Top() const {
        return lasd::List<Data>::Front();
    }
    template <typename Data>
    Data & lasd::StackLst<Data>::Top()
    {
        return lasd::List<Data>::Front();
    }
    template <typename Data>
    void lasd::StackLst<Data>::Pop()
    {
        lasd::List<Data>::RemoveFromFront();
    }
    template <typename Data>
    Data lasd::StackLst<Data>::TopNPop()
    {
        Data to_return = lasd::List<Data>::Front();
        lasd::List<Data>::RemoveFromFront();
        return to_return;
    }
    template <typename Data>
    lasd::StackLst<Data>::~StackLst()
    {
        Clear();// per deallocare tutti i nodi
    }
}
