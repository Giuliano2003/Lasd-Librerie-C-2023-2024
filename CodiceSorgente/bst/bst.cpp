#include"bst.hpp"
#include "../vector/vector.hpp"
namespace lasd {
   template <typename Data>
   lasd::BST<Data>::BST(const TraversableContainer<Data>& con) noexcept
   {
        con.Traverse([this](const Data &dat){
            this->Insert(dat);
        });
        this->size = con.Size();
   }

   template <typename Data>
   lasd::BST<Data>::BST(MappableContainer<Data> &&con) 
   {
        con.Map([this](Data &dat){
            this->Insert(std::move(dat));
        });
   }

   template <typename Data>
   lasd::BST<Data>::BST(const BST<Data>& othertree) noexcept:BinaryTreeLnk<Data>::BinaryTreeLnk(othertree)
   {
        this->size = othertree.Size();
   }

   template <typename Data>
   lasd::BST<Data>::BST(BST<Data> &&othertree) : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(othertree)){
        othertree.size = 0;
        othertree.root = nullptr;
   }

   template <typename Data>
   BST<Data>& lasd::BST<Data>::operator=(const BST<Data> &othertree) noexcept
   {
       lasd::BinaryTreeLnk<Data>::operator=(othertree);
       return *this;
   }

   template <typename Data>
   BST<Data> &lasd::BST<Data>::operator=(BST<Data> &&othertree)
   {
       lasd::BinaryTreeLnk<Data>::operator=(std::move(othertree));
       othertree.size = 0;
       othertree.root = nullptr;
       return *this;
   }
   template<typename Data>
   bool lasd::BST<Data>::operator==(const BST<Data> &other) const noexcept{
       if (this->size != other.Size())
           return false;
       lasd::BTInOrderIterator<Data> it(*this);
       lasd::BTInOrderIterator<Data> otherit(other);

       while (!it.Terminated())
       {
           if (*it != *otherit)
               return false;
           ++it;
           ++otherit;
        }
        return true;
   }
   template <typename Data>
   bool lasd::BST<Data>::operator!=(const BST<Data> &other) const noexcept
   {
       return !(*this == other);
   }
   template <typename Data>
   bool lasd::BST<Data>::Insert(const Data &k)
   {
       if (Exists(k))
       {              
           return false; // Return false if it's a duplicate
       }
       this->root = InsertHelp(this->root, k);
       this->size++;
       return true;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk* lasd::BST<Data>::InsertHelp(NodeLnk* T, const Data &k)
   {
        if(T == nullptr)
        {
            T= new NodeLnk(k);
        }
        else{
            if(k < T->Element())
            {
                T->left=InsertHelp(T->left,k);
            }
            else if(k > T->Element())
            {
                T->right=InsertHelp(T->right,k);
            }
        }
        return T;
   }

   template <typename Data>
   bool lasd::BST<Data>::Insert(Data &&k)
   {
       if (Exists(k))
       { 
           return false; // Return false if it's a duplicate
       }
       this->root = InsertHelp(this->root, std::move(k)); 
       this->size++;
       return true;                     
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::InsertHelp(NodeLnk *T,Data &&k)
   {
       if (T == nullptr)
       {
           T = new NodeLnk(std::move(k));
       }
       else
       {
           if (k < T->Element())
           {
               T->left=InsertHelp(T->left, k);
           }
           else if (k > T->Element())
           {
               T->right=InsertHelp(T->right, k);
           }
       }
       return T;
   }

   template <typename Data>
   bool lasd::BST<Data>::Remove(const Data &K)
   {
        if(Exists(K))
        {
            this->root=this->RemoveData(this->root,K);
            this->size--;
            return true;
        }
        else{
            return false;
        }
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::RemoveData(NodeLnk *T, const Data &K)
   {
       if (T == nullptr)
           return nullptr;
       if (T->Element() > K)
           T->left = RemoveData(T->left, K);
       else if (T->Element() < K)
           T->right = RemoveData(T->right, K);
       else
           T = DataNDelete(T);
       return T;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::DataNDelete(NodeLnk *T) noexcept
   {
       if (T == nullptr)
           return nullptr;

       if (T->left == nullptr)
       {
           T = Skip2Right(T);
       }
       else if (T->right == nullptr)
       {
           T = Skip2Left(T);
       }
       else
       {
           Data d;
           T->element = GetDeleteMin(T->right, T, d);
       }
       return T;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::Skip2Left(NodeLnk *T) noexcept
   {
       if (T != nullptr)
       {
           NodeLnk *y = T->left;
           delete T;
           T = nullptr;
           return y;
       }
       return nullptr;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::Skip2Right(NodeLnk *T) noexcept
   {
       if (T != nullptr)
       {
           NodeLnk *y = T->right;
           delete T;
           return y;
       }
        return nullptr;
   }

   template <typename Data>
   Data &lasd::BST<Data>::GetDeleteMin(NodeLnk *T, NodeLnk *P, Data &d)
   {
       if (T == nullptr)
       {
           // Caso in cui il nodo da eliminare sia il minimo
           d = P->Element();
           if (P->left == T)
           {
               P->left = nullptr;
           }
           else
           {
               P->right = nullptr;
           }
           delete T;
       }
       else if (T->left == nullptr)
       {
           d = T->Element();
           NodeLnk *y = Skip2Right(T);
           if (P->left == T)
           {
               P->left = y; // invece qui se scendo più in profondo
           }
           else
           {
               P->right = y; // entro qui se trovo subito il minimo a destra
           }
       }
       else
       {
           d = GetDeleteMin(T->left, T, d);
       }
       return d;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::FindPointerTo(NodeLnk *T, const Data &key) noexcept
   {
       if (T != nullptr)
       {
           if (key < T->Element())
           {
               return FindPointerTo(T->left, key);
           }
           else if (key > T->Element())
           {
               return FindPointerTo(T->right, key);
           }
           else
           {
               return T; // key == element
           }
       }
       return nullptr;
   }

   template <typename Data>
   const typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::FindPointerTo(const NodeLnk *T, const Data &key) const noexcept
   {
       if (T != nullptr)
       {
           if (key < T->Element())
           {
               return FindPointerTo(T->left, key);
           }
           else if (key > T->Element())
           {
               return FindPointerTo(T->right, key);
           }
           else
           {
               return T; // key == element
           }
       }
       return nullptr;
   }

   template <typename Data>
   Data& lasd::BST<Data>::DetachMin(NodeLnk *T) const noexcept
   {
       if(T->left == nullptr){
            return T->element;
       }
       else{
        return DetachMin(T->left);
       }
   }

   template <typename Data>
   void lasd::BST<Data>::RemoveMin(){
        if(this->root == nullptr)
            throw std::length_error("Non c'è minimo!");
        Data & min = this->DetachMin(this->root);
        this->root=this->RemoveData(this->root,min);
        this->size--;
   }

   template <typename Data>
   void lasd::BST<Data>::RemoveMax()
   {
       if (this->root == nullptr)
           throw std::length_error("Non c'è minimo!");
       Data &max = this->DetachMax(this->root);
       this->root=this->RemoveData(this->root,max);
       this->size--;
   }

   template <typename Data>
   void lasd::BST<Data>::RemoveSuccessor(const Data &key)
   {
       if (this->root == nullptr)
           throw std::length_error("Non c'è Successore");
       NodeLnk *successor = nullptr;
       successor=FindPointerToSuccessor(this->root,key,successor);
       if(successor == nullptr)
           throw std::length_error("Non c'è Successore");
        this->root=this->RemoveData(this->root,successor->Element());
        this->size--;
   }

   template <typename Data>
   void lasd::BST<Data>::RemovePredecessor(const Data &key)
   {
       if (this->root == nullptr)
           throw std::length_error("Non c'è Predecessore");
       NodeLnk *predecessor = nullptr;
       predecessor = this->FindPointerToPredecessor(this->root, key, predecessor);
       if (predecessor == nullptr)
           throw std::length_error("Non c'è Predecessore");
       this->root=this->RemoveData(this->root, predecessor->Element());
       this->size--;
   }

   template <typename Data>
   Data lasd::BST<Data>::MinNRemove()
   {
       if(this->root == nullptr)
       {
           throw std::length_error("Albero vuoto!");
       }
       Data min = this->DetachMin(this->root);
       this->root = this->RemoveData(this->root,min);
       this->size--;
       return min;
   }

   template <typename Data>
   Data lasd::BST<Data>::MaxNRemove()
   {
        if(this->root == nullptr)
        {
            throw std::length_error("Albero vuoto!");
        }
       Data max = this->DetachMax(this->root);
       this->root = this->RemoveData(this->root,max);
       this->size--;
       return max;
   }

   template <typename Data>
   Data lasd::BST<Data>::PredecessorNRemove(const Data &key)
   {
       NodeLnk * prec = nullptr;
       prec=this->FindPointerToPredecessor(this->root,key,prec);
       if (prec == nullptr)
           throw std::length_error("Non trovato!");
       Data pre = prec->Element();
       this->Remove(prec->Element());
       return pre;
   }

   template <typename Data>
   Data lasd::BST<Data>::SuccessorNRemove(const Data &key)
   {
        NodeLnk *succ = nullptr;
        succ=this->FindPointerToSuccessor(this->root,key,succ);
        if(succ == nullptr)
            throw std::length_error("Non trovato!");
        Data succer = succ->Element();
        this->Remove(succ->Element());
        return succer;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk const *lasd::BST<Data>::FindPointerToMin(const NodeLnk *T) const noexcept
   {
       if (!T->HasLeftChild())
       {
           return T;
       }
       else
       {
           return FindPointerToMin(T->left);
       }
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk* lasd::BST<Data>::FindPointerToMin(NodeLnk *T) noexcept
   {
       if (!T->HasLeftChild())
       {
           return T;
       }
       else
       {
           return FindPointerToMin(T->left);
       }
   }

   template <typename Data>
   Data &lasd::BST<Data>::DetachMax(NodeLnk *T) const noexcept
   {
       if (!T->HasRightChild())
       {
           return T->element;
       }
       else
       {
           return DetachMax(T->right);
       }
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk const *lasd::BST<Data>::FindPointerToMax(const NodeLnk *T) const noexcept
   {
       if (!T->HasRightChild())
       {
           return T;
       }
       else
       {
           return FindPointerToMax(T->right);
       }
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::FindPointerToMax(NodeLnk *T) noexcept
   {
       if (!T->HasRightChild())
       {
           return T;
       }
       else
       {
           return FindPointerToMax(T->right);
       }
   }

   template <typename Data>
   const Data &lasd::BST<Data>::Predecessor(const Data &k) const
   {
       const NodeLnk *predecessor = nullptr;
       predecessor = FindPointerToPredecessor(this->root,k,predecessor);
       if (predecessor != nullptr)
       {
           return predecessor->Element();
       }
       else
       {
           throw std::length_error("Predecessore Non Trovato !");
       }
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::FindPointerToPredecessor(NodeLnk *T, const Data &k, NodeLnk *p) noexcept
   {
       if (T != nullptr)
       {
           if (k > T->Element())
           {
               p = FindPointerToPredecessor(T->right, k, T);
           }
           else if (k < T->Element())
           {
               p = FindPointerToPredecessor(T->left, k, p);
           }
           else
           {
               if (T->left != nullptr)
               {
                   p = FindPointerToMax(T->left);
               }
               else
               {
                   return p;
               }
           }
       }
       return p;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk const *lasd::BST<Data>::FindPointerToPredecessor(const NodeLnk *T, const Data &k, const NodeLnk *p) const noexcept
   {
       if (T != nullptr)
       {
           if (k > T->Element())
           {
               p = this->FindPointerToPredecessor(T->right, k, T);
           }
           else if (k < T->Element())
           {
               p = this->FindPointerToPredecessor(T->left, k, p);
           }
           else
           {
               if (T->left != nullptr)
               {
                   p = FindPointerToMax(T->left);
               }
               else
               {
                    return p;
               }
           }
       }
       return p;
   }

   template <typename Data>
   const Data &lasd::BST<Data>::Successor(const Data &k) const
   {
       const NodeLnk *successor = nullptr;
       successor=this->FindPointerToSuccessor(this->root, k, successor);
       if(successor != nullptr)
       {
            return successor->Element();
       }
       else{
            throw std::length_error("Successore Non Trovato !");
       }
   }

   

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BST<Data>::FindPointerToSuccessor(NodeLnk *T, const Data &k, NodeLnk *s) noexcept
   {
       if (T != nullptr)
       {
           if (k < T->Element())
           {
               s = FindPointerToSuccessor(T->left, k, T);
           }
           else if (k > T->Element())
           {
               s = FindPointerToSuccessor(T->right, k, s);
           }
           else{ // k=element
                if(T->right != nullptr){
                    s=FindPointerToMin(T->right);
                }else{
                    return s;
                }
           }
       }
       return s;
   }

   template <typename Data>
   typename lasd::BinaryTreeLnk<Data>::NodeLnk const *lasd::BST<Data>::FindPointerToSuccessor(const NodeLnk *T, const Data &k, const NodeLnk *s)const noexcept
   {
       if (T != nullptr)
       {
           if (k < T->Element())
           {
               s = FindPointerToSuccessor(T->left, k, T);
           }
           else if (k > T->Element())
           {
               s = FindPointerToSuccessor(T->right, k, s);
           }
           else
           { // k=element
               if (T->right != nullptr)
               {
                   s = FindPointerToMin(T->right);
               }
               else
               {
                   return s;
               }
           }
       }
       return s;
   }

   template <typename Data>
   bool lasd::BST<Data>::Exists(const Data &k) const noexcept
   {
    if(this->root != nullptr)
    {
        const NodeLnk* T = FindPointerTo(this->root,k);
        return (T != nullptr);
    }
    return false;     
   }

   template <typename Data>
   void lasd::BST<Data>::Clear()
   {
       if(this->root != nullptr){
            BinaryTreeLnk<Data>::Clear();
       }
   }

   template <typename Data>
   BST<Data>::~BST()
   {
     this->Clear();
   }
}


