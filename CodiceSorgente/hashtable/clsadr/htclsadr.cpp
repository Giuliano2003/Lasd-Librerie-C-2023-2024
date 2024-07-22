#include"htclsadr.hpp"
#include "../../bst/bst.hpp"

namespace lasd {

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long &initsize) noexcept{
        this->v.Resize(initsize);
        TABLESIZE = initsize;
        this->size = 0;
    }


    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& con) noexcept
    {
        this->v.Resize(con.Size());
        TABLESIZE = con.Size();
        int index = 0;
        if(!con.Empty())
        {
            con.Traverse(
                [this,&index](const Data &dat){
                    Insert(dat);
                    index++;
                }
            );
        }
    }

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long &newsize,const TraversableContainer<Data> &con)
    {
        this->v.Resize(newsize);
        TABLESIZE = newsize;
        int index = 0;
        if (!con.Empty())
        {
            con.Traverse(
                [this, &index](const Data &dat)
                {
                    Insert(dat);
                    index++;
                });
        }
    }

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> &&map) noexcept
    {
        this->v.Resize(map.Size());
        TABLESIZE = map.Size();
        if (!map.Empty())
        {
            map.Map(
                [this](Data &dat)
                {
                    Insert(dat);
                });
        }
    }

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long &newsize, MappableContainer<Data> &&map) noexcept
    {
        this->v.Resize(newsize);
        TABLESIZE = newsize;
        int index = 0;
        if (!map.Empty())
        {
            map.Map(
                [this, &index](Data &dat)
                {
                    Insert(std::move(dat));
                    index++;
                });
        }
    }

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &ht) 
    {
        size = ht.size;
        this->acst = ht.acst;
        this->bcst = ht.bcst;
        TABLESIZE = ht.TABLESIZE;
        this->v = ht.v;
    }

    template <typename Data>
    lasd::HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&ht) 
    {
        std::swap(size, ht.size);
        std::swap(this->acst, ht.acst);
        std::swap(this->bcst, ht.bcst);
        std::swap(TABLESIZE, ht.TABLESIZE);
        std::swap(this->v,ht.v);
    }

    template <typename Data>
    HashTableClsAdr<Data>& lasd::HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> &ht) noexcept
    {
        size = ht.size;
        this->acst = ht.acst;
        this->bcst = ht.bcst;
        TABLESIZE = ht.TABLESIZE;
        this->v = ht.v;
        return *this;
    }

    template <typename Data>
    HashTableClsAdr<Data> &lasd::HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data> &&ht) noexcept
    {
        std::swap(size, ht.size);
        std::swap(this->acst, ht.acst);
        std::swap(this->bcst, ht.bcst);
        std::swap(TABLESIZE, ht.TABLESIZE);
        std::swap(this->v, ht.v);
        return *this;
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data> &ht) const noexcept
    {
        if(this->size != ht.size)
        {
            return false;
        }
        bool isEqual = true;
        for(unsigned long i = 0;i<TABLESIZE;i++){
            this->v[i].Traverse(
                [ht,&isEqual](const Data &dat){
                    if(!ht.Exists(dat)){
                        isEqual = false;
                    }
                }
            );
        }
        return (isEqual == true);
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data> &ht) const noexcept
    {
        return !(HashTableClsAdr<Data>::operator==(ht));
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::Insert(const Data &dat) 
    {
        if(TABLESIZE == 0)
        {
            this->Resize(64);
        }
        unsigned long index = this->HashKey(dat);
        if(this->v[index].Insert(dat))
        {
            this->size++;
            return true;
        }
        return false;
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::Insert(Data &&dat)
    {
        if (TABLESIZE == 0)
        {
            this->Resize(64);
        }
        unsigned long index = this->HashKey(dat);
        if (this->v[index].Insert(std::move(dat)))
        {
            this->size++;
            return true;
        }
        return false;
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::Remove(const Data &dat)
    {
        unsigned long index = this->HashKey(dat);
        if(this->size != 0)
        {
            if (this->v[index].Remove(dat))
            {
                this->size--;
                return true;
            }
            return false;
        }else{
            return false;
        }
    }

    template <typename Data>
    void lasd::HashTableClsAdr<Data>::Resize(const unsigned long newindex)
    {
        if(newindex == 0)
        {
            this->Clear();
        }
        else{
        HashTableClsAdr<Data> newHash(newindex);
        if(!this->size == 0)
        {
            for(unsigned long i = 0; i < TABLESIZE; i++)
            {
                v[i].Traverse(
                [&newHash](const Data &dat){
                    newHash.Insert(dat);
                });
            }
        }
        this->Clear();
        *this = newHash;
        newHash.Clear();
        }
    }

    template <typename Data>
    bool lasd::HashTableClsAdr<Data>::Exists(const Data &dat) const noexcept
    {
        if(this->size != 0){
            unsigned long index = this->HashKey(dat);
            return (this->v[index].Exists(dat));
        }
        return false;
    }

    template <typename Data>
    void lasd::HashTableClsAdr<Data>::Clear() noexcept{
        if(!this->v.Empty())
        {
            for(unsigned long i = 0; i<TABLESIZE;i++)
            {
                this->v[i].Clear();
            }
        }
        this->size = 0;
        TABLESIZE = 0;
    }
}


