#include"binarytree.hpp"

namespace lasd {
    //Funzioni per binarytree non mutable

    /*BINARY TREE*/
    template<typename Data>
    bool lasd::BinaryTree<Data>::Node::IsLeaf() const noexcept
    {
        if(!this->HasLeftChild() && !this->HasRightChild())
            return true;
        return false;
    }
    template<typename Data>
    bool lasd::BinaryTree<Data>::Node::operator==(const Node & nod) const noexcept{
        if(this->Element() == nod.Element())
        {
            if(this->LeftChild() == nod.LeftChild() && this->RightChild() == nod.RightChild())
            {
                return true;
            }
            return false;
        }
        return false;
    }
    template <typename Data>
    inline bool lasd::BinaryTree<Data>::Node::operator!=(const Node &nod) const noexcept
    {
        return !(*this == nod);
    }

    template <typename Data>
    bool lasd::BinaryTree<Data>::operator==(const BinaryTree<Data>& othertree) const noexcept{
        if(this->size != othertree.size)
            return false;
        lasd::BTPreOrderIterator<Data> it(*this);
        lasd::BTPreOrderIterator<Data> otherit(othertree);
        while (!it.Terminated() && !otherit.Terminated())
        {
            if (*it != *otherit)
                return false;
            ++it;
            ++otherit;
        }
        return it.Terminated() && otherit.Terminated();
    }

    template <typename Data>
    bool lasd::BinaryTree<Data>::operator!=(const BinaryTree<Data> &othertree) const noexcept
    {
        return !(*this == othertree);
    }
    
