#include<iostream>
#include<stdexcept>
#include"list.hpp"
using namespace std;
namespace lasd {
    template<typename Data>
    lasd::List<Data>::List(const List<Data> &otherList) noexcept{
        otherList.Traverse(
            [this](const Data &dat)
            {
                InsertAtBack(dat);
            });
        this->size=otherList.size;
    }
    template <typename Data>
    lasd::List<Data>::List(List<Data> &&otherList) noexcept
    {
        std::swap(head,otherList.head);
        std::swap(tail,otherList.tail);
        std::swap(size,otherList.size);
    }

    template <typename Data>
    lasd::List<Data>::List(const TraversableContainer<Data> &other) noexcept
    {
        other.Traverse(
            [this](const Data &dat)
            {
                InsertAtBack(dat);
            });
    }

    template <typename Data>
    lasd::List<Data>::List(MappableContainer<Data> &&other) noexcept
    {
        other.Map(
            [this](Data &dat)
            {
               InsertAtBack(std::move(dat));
            });
    }

    template <typename Data>
    lasd::List<Data>::Node::Node(Node &&nod) noexcept : element(std::move(nod.element)), link(nod.link)
    {
        nod.link = nullptr;
    }
    template <typename Data>
    bool lasd::List<Data>::Node::operator==(const Node &nod) const noexcept
    {
        if(this->element != nod.element)
            return false;
        if(this->link != nod.link)
            return false;
        return true;
    }
    template <typename Data>
    bool lasd::List<Data>::Node::operator!=(const Node &nod) const noexcept
    {
        return !(*this == nod);
    }
    // Copy Assignement
    template <typename Data>
    List<Data> &lasd::List<Data>::operator=(const List<Data> &otherList) noexcept
    {
        List<Data> *tmplist = new List<Data>(otherList);
        std::swap(*tmplist, *this);
        delete (tmplist);
        return *this;
    }
    //Move Assignement
    template <typename Data>
    List<Data> &lasd::List<Data>::operator=(List<Data> &&otherList) noexcept
    {
        std::swap(head, otherList.head);
        std::swap(tail, otherList.tail);
        std::swap(size, otherList.size);
        return *this;
    }
    //Comparison Operator
    template <typename Data>
    bool lasd::List<Data>::operator==(const List<Data>& otherList) const noexcept{
        if(this->Size() != otherList.Size())
        {
            return false;
        }
       Node *curr = this->head;
       Node *othercurr = otherList.head;
       while(curr != nullptr)
       {
            if(curr->element != othercurr->element)
                return false;
            curr=curr->link;
            othercurr=othercurr->link;
       }
       return true;
    }
    // Comparison Operator
    template <typename Data>
    bool lasd::List<Data>::operator!=(const List<Data> &otherList) const noexcept
    {
        return !(*this == otherList);
    }
    template <typename Data>
    lasd::List<Data>::Node::Node(Data &&key, Node *nextval) noexcept: element(std::move(key)), link(nextval) {}

    
    template <typename Data>
    bool lasd::List<Data>::Insert(const Data &key)
    {
        Node *curr = this->head;
        // vedo se l'elemento è gia presente
        while (curr!= nullptr)
        {
            if (curr->element == key)
                return false;
            curr = curr->link;
        }
        InsertAtBack(key);
        return true;
    }
    template <typename Data>
    bool lasd::List<Data>::Insert(Data &&key)
    {
        Node *curr = this->head;
        // vedo se l'elemento è gia presente
        while (curr != nullptr)
        {
            if (curr->element == key)
                return false;
            curr = curr->link;
        }
        InsertAtBack(std::move(key));
        return true;
    }
    template <typename Data>
    bool lasd::List<Data>::Remove(const Data &key)
    {
        if (this->head == nullptr)
            return false; // Lista vuota, nessun elemento da rimuovere

        Node *curr = this->head;
        Node *prec = nullptr;

        // Controllo se l'elemento è presente nella lista
        while (curr != nullptr)
        {
            if (curr->element == key)
            {
                Node *to_remove = nullptr;
                if (head == curr)
                {
                    // Sto eliminando il primo nodo
                    to_remove = head;
                    head = curr->link;
                    // Se il nodo rimosso era anche l'ultimo, aggiorna tail
                    if (head == nullptr)
                        tail = nullptr;
                }
                else
                {
                    // Sto eliminando un nodo diverso dal primo
                    to_remove = curr;
                    prec->link = curr->link;
                    // Se il nodo rimosso era l'ultimo, aggiorna tail
                    if (curr->link == nullptr)
                        tail = prec;
                }

                delete to_remove; // Dealloca il nodo rimosso
                this->size--;     // Riduce la dimensione della lista
                return true;      // Elemento rimosso con successo
            }
            // Avanzo nella lista
            prec = curr;
            curr = curr->link;
        }

        return false; // Elemento non trovato nella lista
    }

