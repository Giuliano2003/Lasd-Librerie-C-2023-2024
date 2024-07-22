#include<iostream>
#include<stdexcept>
#include"queuelst.hpp"

using namespace std;
namespace lasd {
    template <typename Data>
    lasd::QueueLst<Data>::QueueLst(const QueueLst<Data> &other) noexcept : List<Data>(other)
    { }

    template <typename Data>
    lasd::QueueLst<Data>::QueueLst(QueueLst<Data> &&other) noexcept : List<Data>(std::move(other))
    {
        other.Clear();
    }
    template <typename Data>
    lasd::QueueLst<Data>::QueueLst(const TraversableContainer<Data> &other) noexcept : List<Data>(other)
    {
    }
    template <typename Data>
    lasd::QueueLst<Data>::QueueLst(MappableContainer<Data> &&other) noexcept : List<Data>(std::move(other))
    {
    }
    template <typename Data>
    QueueLst<Data>& lasd::QueueLst<Data>::operator=(const QueueLst<Data> &other) noexcept
    {
        List<Data>::operator=(other);
        return *this;
    }

    template <typename Data>
    QueueLst<Data>& lasd::QueueLst<Data>::operator=(QueueLst<Data> &&other) noexcept
    {
        List<Data>::operator=(std::move(other));
        return *this;
    }

    template <typename Data>
    bool lasd::QueueLst<Data>::operator==(const QueueLst<Data> &other)const noexcept
    {
        return List<Data>::operator==(other);
    }

    template <typename Data>
    bool lasd::QueueLst<Data>::operator!=(const QueueLst<Data> &other)const noexcept
    {
        return List<Data>::operator!=(other);
    }

    template <typename Data>
    void lasd::QueueLst<Data>::Enqueue(const Data &key) noexcept
    {
        List<Data>::InsertAtBack(key);
    }
    template <typename Data>
    void lasd::QueueLst<Data>::Enqueue(Data &&key) noexcept
    {
        List<Data>::InsertAtBack(std::move(key));
    }
    template <typename Data>
    void lasd::QueueLst<Data>::Dequeue()
    {
        List<Data>::RemoveFromFront();
    }
    template <typename Data>
    Data lasd::QueueLst<Data>::HeadNDequeue()
    {
        Data to_return = this->Head();
        this->Dequeue();
        return to_return;
    }
    template <typename Data>
    const Data & lasd::QueueLst<Data>::Head() const
    {
        return List<Data>::Front();
    }
    template <typename Data>
    Data & lasd::QueueLst<Data>::Head()
    {
        return List<Data>::Front();
    }
    template <typename Data>
    lasd::QueueLst<Data>::~QueueLst()
    {
        Clear(); // dealloco tutti i nodi
    }
};