    template <typename Data>
    void lasd::BinaryTree<Data>::Traverse(TraverseFun fun) const
    {
        if(!this->Empty())
            PreOrderTraverse(fun,this->Root());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const
    {
        if(!this->Empty())
            PreOrderTraverse(fun, this->Root());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const
    {
        if(!this->Empty())
            PostOrderTraverse(fun, this->Root());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const
    {
        if(!this->Empty())
            InOrderTraverse(fun, this->Root());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const
    {
        if(!this->Empty())
            BreadthTraverse(fun,this->Root());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::PreOrderTraverse(TraverseFun fun,const Node & T) const
    {
            fun(T.Element());
            if(T.HasLeftChild())
            {
                PreOrderTraverse(fun,T.LeftChild());
            }
            if(T.HasRightChild())
            {
                PreOrderTraverse(fun,T.RightChild());
            }
    }
    
    template <typename Data>
    void lasd::BinaryTree<Data>::PostOrderTraverse(TraverseFun fun,const Node &T) const
    {
            if (T.HasLeftChild())
                PostOrderTraverse(fun, T.LeftChild());
            if (T.HasRightChild())
                PostOrderTraverse(fun, T.RightChild());
            fun(T.Element());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::InOrderTraverse(TraverseFun fun,const Node &T) const
    {
            if (T.HasLeftChild())
                InOrderTraverse(fun, T.LeftChild());
            fun(T.Element());
            if (T.HasRightChild())
                InOrderTraverse(fun, T.RightChild());
    }
    template <typename Data>
    void lasd::BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node &T) const
    {
        QueueVec<const typename lasd::BinaryTree<Data>::Node *> queue;
        queue.Enqueue(&T);
        const Node *current;

        while (queue.Size() != 0)
        {
            current = queue.HeadNDequeue(); 
            if (current->HasLeftChild())
            {
                queue.Enqueue(&(current->LeftChild()));
            }
            if (current->HasRightChild())
            {
                queue.Enqueue(&(current->RightChild()));
            }
            fun(current->Element());
        }
    }

    // Funzioni per binarytree mutable

    template <typename Data>
    void lasd::MutableBinaryTree<Data>::Map(MapFun fun)
    {
        if(!this->Empty())
            PreOrderMap(fun, this->Root());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::PreOrderMap(MapFun fun)
    {
        if(!this->Empty())
            PreOrderMap(fun, this->Root());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::PostOrderMap(MapFun fun)
    {
        if(!this->Empty())
            PostOrderMap(fun, this->Root());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::InOrderMap(MapFun fun)
    {
        if(!this->Empty())
            InOrderMap(fun, this->Root());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::BreadthMap(MapFun fun)
    {
        if(!this->Empty())
        {
            BreadthMap(fun, &this->Root());
        }
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::PreOrderMap(MapFun fun,MutableNode &T) 
    {
        fun(T.Element());
        if(T.HasLeftChild())
            PreOrderMap(fun, T.LeftChild());
        if(T.HasRightChild())
            PreOrderMap(fun, T.RightChild());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode &T) 
    {
        if(T.HasLeftChild())
            PostOrderMap(fun, T.LeftChild());
        if(T.HasRightChild())
            PostOrderMap(fun, T.RightChild());
        fun(T.Element());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode &T) 
    {
        if(T.HasLeftChild())
            InOrderMap(fun, T.LeftChild());
        fun(T.Element());
        if(T.HasRightChild())
            InOrderMap(fun, T.RightChild());
    }
    template <typename Data>
    void lasd::MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode *T)
    {
            QueueVec<MutableNode *> queue;
            queue.Enqueue(T);
            while (queue.Size() != 0)
            {
                T = queue.HeadNDequeue();
                MutableNode& othert = *T;
                if (othert.HasLeftChild())
                    queue.Enqueue(&othert.LeftChild());
                if (othert.HasRightChild())
                    queue.Enqueue(&othert.RightChild());
                fun(othert.Element());
            }
    }

    //Iteratore Visita In Ampiezza
    template <typename Data>
    lasd::BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> & tree){
        if(!tree.Empty())
        {
            this->queuelst.Enqueue(&(tree.Root()));
            this->first = &(tree.Root());
        }
    }

    template <typename Data>
    lasd::BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& other) noexcept
    {
        this->queuelst = other.queuelst;
        this->first = other.first;
    }

    template <typename Data>
    lasd::BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&other)
    {
        std::swap(this->queuelst, other.queuelst);
        std::swap(this->first,other.first);
    }

    template <typename Data>
    BTBreadthIterator<Data>& lasd::BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &other) noexcept
    {
        if (this != &other)
        {
            this->queuelst = other.queuelst;
            this->first = other.first;
        }
        return *this;
    }
    template <typename Data>
    BTBreadthIterator<Data> &lasd::BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&other) noexcept
    {
        std::swap(this->queuelst, other.queuelst);
        std::swap(this->first,other.first);
        return *this;
    }
    template <typename Data>
    bool lasd::BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &other)const noexcept
    {
        return this->queuelst == other.queuelst;
    }
    template <typename Data>
    bool lasd::BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &other)const noexcept
    {
        return !(this->queuelst == other.queuelst);
    }
    template<typename Data>
    const Data& lasd::BTBreadthIterator<Data>::operator*() const{
        if(this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        return this->queuelst.Head()->Element();
    }
    template <typename Data>
    bool lasd::BTBreadthIterator<Data>::Terminated() const noexcept
    {
        return (this->queuelst.Size() == 0);
    }
    template <typename Data>
    ForwardIterator<Data>& lasd::BTBreadthIterator<Data>::operator++()
    {
        if (this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        typename lasd::BinaryTree<Data>::Node const &T = *(this->queuelst.HeadNDequeue());
        if(T.HasLeftChild())
            this->queuelst.Enqueue(&(T.LeftChild()));
        if (T.HasRightChild())
            this->queuelst.Enqueue(&(T.RightChild()));
        return *this;
    }
    template <typename Data>
    void lasd::BTBreadthIterator<Data>::Reset() noexcept
    {
        if(this->first != nullptr){
            this->queuelst.Clear();
            queuelst.Enqueue(first);
        }
    }


    //iterator Pre-Ordine(Non-Mutable)
    template <typename Data>
    lasd::BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &tree)
    {
        if(!tree.Empty())
        {
            this->stklst.Push(&(tree.Root()));
            this->first = &(tree.Root());
        }
    }

    template <typename Data>
    lasd::BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> &other) noexcept
    {
        this->stklst = other.stklst;
        this->first = other.first;
    }

    template <typename Data>
    lasd::BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> &&other)
    {
        std::swap(this->stklst, other.stklst);
        std::swap(this->first, other.first);
    }

    template <typename Data>
    lasd::BTPreOrderIterator<Data>::~BTPreOrderIterator()
    {
        stklst.Clear();
        this->first = nullptr;
        delete first;
    }

    template <typename Data>
    lasd::BTPreOrderIterator<Data> &lasd::BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> &other) noexcept
    {
        if (this != &other)
        {
            stklst = other.stklst;
            first = other.first;
        }
        return *this;
    }
    template <typename Data>
    lasd::BTPreOrderIterator<Data> &lasd::BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&other) noexcept
    {
        std::swap(this->stklst, other.stklst);
        std::swap(this->first, other.first);
        return *this;
    }

    template <typename Data>
    bool lasd::BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &other)const noexcept
    {
        return this->stklst == other.stklst;
    }
    template <typename Data>
    bool lasd::BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &other)const noexcept
    {
        return !(this->stklst == other.stklst);
    }

    template <typename Data>
    const Data &lasd::BTPreOrderIterator<Data>::operator*() const
    {
        if (this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        return this->stklst.Top()->Element();
    }

    template <typename Data>
    ForwardIterator<Data>&lasd::BTPreOrderIterator<Data>::operator++()
    {
        if (this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        typename lasd::BinaryTree<Data>::Node const &T = *(this->stklst.TopNPop());
        if (T.HasRightChild())
            this->stklst.Push(&(T.RightChild()));
        if (T.HasLeftChild())
            this->stklst.Push(&(T.LeftChild()));
        return *this;
    }

    template <typename Data>
    bool lasd::BTPreOrderIterator<Data>::Terminated() const noexcept
    {
        return (this->stklst.Size() == 0);
    }

    template <typename Data>
    void lasd::BTPreOrderIterator<Data>::Reset() noexcept
    {
        if (this->first != nullptr)
        {
            this->stklst.Clear();
            stklst.Push(first);
        }
    }

    
    //Iteratore In-Ordine(Non-Mutable)
    template <typename Data>
    lasd::BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &tree)
    {
        if(!tree.Empty())
        {
            this->searchLeftMostNode(tree.Root());
            this->first = &(tree.Root());
        }
    }

    template <typename Data>
    lasd::BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> &other) noexcept
    {
        this->stklst = other.stklst;
        this->first = other.first;
    }

    template <typename Data>
    lasd::BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&other)
    {
        this->stklst = std::move(other.stklst);
        std::swap(this->first, other.first);
    }

    template <typename Data>
    lasd::BTInOrderIterator<Data> &lasd::BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> &other) noexcept
    {
        if (this != &other)
        {
            stklst = other.stklst;
            first = other.first;
        }
        return *this;
    }
    template <typename Data>
    lasd::BTInOrderIterator<Data> &lasd::BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> &&other) noexcept
    {
        std::swap(this->stklst, other.stklst);
        std::swap(this->first, other.first);
        return *this;
    }

    template <typename Data>
    bool lasd::BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> &other)const noexcept
    {
        return this->stklst == other.stklst;
    }
    template <typename Data>
    bool lasd::BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> &other) const noexcept
    {
        return !(this->stklst == other.stklst);
    }

    template <typename Data>
    const Data &lasd::BTInOrderIterator<Data>::operator*() const
    {
        if (this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        return this->stklst.Top()->Element();
    }

    template <typename Data>
    BTInOrderIterator<Data> &lasd::BTInOrderIterator<Data>::operator++()
    {
        if(this->Terminated())
            throw std::out_of_range("Struttura Terminata !");
        typename lasd::BinaryTree<Data>::Node const &T = *this->stklst.TopNPop();
        if(T.HasRightChild())
        {
            this->stklst.Push(&T.RightChild());
            if(this->stklst.Top()->HasLeftChild())
            {
                searchLeftMostNode(this->stklst.Top()->LeftChild());
            }
        }
        return *this;
    }

    template <typename Data>
    bool lasd::BTInOrderIterator<Data>::Terminated() const noexcept
    {
        return (this->stklst.Size() == 0);
    }

    template <typename Data>
    void lasd::BTInOrderIterator<Data>::Reset() noexcept
    {
        if(this->first != nullptr)
        {
            this->stklst.Clear();
            searchLeftMostNode(*this->first);
        }
    }

    template <typename Data>
    void lasd::BTInOrderIterator<Data>::searchLeftMostNode(const typename lasd::BinaryTree<Data>::Node &T)
    {
        if(T.HasLeftChild())
        {
            this->stklst.Push(&T);
            searchLeftMostNode(T.LeftChild());
        }
        else{
            this->stklst.Push(&T);
            return ;
        }
    }

    //Iteratore Post-Ordine(Non-Mutable)

    // Function GetMostLeftLeaf
    template <typename Data>
    void BTPostOrderIterator<Data>::getMostLeftLeaf(const struct BinaryTree<Data>::Node &nod)
    {
        this->current = &nod; // Store pointer to the current node
        while (current->HasLeftChild() || current->HasRightChild())
        {
            stk.Push(current); // Push current node to stack
            if (current->HasLeftChild())
            {
                current = &(current->LeftChild()); // Move to the left child
            }
            else if(current->HasRightChild())
            {
                current = &(current->RightChild()); // Move to the right child
            }
        }
        stk.Push(current);
    }

    /* ************************************************************************** */

    // Specific constructors
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &bt)
    {
        if(!bt.Empty())
        {
            getMostLeftLeaf(bt.Root());
            this->root = &bt.Root();
            this->current = stk.Top();
        }
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept
    {
        if(this->root != nullptr)
        {
            stk.Clear();
            getMostLeftLeaf(*this->root);
            this->current = stk.Top();
        }
    }

    /* ************************************************************************ */

    // Copy constructor
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &iter)
    {
       this->stk = iter.stk;
       this->current = iter.current;
       this->root = iter.root;
    }

    // Move constructor
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&iter) noexcept
    {
       this->stk = std::move(iter.stk);
       std::swap(this->current,iter.current);
       std::swap(this->root,iter.root);
    }

    /* ************************************************************************ */

    // Destructor
    template <typename Data>
    BTPostOrderIterator<Data>::~BTPostOrderIterator()
    {
       stk.Clear();
    }

    /* ************************************************************************ */

    // Copy assignment
    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &iter)
    {
        BTPostOrderIterator<Data> *tmp = new BTPostOrderIterator<Data>(iter);
        std::swap(*tmp, *this);
        delete (tmp);
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&iter) noexcept
    {
        this->stk = std::move(iter.stk);
        std::swap(this->current, iter.current);
        std::swap(this->root, iter.root);
        return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &iter) const noexcept
    {
        if(this->current != iter.current)
            return false;
        if(this->root != iter.root)
            return false;
        if(this->stk != iter.stk)
            return false;
        return true;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &iter) const noexcept
    {
        return !(*this == iter);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)
    template <typename Data>
    const Data &BTPostOrderIterator<Data>::operator*() const
    {
        if(!Terminated())
        {
            return current->Element();
        }
        throw std::out_of_range("Iteratore terminato\n");
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept
    {
        return (this->current == nullptr);
    }

    /* ************************************************************************ */

    template <typename Data>
    ForwardIterator<Data>& BTPostOrderIterator<Data>::operator++()
    {
        if(Terminated())
            throw std::out_of_range("Iteratore Terminato\n");
        const struct BinaryTree<Data>::Node *nod = stk.TopNPop();
        if(!stk.Empty())
        {
            if (stk.Top()->HasLeftChild() && nod == &stk.Top()->LeftChild() && stk.Top()->HasRightChild())
            { // controllo se vengo da sinistra
                stk.Push(&stk.Top()->RightChild());
                if (stk.Top()->HasLeftChild())
                {
                    getMostLeftLeaf(stk.Top()->LeftChild());
                }
                else if (stk.Top()->HasRightChild())
                {
                    getMostLeftLeaf(stk.Top()->RightChild());
                }
            }
            this->current = stk.Top();
        }
        else{
            this->current = nullptr; // stack terminato
        }
        return *this;
    }
};