    template <typename Data>
    void lasd::List<Data>::InsertAtBack(const Data &key){
        Node *newNode = new Node(key);
        if (head == nullptr)
        {
            // è il primo nodo che inserisco
            this->head = newNode;
        }
        else
        {
            // non è il primo
            this->tail->link = newNode;
        }
        this->tail = newNode;
        this->size++;
    }
    template <typename Data>
    void lasd::List<Data>::InsertAtBack(Data &&key)
    {
        //std::move converte value in r-value.
        Node *newNode = new Node(std::move(key));
        if (head == nullptr)
        {
            // è il primo nodo che inserisco
            this->head = newNode;
        }
        else{
            //non è il primo
            this->tail->link=newNode;
        }
        this->tail = newNode;
        this->size++;
    }
    template <typename Data>
    void lasd::List<Data>::InsertAtFront(const Data &k)
    {
        Node *newnode = new Node(k, head);
        this->head = newnode;
        if (this->tail == nullptr)
            this->tail = newnode;
        this->size++;
    }
    template <typename Data>
    void lasd::List<Data>::InsertAtFront(Data &&k)
    {
        Node *newnode = new Node(std::move(k), head);
        head = newnode;
        if(this->tail==nullptr)
            this->tail=newnode;
        this->size++;
    }
    template <typename Data>
    void lasd::List<Data>::RemoveFromFront()
    {
        if(this->Empty()){
            throw std::length_error("La Lista è vuota!"); 
        }
        Node *to_remove=this->head;
        head=to_remove->link;
        delete to_remove;
        this->size--;
        if (head == nullptr)
        {
            this->tail = nullptr;
        }
    }
    template <typename Data>
    Data lasd::List<Data>::FrontNRemove()
    {
        Data to_return;
        if (this->Empty())
        {
            throw std::length_error("La Lista è vuota!");
        }
        Node *to_remove = this->head;
        head = to_remove->link;
        to_return=to_remove->element;
        delete to_remove;
        this->size--;
        if (head == nullptr)
        {
            this->tail = nullptr;
        }
        return to_return;
    }
    template <typename Data>
    const Data &lasd::List<Data>::operator[](const unsigned long index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Non puoi accedere !");
        }
        Node *curr = this->head;
        for (unsigned long i = 0; i < index; i++)
            curr = curr->link;
        return curr->element;
    }
    template <typename Data>
    Data &lasd::List<Data>::operator[](const unsigned long index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Non puoi accedere !");
        }
        Node *curr = this->head;
        for (unsigned long i = 0; i < index; i++)
            curr = curr->link;
        return curr->element;
    }

    template<typename Data>
    const Data& lasd::List<Data>::Front() const{
        if(this->Empty())
        {
            throw std::length_error("La lista è vuota !");
        }
        return this->head->element;
    }
    template <typename Data>
    Data &lasd::List<Data>::Front()
    {
        if (this->Empty())
        {
            throw std::length_error("La lista è vuota !");
        }
        return this->head->element;
    }
    template <typename Data>
    const Data &lasd::List<Data>::Back() const
    {
        if (this->Empty())
        {
            throw std::length_error("La lista è vuota !");
        }
        return this->tail->element;
    }
    template <typename Data>
    Data &lasd::List<Data>::Back()
    {
        if (this->Empty())
        {
            throw std::length_error("La lista è vuota !");
        }
        return this->tail->element;
    }

    template <typename Data>
    lasd::List<Data>::~List()
    {
        Clear();
    }
    template <typename Data>
    void lasd::List<Data>::Clear()
    {
        struct Node *in_esame=this->head;
        while(in_esame != nullptr)
        {
            struct Node *prox=in_esame->link;
            delete in_esame;
            in_esame=prox;
        }
        this->size=0;
        this->head=nullptr;
        this->tail=nullptr;
    }

    template <typename Data>
    void lasd::List<Data>::Traverse(TraverseFun fun) const
    {
        PreOrderTraverse(fun);
    }
    template <typename Data>
    void lasd::List<Data>::PreOrderTraverse(TraverseFun fun) const
    {
        Node *in_esame= this->head;
        PreOrderTraverse(fun,in_esame);   
    }

    template <typename Data>
    void lasd::List<Data>::PostOrderTraverse(TraverseFun fun) const
    {
        Node *in_esame = this->head;
        PostOrderTraverse(fun,in_esame);
    }

    template <typename Data>
    void lasd::List<Data>::Map(MapFun fun)
    {
        PreOrderMap(fun);
    }
    template <typename Data>
    void lasd::List<Data>::PreOrderMap(MapFun fun)
    {
        Node *in_esame=this->head; 
        PreOrderMap(fun,in_esame);
    }

    template <typename Data>
    void lasd::List<Data>::PostOrderMap(MapFun fun)
    {
        Node *in_esame = this->head;
        PostOrderMap(fun, in_esame);
    }

    /*Auxiliary Member Functions (List) for TraverableContainer*/

    template<typename Data>
    void lasd::List<Data>::PreOrderTraverse(TraverseFun fun,Node * curr)const{
        while (curr != nullptr)
        {
            fun(curr->element);
            curr=curr->link;
        }
    }

    template <typename Data>
    void lasd::List<Data>::PostOrderTraverse(TraverseFun fun, Node *curr) const
    {
        if(curr == nullptr)
            return;
        PostOrderTraverse(fun,curr->link);
        fun(curr->element);
    }

    /*Auxiliary Member Functions (List) for MappableContainer*/
    template <typename Data>
    void lasd::List<Data>::PreOrderMap(MapFun fun, Node *curr)
    {
        while (curr != nullptr)
        {
            fun(curr->element);
            curr = curr->link;
        }
    }

    template <typename Data>
    void lasd::List<Data>::PostOrderMap(MapFun fun, Node *curr)
    {
        if (curr == nullptr)
            return;
        PostOrderMap(fun, curr->link);
        fun(curr->element);
    }
}

