#include <stdexcept>
#include "stackvec.hpp"
namespace lasd
{

    /* ************************************************************************** */
    
    template <typename Data>
    StackVec<Data>::StackVec(StackVec<Data> &&stk) noexcept
    {
        std::swap(this->elem, stk.elem);
        std::swap(this->size, stk.size);
        std::swap(this->i, stk.i);
    }

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &stk)
    {
        Vector<Data>::operator=(stk);
        this->i = stk.i;
        return *this;
    };

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&stk)
    {
        Vector<Data>::operator=(std::move(stk));
        std::swap(this->i, stk.i);
        return *this;
    };

    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data> &vec) const noexcept{
        if (this->i == vec.i)
        {
            for (unsigned long i = 0; i < this->i; ++i)
            {
                if (this->elem[i] != vec.elem[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool StackVec<Data>::operator!=(const StackVec<Data> &stk) const noexcept
    {
        return !(*this == stk);
    };

    template <typename Data>
    const Data &StackVec<Data>::Top() const
    {
        if (i != 0)
        {
            return this->elem[i - 1];
        }
        else
        {
            throw std::length_error("L'array è vuoto");
        }
    };

    template <typename Data>
    Data &StackVec<Data>::Top()
    {
        if (i != 0)
        {
            return this->elem[i - 1];
        }
        else
        {
            throw std::length_error("L'array è vuoto");
        }
    };

    template <typename Data>
    void StackVec<Data>::Pop()
    {
        if (i != 0)
        {
            Reduce();
            i--;
        }
        else
        {
            throw std::length_error("L'array è vuoto");
        };
    };

    template <typename Data>
    Data StackVec<Data>::TopNPop()
    {
        Reduce();
        Data to_return = Top();
        Pop();
        return to_return;
    };

    template <typename Data>
    void StackVec<Data>::Push(const Data &elem) noexcept
    {
        Expand();
        this->elem[i++] = elem;
    };

    template <typename Data>
    void StackVec<Data>::Push(Data &&elem) noexcept
    {
        Expand();
        this->elem[i++] = std::move(elem);
    };

    template <typename Data>
    bool StackVec<Data>::Empty() const noexcept
    {
       return (i == 0);
    };

    template <typename Data>
    unsigned long StackVec<Data>::Size() const noexcept
    {
        return i;
    };

    template <typename Data>
    void StackVec<Data>::Clear() noexcept
    {
        i=0;
        Vector<Data>::Resize(1);
    };

    template <typename Data>
    void StackVec<Data>::Expand()
    {
        if (i == this->size)
        {
            Vector<Data>::Resize(this->size * 2);
        };
    };

    template <typename Data>
    void StackVec<Data>::Reduce()
    {
        if (i == this->size / 4)
        {
            Vector<Data>::Resize(this->size / 2);
        }
    };

    /* ************************************************************************** */

}


