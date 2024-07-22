#include "binarytreelnk.hpp"
#include "../../vector/vector.hpp"

namespace lasd
{
    template <typename Data>
    lasd::BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> &other) noexcept
    {
        if (!other.Empty())
        {
            int index = 0;
            std::vector<Data> vec(other.Size());
            other.Traverse(
                [&index, &vec](const Data &dat)
                {
                    vec.operator[](index) = dat;
                    index++;
                });
            this->root = new NodeLnk(vec[0]);
            buildComplete(0, root, vec);
            this->size = other.Size();
        }
    }

    template <typename Data>
    lasd::BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> &&other)
    {
        if (!other.Empty())
        {
            int index = 0;
            std::vector<Data> vec(other.Size());
            other.Map(
                [&index, &vec](Data &dat)
                {
                    vec.operator[](index) = std::move(dat);
                    index++;
                });
            this->root = new NodeLnk(vec[0]);
            buildComplete(0, root, vec);
            this->size = other.Size();
        }
    }

    template <typename Data>
    lasd::BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &othertree) noexcept
    {
        if (othertree.root != nullptr)
        {
            this->root = CloneTreeC(this->root, othertree.root);
            this->size = othertree.Size();
        }
    }

    template <typename Data>
    lasd::BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&othertree)
    {
        std::swap(this->root, othertree.root);
        this->size = othertree.Size();
        othertree.Clear();
    }

    template <typename Data>
    typename lasd::BinaryTreeLnk<Data>::NodeLnk *lasd::BinaryTreeLnk<Data>::CloneTreeC(NodeLnk *T, NodeLnk *otherT) noexcept
    {
        if (otherT == nullptr)
        {
            return nullptr;
        }
        else
        {
            T = new NodeLnk(otherT->Element());
            T->left = CloneTreeC(T->left, otherT->left);
            T->right = CloneTreeC(T->right, otherT->right);
        }
        return T;
    }

    template <typename Data>
    void lasd::BinaryTreeLnk<Data>::Clear()
    {
        CleanTree(this->root);
        this->size = 0;
        this->root = nullptr;
    }

    template <typename Data>
    void lasd::BinaryTreeLnk<Data>::CleanTree(NodeLnk *T) noexcept
    {
        if (T != nullptr)
        {
            CleanTree(T->left);
            CleanTree(T->right);
            delete T;
        }
    }

    template <typename Data>
    BinaryTreeLnk<Data> &lasd::BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &othertree)
    {
        if (!othertree.Empty())
        {
            BinaryTreeLnk<Data> *tmpbt = new BinaryTreeLnk<Data>(othertree);
            std::swap(*tmpbt, *this);
            delete tmpbt;
            this->size = othertree.Size();
        }
        else
        {
            Clear();
        }
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &lasd::BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&othertree)
    {
        this->size = othertree.Size();
        std::swap(this->root, othertree.root);
        othertree.Clear();
        return *this;
    }

    template <typename Data>
    bool lasd::BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> &othertree) const noexcept
    {
        return lasd::BinaryTree<Data>::operator==(othertree);
    }

    template <typename Data>
    bool lasd::BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> &othertree) const noexcept
    {
        return lasd::BinaryTree<Data>::operator!=(othertree);
    }

    template <typename Data>
    void lasd::BinaryTreeLnk<Data>::buildComplete(unsigned long index, NodeLnk *nod, const std::vector<Data> &vec) noexcept
    {
        if ((index * 2) + 1 <= vec.size() - 1)
        {
            nod->left = new NodeLnk(vec[(index * 2) + 1]);
            buildComplete((index * 2) + 1, nod->left, vec);
        }
        if ((index * 2) + 2 <= vec.size() - 1)
        {
            nod->right = new NodeLnk(vec[(index * 2) + 2]);
            buildComplete((index * 2) + 2, nod->right, vec);
        }
    }


    template <typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk()
    {
        this->Clear();
    }
};
