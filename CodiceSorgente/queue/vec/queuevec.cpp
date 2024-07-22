 #include<iostream>
#include"queuevec.hpp"
#include<stdexcept>
using namespace std;
namespace lasd {
    template <typename Data>
    lasd::QueueVec<Data>::QueueVec(const QueueVec<Data> &other) noexcept
        : Vector<Data>(other), head(other.head), tail(other.tail) {}

    template <typename Data>
    lasd::QueueVec<Data>::QueueVec(QueueVec<Data> &&other) noexcept
        : Vector<Data>(std::move(other)), head(other.head), tail(other.tail) {
            other.Clear();
        }

    template <typename Data>
    QueueVec<Data> &lasd::QueueVec<Data>::operator=(const QueueVec<Data> &other) noexcept
    {   
        if (this != &other)
        {
            lasd::Vector<Data>::operator=(other);
            this->head = other.head;
            this->tail = other.tail;
        }
        return *this;
    }

    template <typename Data>
    QueueVec<Data> &lasd::QueueVec<Data>::operator=(QueueVec<Data> &&other) noexcept
    {
        if (this != &other)
        {
            lasd::Vector<Data>::operator=(std::move(other));
            this->head = other.head;
            this->tail = other.tail;
            other.Clear();
        }
        return *this;
    }

    template <typename Data>
    lasd::QueueVec<Data>::QueueVec(const TraversableContainer<Data> &other) noexcept : Vector<Data>::Vector(other)
    {
        this->head = 0;
        this->tail = other.Size();
        this->size = other.Size()+4;
    }
    template <typename Data>
    lasd::QueueVec<Data>::QueueVec(MappableContainer<Data> &&other) noexcept : Vector<Data>::Vector(std::move(other))
    {
        this->head = 0;
        this->tail = other.Size();
        this->size = other.Size() + 4;
    }

    template <typename Data>
    bool lasd::QueueVec<Data>::operator==(const QueueVec<Data> &other)const noexcept
    {
        if (Size() != other.Size())
            return false;

        unsigned long i = head;
        unsigned long j = tail;
        unsigned long k = other.head;

        while (i != j)
        {
            if (this->elem[i] != other.elem[k])
                return false;
            i = (i + 1) % size;
            k = (k + 1) % other.size;
        }

        return true;
    }

    template <typename Data>
    bool lasd::QueueVec<Data>::operator!=(const QueueVec<Data> &que) const noexcept
    {
        return !(*this == que);
    }

    template<typename Data>
    void lasd::QueueVec<Data>::Enqueue(const Data &dat) noexcept{
        Expand();
        this->elem[this->tail]=dat;
        this->tail++;
        this->tail = this->tail % this->size;
    }
    template <typename Data>
    void lasd::QueueVec<Data>::Enqueue(Data &&dat) noexcept
    {
        Expand();
        this->elem[this->tail] = std::move(dat);
        this->tail++;
        this->tail = this->tail % this->size;
    }
    template <typename Data>
    void lasd::QueueVec<Data>::Dequeue()
    {
        if(this->head == this->tail)
        {
            throw std::length_error("Non ci sono elementi !");
        }
        Reduce();
        this->head++;
        this->head=this->head % this->size;
    }
    template <typename Data>
    const Data &lasd::QueueVec<Data>::Head() const
    {
        if (this->head == this->tail || this->elem == nullptr)
        {
            throw std::length_error("Il vettore è vuoto !");
        }
    
        return this->elem[this->head];
    }

    template <typename Data>
    Data &lasd::QueueVec<Data>::Head()
    {
        if (this->head == this->tail || this->elem == nullptr)
        {
            throw std::length_error("Il vettore è vuoto !");
        }
       
        return this->elem[this->head];
    }

    template <typename Data>
    Data lasd::QueueVec<Data>::HeadNDequeue()
    {
        if (this->head != this->tail)
        {
            Data dat(std::move(this->elem[head]));
            Reduce();
            head = head + 1;
            head = head % this->size;
            return dat;
        }
        else
        {
            throw std::length_error("La coda è vuota!");
        }
    }

    template <typename Data>
    void lasd::QueueVec<Data>::Expand()
    {
        unsigned long num = this->Size(); // numero di elementi effettivi presenti nel vettore   
        cout<<"E"<<endl;
        if(num + 1 == this->size)
        {
            cout << "E" << endl;
            Resize(this->size*2,num);
        }
    }

    template <typename Data>
    void lasd::QueueVec<Data>::Reduce()
    {
        unsigned long num = this->Size(); // numero di elementi effettivi presenti nel vettore
        if (num + 1 == this->size / 4)
        {
            Resize(this->size / 2, num);
        }
    }

    template <typename Data>
    void lasd::QueueVec<Data>::Resize(unsigned long newSize, unsigned long num)
    {
        Data *temp = new Data[newSize];
        unsigned long max = (num <= newSize) ? num : newSize;
        for (unsigned long idx1 = head, idx2 = 0; idx2 < max; ++idx2, ++idx1 %= this->size)
        {
            std::swap(this->elem[idx1], temp[idx2]);
        }
        std::swap(this->elem, temp);
        delete[] temp;
        this->size = newSize;
        this->tail = num;
        this->head = 0;
    }

    template <typename Data>
    unsigned long lasd::QueueVec<Data>::Size() const noexcept
    {
        return (((this->tail+this->size)-this->head)%this->size);
    }

    template <typename Data>
    bool lasd::QueueVec<Data>::Empty() const noexcept
    {
        return (this->head == this->tail);
    }

    template <typename Data>
    void lasd::QueueVec<Data>::Clear() noexcept
    {
        this->head = 0;
        this->tail = 0;
        Vector<Data>::Resize(4);
    }
}



