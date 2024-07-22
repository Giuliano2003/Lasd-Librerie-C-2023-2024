#include<iostream>
#include<algorithm>
using namespace std;
#include <stdexcept>
#include"vector.hpp"
namespace lasd
{
    template<typename Data>
    lasd::Vector<Data>::Vector(const unsigned long initialSize)
    {
        this->size=initialSize;
        this->elem=new Data[initialSize] {};
    }
    template <typename Data>
    lasd::Vector<Data>::Vector(const TraversableContainer<Data> &con):Vector(con.Size())
    {
        int index=0;
        con.Traverse(
            [&index,this](const Data &dat){
                this->elem[index]=dat;
                index++;
            }
        );
    }
    template <typename Data>
    lasd::Vector<Data>::Vector(MappableContainer<Data> &&map) : Vector(map.Size())
    {
        int index = 0;
        map.Map(
            [&index, this](Data &dat)
            {
                this->elem[index] = std::move(dat);
                index++;
            });
    }

    
    template <typename Data>
    const Data& lasd::Vector<Data>::operator[](const unsigned long i) const
    {
        if (i < this->size)
        {
            return this->elem[i];
        }
        else
        {
            throw std::out_of_range("Non puoi!");
        }
    }
    
    template<typename Data>
    lasd::Vector<Data>::Vector(const Vector<Data> &v)
    {
        this->elem = new Data[v.size];
        std::copy(v.elem, v.elem + v.size, this->elem);
        this->size = v.size;
    }

    template<typename Data>
    lasd::Vector<Data>::~Vector() noexcept
    {
            delete [] elem;
            this->elem=nullptr;
    }

    template <typename Data>
    Vector<Data> &lasd::Vector<Data>::operator=(const Vector<Data> &other)
    {
        Vector<Data> *tmpVec = new Vector<Data>(other);
        std::swap(*tmpVec,*this);
        delete tmpVec;
        return *this;
    }
    template <typename Data>
    lasd::Vector<Data>::Vector(Vector<Data> &&v) noexcept
    {
        std::swap(this->elem, v.elem);
        std::swap(size,v.size);
    }
    template <typename Data>
    Vector<Data> &lasd::Vector<Data>::operator=(Vector<Data> &&other) noexcept
    {
        std::swap(size, other.size);
        std::swap(this->elem, other.elem);
        return *this;
    }

    template<typename Data>
    bool lasd::Vector<Data>::operator==(const Vector<Data> &other)const noexcept{
        if(this->size == other.size)
        {
            for(unsigned long index = 0;index<size;++index)
            {
                if(this->elem[index] != other.operator[](index))
                {
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }
    }
    template <typename Data>
    bool lasd::Vector<Data>::operator!=(const Vector<Data> &other)const noexcept
    {
        return !(*this == other);
    }
    template <typename Data>
    void lasd::Vector<Data>::Clear() noexcept{
        if(this->elem != nullptr)
        {
            delete[] this->elem;
            this->elem = nullptr;
            this->size = 0;
        }
    }
    template <typename Data>
    void Vector<Data>::Resize(const unsigned long newsize)
    {
        if (newsize == 0)
        {
            Clear();
        }
        else if (size != newsize)
        {
            unsigned long limit = (size < newsize) ? size : newsize;
            Data *TmpElements = new Data[newsize]{};
            for (unsigned long index = 0; index < limit; ++index)
            {
                std::swap(this->elem[index], TmpElements[index]);
            }
            delete[] this->elem;
            std::swap(this->elem, TmpElements);
            size = newsize;
        }
    }

    template <typename Data>
    Data& lasd::Vector<Data>::operator[](const unsigned long index){
        if(index < this->size)
        {
            return this->elem[index];
        }else{
            throw std::out_of_range("Non puoi!");
        }
    }

  /*

    template <typename Data>
    const Data& lasd::Vector<Data>::Front() const
    {
        if(this->size != 0){
            return this->elem[0];
        }else{
            throw std::length_error("Non puoi !");
        }
    }

    template <typename Data>
    Data &lasd::Vector<Data>::Front()
    {
        if (this->size != 0)
        {
            return this->elem[0];
        }
        else
        {
            throw std::length_error("Non puoi !");
        }
    }

    template <typename Data>
    const Data &lasd::Vector<Data>::Back() const
    {
        if (size != 0)
        {
            return this->elem[this->size-1];
        }
        else
        {
            throw std::length_error("Non puoi !");
        }
    }
*/
    /*
    template <typename Data>
    Data &lasd::Vector<Data>::Back()
    {
        if (size != 0)
        {
            return this->elem[this->size-1];
        }
        else
        {
            throw std::length_error("Non puoi !");
        }
    }
*/
    /*Member for SortableVector.hpp*/
    // qui in sortable usare i metodi di Vector
    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(unsigned long initialSize)noexcept:Vector<Data>(initialSize)
    {}
    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(const SortableVector<Data> &v) noexcept :Vector<Data>(v)
    {}
    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(const TraversableContainer<Data> &other) : Vector<Data>(other)
    {
    }
    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(MappableContainer<Data> &&other) noexcept : Vector<Data>(std::move(other))
    {
    }
    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(SortableVector<Data> &&v) noexcept:Vector<Data>(std::move(v))
    {}

    template <typename Data>
    SortableVector<Data>& lasd::SortableVector<Data>::operator=(const SortableVector<Data> &other) noexcept
    {
        Vector<Data>::operator=(other);
        return *this;
    }
    template <typename Data>
    SortableVector<Data>& lasd::SortableVector<Data>::operator=(SortableVector<Data> &&other) noexcept
    {
        Vector<Data>::operator=(std::move(other));
        return *this;
    }
   
}
