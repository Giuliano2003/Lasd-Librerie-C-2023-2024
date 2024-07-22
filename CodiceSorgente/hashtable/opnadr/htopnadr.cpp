#include "htopnadr.hpp"
#include "../../list/list.hpp"
#define CELLALIBERA 0 
#define CELLAOCCUPATA 1
#define CELLACANCELLATA 2
namespace lasd {

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long size)
    {
        this->table.Resize(size);
        this->support.Resize(size);
        TABLESIZE = size;
        hop=HashKeyC(size);
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> &ht)
    {
        size = ht.size;
        this->acst = ht.acst;
        this->bcst = ht.bcst;
        TABLESIZE = ht.TABLESIZE;
        this->table = ht.table;
        this->support = ht.support;
        this->hop = ht.hop;
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> &&ht)
    {
        std::swap(size, ht.size);
        std::swap(this->acst, ht.acst);
        std::swap(this->bcst, ht.bcst);
        std::swap(TABLESIZE, ht.TABLESIZE);
        this->table = std::move(ht.table);
        this->support = std::move(ht.support);
        std::swap(this->hop, ht.hop);
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> &con)
    {
        init(con.Size());
        if(!con.Empty()){
            con.Traverse(
                [this](const Data &dat){
                    this->Insert(dat);
                }
            );
        }
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, const TraversableContainer<Data> &con)
    {
        init(size);
        if (!con.Empty())
        {
            con.Traverse(
                [this](const Data &dat)
                {
                    this->Insert(dat);
                });
        }
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> &&map)
    {
        init(map.Size());
        if (!map.Empty())
        {
            map.Map(
                [this](Data &dat)
                {
                    this->Insert(std::move(dat));
                });
        }
    }

    template <typename Data>
    lasd::HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, MappableContainer<Data> &&map)
    {
        init(size);
        if (!map.Empty())
        {
            map.Map(
                [this](Data &dat)
                {
                    this->Insert(std::move(dat));
                });
        }
    }

    template <typename Data>
    HashTableOpnAdr<Data> &lasd::HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data> &ht) noexcept
    {
        size = ht.size;
        this->acst = ht.acst;
        this->bcst = ht.bcst;
        TABLESIZE = ht.TABLESIZE;
        this->table = ht.table;
        this->support = ht.support;
        this->hop = ht.hop;
        return *this;
    }

    template <typename Data>
    HashTableOpnAdr<Data> &lasd::HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data> &&ht) noexcept
    {
        std::swap(size, ht.size);
        std::swap(this->acst, ht.acst);
        std::swap(this->bcst, ht.bcst);
        std::swap(TABLESIZE, ht.TABLESIZE);
        this->table = std::move(ht.table);
        this->support = std::move(ht.support);
        std::swap(this->hop,ht.hop);
        return *this;
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> &ht) const noexcept
    {
       if(this->size != ht.size){
            return false;
       }
       for(unsigned long i = 0; i< this->size ; i++)
       {
            if(this->support[i] == CELLAOCCUPATA)
            {
                if(!ht.Exists(this->table[i]))
                {
                    return false;
                }
            }

       }
        return true;
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data> &ht) const noexcept
    {
        return !(*this == ht);
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::Insert(const Data &key)
    {

        if(TABLESIZE == 0)
        {
            this->Resize((TABLESIZE+1)*2);
        }
        if (this->size >= TABLESIZE / 2)
        {
            this->Resize(TABLESIZE * 2);
        }

        if(this->Exists(key))
        {
            return false;
        }

        unsigned long hash = this->HashKey(key);

        if (this->support[hash] == CELLALIBERA || this->support[hash] == CELLACANCELLATA)
        {
            this->table[hash] = key;
            this->support[hash] = CELLAOCCUPATA;
            this->size++;
            return true;
        }
        unsigned long i = Find(hash);
        if (i != hash)
        {
            this->table[i] = key;
            this->support[i] = CELLAOCCUPATA;
            this->size++;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::Insert(Data &&key)
    {
        if (TABLESIZE == 0)
        {
            this->Resize((TABLESIZE + 1) * 2);
        }
        if (this->size >= TABLESIZE / 2)
        {
            this->Resize(TABLESIZE * 2);
        }
        if (this->Exists(key))
        {
            return false;
        }
        unsigned long hash = this->HashKey(key);
        if (this->support[hash] == CELLALIBERA || this->support[hash] == CELLACANCELLATA)
        {
            this->table[hash] = std::move(key);
            this->support[hash] = CELLAOCCUPATA; 
            this->size++;
            return true;
        }
        unsigned long i = Find(hash);
        if (i != hash)
        {
            this->table[i] = std::move(key);
            this->support[i] = CELLAOCCUPATA;
            this->size++;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::Remove(const Data &dat)
    {
        if(Exists(dat))
        {
            unsigned long hash = this->HashKey(dat);
            if(this->support[hash] == CELLAOCCUPATA && this->table[hash] == dat)
            {
                this->support[hash] = CELLACANCELLATA;
                this->size--;
                return true;
            }
            else{
                unsigned long i = FindEmpty(hash,dat); // vedo se il dato c'è più avanti
                if(i != hash)
                {
                    this->support[i] = CELLACANCELLATA;
                    this->size--;
                    return true;
                }
            }
        }
        return false;
    }




    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::Exists(const Data &dat) const noexcept
    {
        if(this->size != 0)
        {
            unsigned long hash = this->HashKey(dat);
            if(this->support[hash] == CELLAOCCUPATA || this->support[hash] == CELLACANCELLATA)
            {
                if(this->table[hash] == dat && this->support[hash] == CELLAOCCUPATA){
                    return true;
                }
                else{
                    unsigned long to_search=FindEmpty(hash,dat);
                    if(to_search != hash && this->support[to_search] == CELLAOCCUPATA){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
            return false;
        }
        return false;
    }

    template <typename Data>
    void lasd::HashTableOpnAdr<Data>::Clear() noexcept
    {
        if(!this->table.Empty())
        {
            table.Clear();
            support.Clear();  
        }
        this->size = 0;
        TABLESIZE = 0;
    }

    template <typename Data>
    void lasd::HashTableOpnAdr<Data>::Resize(unsigned long newindex) noexcept
    {
        if(newindex == 0)
        {
            this->Clear();
        }
        else{
            HashTableOpnAdr<Data> newHash(newindex);
            if(!this->size == 0)
            {
                for(unsigned long i = 0; i< TABLESIZE;i++)
                {
                    if(this->support[i] == CELLAOCCUPATA)
                    {
                        newHash.Insert(this->table[i]);
                    }
                    if(this->support[i] == CELLACANCELLATA)
                    {
                        if(newHash.Insert(this->table[i])){
                            unsigned long hash = newHash.HashKey(this->table[i]);
                            unsigned long index = newHash.FindEmpty(hash,this->table[i]);
                            newHash.support[index] = CELLACANCELLATA;
                        }
                    }
                }
            }
            unsigned long oldSize = this->size;
            this->Clear();
            *this = newHash;
            this->size = oldSize;
            newHash.Clear();
        }
    }

    template <typename Data>
    unsigned long lasd::HashTableOpnAdr<Data>::Find(unsigned long hash) noexcept
    {
        unsigned long proning = 0;
        for(unsigned long i = 0;i<TABLESIZE;i++)
        {
            proning = ((hash + (i * hop))) % TABLESIZE;
            if (this->support[proning] != CELLAOCCUPATA)
            {
                return proning;
            }
        }
        return proning;
    }

    template <typename Data>
    unsigned long lasd::HashTableOpnAdr<Data>::FindEmpty(unsigned long hash,const Data &dat)const noexcept
    {
        unsigned long proning = 0;
        for (unsigned long i = 0; i < TABLESIZE; i++)
        {
            proning = ((hash + (i * hop))) % TABLESIZE;
            if(this->support[proning] == CELLAOCCUPATA && this->table[proning] == dat) // è una cella occupata dal dato che miserve
            {
                return proning;
            }
            if(this->support[proning] == CELLALIBERA)
            {
                // se ho trovato una cella libera posso fermarmi
                return hash;
            }
        }
        return proning;
    }

    template <typename Data>
    unsigned long lasd::HashTableOpnAdr<Data>::HashKeyC(unsigned long key) noexcept
    {
        // Controllo del caso quando key è 0 o 1
        if (key <= 1)
        {
            return 0;
        }
        std::default_random_engine eng1 = std::default_random_engine(std::random_device{}());
        std::uniform_int_distribution<unsigned long> distra = std::uniform_int_distribution<unsigned long>(1, key - 1);
        if (isPrime(key))
        {
            return distra(eng1); // Se il numero è primo, restituisce un numero casuale tra 1 e key-1
        }
        else
        {
            if (key > 0 && (key & (key - 1)) == 0)
            { // Controlla se key è una potenza di 2
                //cout<<"Entrato\n";
                return (key / 2) + 1;
            }
            else if (key % 2 != 0)
            { // Se key è dispari
                return key + 1;
            }
            else
            { // Caso in cui key è pari e non è una potenza di 2
                for (unsigned long i = 2; i < key; ++i)
                {
                    if (std::gcd(key, i) == 1)
                    {
                        return i;
                    }
                }
            }
        }
        return 1;
    }

    template <typename Data>
    bool lasd::HashTableOpnAdr<Data>::isPrime(unsigned long key) const noexcept{
        if (key < 2)
        {
            return false;
        }
        for (int i = 2; i <= std::sqrt(key); ++i)
        {
            if (key % i == 0)
            {
                return false; 
            }
        }
        return true;
    }

    template <typename Data>
    void lasd::HashTableOpnAdr<Data>::init(unsigned long newsize) noexcept{
        this->table.Resize(newsize);
        this->support.Resize(newsize);
        TABLESIZE = newsize;
        hop = HashKeyC(newsize);
    }
};
