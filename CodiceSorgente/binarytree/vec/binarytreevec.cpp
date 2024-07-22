#include"binarytreevec.hpp"
#include "../../list/list.hpp"
namespace lasd {

    /*Nodi*/

    template<typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & dat,unsigned long index,Vector<NodeVec *> * vectorN)
    {
        element = dat;
        indexNode = index;
        vectorNode = vectorN;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(Data &dat, unsigned long index,Vector<NodeVec *> *vectorN) : 
    element(std::move(dat)), indexNode(index),vectorNode(vectorN) {}

    /*Costruttori Per BinaryTreeVec*/

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> &con) noexcept
    {
        if(!con.Empty()){
            this->treevector = new Vector<NodeVec *>(con.Size());
            int index = 0;
            con.Traverse(
                [&index, this](const Data &dat)
                {
                    NodeVec *newNode = new NodeVec(dat, index,this->treevector);
                    this->treevector->operator[](index) = newNode;
                    index++;
                });
            this->size = con.Size();
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> &&map)
    {
        if(!map.Empty())
        {
            this->treevector = new Vector<NodeVec *>(map.Size());
            int index = 0;
            map.Map(
                [&index, this](Data &dat)
                {
                    NodeVec *newNode = new NodeVec(std::move(dat), index,this->treevector);
                    this->treevector->operator[](index) = newNode;
                    index++;
                });
            this->size = map.Size();
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bvec) noexcept
    {
        if(!bvec.Empty())
        {
            this->treevector = new Vector<NodeVec *>(bvec.size);
            int index = 0;
            bvec.BreadthTraverse(
                [&index, this](const Data &dat)
                {
                    NodeVec *newNode = new NodeVec(dat, index, this->treevector);
                    this->treevector->operator[](index) = newNode;
                    index++;
                });
            this->size = bvec.Size();
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&bvec)
    {
        std::swap(this->treevector,bvec.treevector);
        std::swap(this->size,bvec.size);
        bvec.Clear();
       
    }

    /*Copy And Move assignment*/
    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &bt) noexcept
    {
        if(!bt.Empty())
        {
            this->size = bt.Size();
            BinaryTreeVec<Data> *tmpbt = new BinaryTreeVec<Data>(bt);
            std::swap(*this, *tmpbt);
            delete tmpbt;
        }
        else{
            Clear();
        }
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&bvec)
    {
        std::swap(size, bvec.size);
        std::swap(treevector, bvec.treevector);
        return *this;
    }

    /*Clear*/
    template <typename Data>
    void BinaryTreeVec<Data>::Clear() noexcept
    {
        if (this->treevector != nullptr)
        {
            for (unsigned long index = 0; index < this->size; index++)
            {
                delete this->treevector->operator[](index); // cosi distruggo un nodo
            }
            delete this->treevector;
            this->treevector = nullptr;
            this->size = 0;
        }
    }

    /*Distruttore*/
    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        this->Clear();
        delete treevector;
        treevector = nullptr;
    }

    /*Operatori Di Confronto*/
    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> & bvec) const noexcept
    {
        return BinaryTree<Data>::operator==(bvec);
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &bvec) const noexcept
    {
        return !(*this == bvec);
    }
    /*Membri da Traversable Container*/
    template <typename Data>
    void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const
    {
        for(unsigned long index = 0;index < this->size ; index ++)
        {
            fun(this->treevector->operator[](index)->Element());
        }
    }
    template <typename Data>
    void BinaryTreeVec<Data>::BreadthMap(MapFun fun)
    {
        for (unsigned long index = 0; index < this->size; index++)
        {
            fun(this->treevector->operator[](index)->Element());
        }
    }
}
