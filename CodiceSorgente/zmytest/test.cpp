#include "test.hpp"

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"
#include "../iterator/iterator.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/stack/stack.hpp"
#include "../zlasdtest/queue/queue.hpp"
#include "../zlasdtest/binarytree/binarytree.hpp"
#include "../zlasdtest/bst/bst.hpp"
#include "../zlasdtest/iterator/iterator.hpp"
#include "../zlasdtest/hashtable/hashtable.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

namespace lasd::test
{

    template <typename Data>
    void IteratorPreOrderEqual(uint &testnum, uint &testerr, const lasd::BTPreOrderIterator<Data> &itr1,
                               const lasd::BTPreOrderIterator<Data> &itr2, bool chk)
    {
        bool res;
        bool tst;
        testnum++;
        try
        {
            std::cout << " " << testnum << " (" << testerr << ") The two iterators are "
                      << ((res = (itr1 == itr2)) ? "equal" : "not equal") << " : ";
            std::cout << ((tst = (res == chk)) ? "Correct" : "Error") << "!" << endl;
        }
        catch (std::exception &exc)
        {
            tst = false;
            std::cout << std::endl
                      << "Wrong exception: " << exc.what() << "!" << std::endl;
        }
        testerr += (1 - (uint)tst);
    }

    template <typename Data>
    void IteratorPostOrderEqual(uint &testnum, uint &testerr, const lasd::BTPostOrderIterator<Data> &itr1,
                                const lasd::BTPostOrderIterator<Data> &itr2, bool chk)
    {
        bool res;
        bool tst;
        testnum++;
        try
        {
            std::cout << " " << testnum << " (" << testerr << ") The two iterators are "
                      << ((res = (itr1 == itr2)) ? "equal" : "not equal") << " : ";
            std::cout << ((tst = (res == chk)) ? "Correct" : "Error") << "!" << endl;
        }
        catch (std::exception &exc)
        {
            tst = false;
            std::cout << std::endl
                      << "Wrong exception: " << exc.what() << "!" << std::endl;
        }
        testerr += (1 - (uint)tst);
    }

    template <typename Data>
    void IteratorInOrderEqual(uint &testnum, uint &testerr, const lasd::BTInOrderIterator<Data> &itr1,
                              const lasd::BTInOrderIterator<Data> &itr2, bool chk)
    {
        bool res;
        bool tst;
        testnum++;
        try
        {
            std::cout << " " << testnum << " (" << testerr << ") The two iterators are "
                      << ((res = (itr1 == itr2)) ? "equal" : "not equal") << " : ";
            std::cout << ((tst = (res == chk)) ? "Correct" : "Error") << "!" << endl;
        }
        catch (std::exception &exc)
        {
            tst = false;
            std::cout << std::endl
                      << "Wrong exception: " << exc.what() << "!" << std::endl;
        }
        testerr += (1 - (uint)tst);
    }

    template <typename Data>
    void IteratorBreadthEqual(uint &testnum, uint &testerr, const lasd::BTBreadthIterator<Data> &itr1,
                              const lasd::BTBreadthIterator<Data> &itr2, bool chk)
    {
        bool res;
        bool tst;
        testnum++;
        try
        {
            std::cout << " " << testnum << " (" << testerr << ") The two iterators are "
                      << ((res = (itr1 == itr2)) ? "equal" : "not equal") << " : ";
            std::cout << ((tst = (res == chk)) ? "Correct" : "Error") << "!" << endl;
        }
        catch (std::exception &exc)
        {
            tst = false;
            std::cout << std::endl
                      << "Wrong exception: " << exc.what() << "!" << std::endl;
        }
        testerr += (1 - (uint)tst);
    }

    template <typename Data>
    void SetDefaultValue(Data &data)
    {
        data = {};
    }
    /* ************************************************************************** */

    using uint = unsigned int;

    void testHTCLSADR(uint &ltestnum, uint &ltesterr)
    {
        try
        {
            {
                lasd::HashTableClsAdr<int> ht1;

                for (ulong i = 0; i < 100; i++)
                {
                    InsertM(ltestnum, ltesterr, ht1, (int)i);
                }
                for (ulong i = 0; i < 100; i++)
                {
                    Exists(ltestnum, ltesterr, ht1, true, (int)i);
                }
                Remove(ltestnum, ltesterr, ht1, 20);
                Exists(ltestnum, ltesterr, ht1, false, 20);

                lasd::HashTableClsAdr<int> ht2(ht1);
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2.Clear();

                NonEqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2 = ht1;
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2.Resize(100);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
            }
            {
                lasd::HashTableClsAdr<int> ht1(10), ht2(20);
                InsertM(ltestnum, ltesterr, ht1, 104);
                Exists(ltestnum, ltesterr, ht1, true, 104);
                Exists(ltestnum, ltesterr, ht1, false, 10);

                InsertM(ltestnum, ltesterr, ht2, 204);
                Exists(ltestnum, ltesterr, ht2, true, 204);
                Exists(ltestnum, ltesterr, ht2, false, 10);

                ht1 = move(ht2);
                Exists(ltestnum, ltesterr, ht1, false, 104);
                Exists(ltestnum, ltesterr, ht1, true, 204);
                Exists(ltestnum, ltesterr, ht2, false, 204); //
                Exists(ltestnum, ltesterr, ht2, true, 104);

                lasd::HashTableClsAdr<int> ht3(move(ht1));
                Exists(ltestnum, ltesterr, ht3, false, 104);
                Exists(ltestnum, ltesterr, ht3, true, 204);
                Exists(ltestnum, ltesterr, ht1, false, 204);
                Exists(ltestnum, ltesterr, ht1, false, 104);
            }
            {
                lasd::HashTableClsAdr<int> ht0(0);
                Remove(ltestnum, ltesterr, ht0, false, 20);
                InsertM(ltestnum, ltesterr, ht0, 20);
                Remove(ltestnum, ltesterr, ht0, true, 20);
                lasd::HashTableClsAdr<int> ht1;
                ht1.Clear();
                Remove(ltestnum, ltesterr, ht1, 20);
                lasd::HashTableClsAdr<int> ht2(ht1);
                ht2.Clear();
                ht1 = move(ht2);
                ht2 = move(ht1);
                ht1.Clear();
                ht1.Clear();
                ht2.Clear();
                ht2.Clear();

                for (ulong i = 0; i < 200; i++)
                {
                    InsertM(ltestnum, ltesterr, ht1, (int)i * 10);
                    ht1.Resize(i * 2);
                }

                Size(ltestnum, ltesterr, ht1, false, 200);
            }
            {
                lasd::List<int> l;
                lasd::HashTableClsAdr<int> ht1(l), ht2(move(l));

                EqualHT(ltestnum, ltesterr, ht1, ht2);
            }
            {

                lasd::List<int> l;
                for (ulong i = 0; i < 10; i++)
                {
                    InsertM(ltestnum, ltesterr, l, true, (int)i);
                }

                lasd::HashTableClsAdr<int> ht1(71, l);

                lasd::HashTableClsAdr<int> ht2(91, move(l));

                EqualHT(ltestnum, ltesterr, ht1, ht2);
                Remove(ltestnum, ltesterr, ht1, 1);
                NonEqualHT(ltestnum, ltesterr, ht1, ht2);
            }
            {

                lasd::List<string> l;
                InsertM(ltestnum, ltesterr, l, true, string("ABBAA"));
                InsertM(ltestnum, ltesterr, l, true, string("BBAAA"));
                InsertM(ltestnum, ltesterr, l, true, string("ABABA"));

                lasd::HashTableClsAdr<string> ht1(l);
                Exists(ltestnum, ltesterr, ht1, true, string("ABBAA"));
                Exists(ltestnum, ltesterr, ht1, true, string("BBAAA"));
                Exists(ltestnum, ltesterr, ht1, true, string("ABABA"));
                Exists(ltestnum, ltesterr, ht1, false, string("AAABB"));
            }
            {

                lasd::List<double> l;
                InsertM(ltestnum, ltesterr, l, true, 2.1);
                InsertM(ltestnum, ltesterr, l, true, 1.2);
                InsertM(ltestnum, ltesterr, l, true, 2.0);
                InsertM(ltestnum, ltesterr, l, true, 3.4);
                InsertM(ltestnum, ltesterr, l, true, 1.754);

                lasd::HashTableClsAdr<double> ht1(move(l));
                Exists(ltestnum, ltesterr, ht1, true, 2.1);
                Exists(ltestnum, ltesterr, ht1, true, 1.2);
                Exists(ltestnum, ltesterr, ht1, true, 2.0);
                Exists(ltestnum, ltesterr, ht1, true, 3.4);
                Exists(ltestnum, ltesterr, ht1, true, 1.754);
                Exists(ltestnum, ltesterr, ht1, false, 10.2);
            }
            {

                lasd::List<int> l;
                for (ulong i = 0; i < 100; i += 2)
                {
                    InsertM(ltestnum, ltesterr, l, (int)i * 11);
                }
                lasd::HashTableClsAdr<int> ht1, ht2(400), ht3(400, l), ht4(l);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                NonEqualHT(ltestnum, ltesterr, ht1, ht3);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht1 = move(ht2);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                ht2 = move(ht1);
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht3 = move(ht4);
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                ht4 = move(ht3);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht1 = move(ht3);
                ht2 = move(ht4);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                NonEqualHT(ltestnum, ltesterr, ht1, ht3);

                ht3.Clear();
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                ht4.Clear();
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                InsertM(ltestnum, ltesterr, ht3, 127);
                InsertM(ltestnum, ltesterr, ht4, 127);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht3.Clear();
                NonEqualHT(ltestnum, ltesterr, ht3, ht4);

                lasd::HashTableClsAdr<int> ht5(ht3);
                InsertM(ltestnum, ltesterr, ht5, 127);
                EqualHT(ltestnum, ltesterr, ht5, ht4);

                ht3 = ht5;
                EqualHT(ltestnum, ltesterr, ht3, ht5);

                ht3.Resize(0);
                Exists(ltestnum, ltesterr, ht3, false, 127);
                NonEqualHT(ltestnum, ltesterr, ht3, ht5);
                ht3.Resize(40);
            }
        }
        catch (...)
        {
            ltestnum++;
            ltesterr++;
            cout << endl
                 << "Unmanaged error! " << endl;
        }
    }

    void testHTOPNADR(uint &ltestnum, uint &ltesterr)
    {
        try
        {
            lasd::HashTableOpnAdr<int> h1(0);
            Remove(ltestnum, ltesterr, h1, false, 20);
            Remove(ltestnum, ltesterr, h1, false, 20);

            InsertM(ltestnum, ltesterr, h1, 104);
            InsertM(ltestnum, ltesterr, h1, 111);
            InsertM(ltestnum, ltesterr, h1, 1041);
            InsertM(ltestnum, ltesterr, h1, 1011);
            InsertM(ltestnum, ltesterr, h1, 110);

            Size(ltestnum, ltesterr, h1, true, 5);

            Exists(ltestnum, ltesterr, h1, true, 104);
            Exists(ltestnum, ltesterr, h1, true, 111);
            Exists(ltestnum, ltesterr, h1, true, 1041);
            Exists(ltestnum, ltesterr, h1, true, 1011);
            Exists(ltestnum, ltesterr, h1, true, 110);

            h1.Clear();

            Size(ltestnum, ltesterr, h1, true, 0);

            Exists(ltestnum, ltesterr, h1, false, 104);
            Exists(ltestnum, ltesterr, h1, false, 111);
            Exists(ltestnum, ltesterr, h1, false, 1041);
            Exists(ltestnum, ltesterr, h1, false, 1011);
            Exists(ltestnum, ltesterr, h1, false, 110);

            Remove(ltestnum, ltesterr, h1, false, 20);
            Remove(ltestnum, ltesterr, h1, false, 20);

            h1.Resize(1);

            Remove(ltestnum, ltesterr, h1, false, 20);
            Remove(ltestnum, ltesterr, h1, false, 20);

            Exists(ltestnum, ltesterr, h1, false, 104);

            h1.Resize(2);

            Size(ltestnum, ltesterr, h1, true, 0);

            h1.Resize(10);

            Size(ltestnum, ltesterr, h1, true, 0);

            Exists(ltestnum, ltesterr, h1, false, 104);

            h1.Resize(0);

            InsertM(ltestnum, ltesterr, h1, 104);
            InsertM(ltestnum, ltesterr, h1, 111);
            InsertM(ltestnum, ltesterr, h1, 1041);
            InsertM(ltestnum, ltesterr, h1, 1011);
            InsertM(ltestnum, ltesterr, h1, 110);

            Size(ltestnum, ltesterr, h1, true, 5);

            lasd::HashTableOpnAdr<int> h2(0);

            h2 = h1;

            EqualHT(ltestnum, ltesterr, h2, h1);

            h2.Clear();

            h1 = h2;

            EqualHT(ltestnum, ltesterr, h2, h1);

            h1.Resize(67);

            h2 = h1;

            EqualHT(ltestnum, ltesterr, h2, h1);

            lasd::HashTableOpnAdr<int> h3;

            h1 = move(h3);

            Size(ltestnum, ltesterr, h1, true, 0);

            h1.Clear();

            h1.Resize(0);
            lasd::Vector<int> vec(100);

            for (unsigned long i = 0; i < vec.Size(); i++)
            {
                vec[i] = i * 3;
            }

            for (unsigned long i = 0; i < vec.Size(); i++)
            {
                h1.Insert(vec[i] + 2 * 3 * i + 1);
                h1.Resize(i + 2);
            }

            Size(ltestnum, ltesterr, h1, true, 100);

            lasd::HashTableOpnAdr<int> h4;

            h4 = h1;

            EqualHT(ltestnum, ltesterr, h4, h1);

            Remove(ltestnum, ltesterr, h1, true, 820);
            Remove(ltestnum, ltesterr, h1, true, 676);
            Remove(ltestnum, ltesterr, h1, true, 55);
            Remove(ltestnum, ltesterr, h1, true, 541);
            Remove(ltestnum, ltesterr, h1, true, 613);
            Remove(ltestnum, ltesterr, h1, true, 343);

            NonEqualHT(ltestnum, ltesterr, h4, h1);

            h1.Resize(203);

            Size(ltestnum, ltesterr, h1, true, 94);

            h1.Resize(67);

            Size(ltestnum, ltesterr, h1, true, 94);

            h4 = h1;

            h1.Clear();

            Remove(ltestnum, ltesterr, h1, false, 343);

            Exists(ltestnum, ltesterr, h1, false, 820);
            Exists(ltestnum, ltesterr, h1, false, 55);
            Exists(ltestnum, ltesterr, h1, false, 613);

            lasd::HashTableOpnAdr<int> h6(0);

            Exists(ltestnum, ltesterr, h6, false, 820);

            h6.Clear();

            Remove(ltestnum, ltesterr, h6, false, 343);

            h6.Resize(0);

            Remove(ltestnum, ltesterr, h6, false, 343);

            Size(ltestnum, ltesterr, h6, true, 0);

            h6.Resize(0);

            lasd::List<int> list;

            for (int i = 0; i < 100; i++)
            {
                list.InsertAtBack(i * 100 + 1 * 5);
            }

            {
                lasd::HashTableOpnAdr<int> h1(3, list);
                Size(ltestnum, ltesterr, h1, true, 100);
            }
            {
                lasd::HashTableOpnAdr<int> ht1;

                for (ulong i = 0; i < 100; i++)
                {
                    InsertM(ltestnum, ltesterr, ht1, (int)i);
                }
                for (ulong i = 0; i < 100; i++)
                {
                    Exists(ltestnum, ltesterr, ht1, true, (int)i);
                }
                Remove(ltestnum, ltesterr, ht1, 20);
                Exists(ltestnum, ltesterr, ht1, false, 20);

                lasd::HashTableOpnAdr<int> ht2(ht1);
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2.Clear();

                NonEqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2 = ht1;
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht2.Resize(100);
                EqualHT(ltestnum, ltesterr, ht1, ht2); //
            }

            {
                lasd::HashTableOpnAdr<int> ht1(10), ht2(20);
                InsertM(ltestnum, ltesterr, ht1, 104);
                Exists(ltestnum, ltesterr, ht1, true, 104);
                Exists(ltestnum, ltesterr, ht1, false, 10);

                InsertM(ltestnum, ltesterr, ht2, 204);
                Exists(ltestnum, ltesterr, ht2, true, 204);
                Exists(ltestnum, ltesterr, ht2, false, 10);

                ht1 = move(ht2);
                Exists(ltestnum, ltesterr, ht1, false, 104);
                Exists(ltestnum, ltesterr, ht1, true, 204);
                Exists(ltestnum, ltesterr, ht2, false, 204); //
                Exists(ltestnum, ltesterr, ht2, true, 104);

                lasd::HashTableOpnAdr<int> ht3(move(ht1));
                Exists(ltestnum, ltesterr, ht3, false, 104);
                Exists(ltestnum, ltesterr, ht3, true, 204);
                Exists(ltestnum, ltesterr, ht1, false, 204);
                Exists(ltestnum, ltesterr, ht1, false, 104);
            }

            {
                lasd::HashTableOpnAdr<int> ht0(0);
                Remove(ltestnum, ltesterr, ht0, false, 20);
                InsertM(ltestnum, ltesterr, ht0, 20);
                Remove(ltestnum, ltesterr, ht0, true, 20);
                lasd::HashTableOpnAdr<int> ht1;
                ht1.Clear();
                Remove(ltestnum, ltesterr, ht1, 20);
                lasd::HashTableOpnAdr<int> ht2(ht1);
                ht2.Clear();
                ht1 = move(ht2);
                ht2 = move(ht1);
                ht1.Clear();
                ht1.Clear();
                ht2.Clear();
                ht2.Clear();

                for (ulong i = 0; i < 200; i++)
                {
                    InsertM(ltestnum, ltesterr, ht1, (int)i * 10);
                    ht1.Resize(i * 2);
                }
            }

            {

                lasd::List<int> l;
                for (ulong i = 0; i < 10; i++)
                {
                    InsertM(ltestnum, ltesterr, l, true, (int)i);
                }

                lasd::HashTableOpnAdr<int> ht1(71, l);

                lasd::HashTableOpnAdr<int> ht2(91, move(l));

                EqualHT(ltestnum, ltesterr, ht1, ht2);
                Remove(ltestnum, ltesterr, ht1, 1);
                NonEqualHT(ltestnum, ltesterr, ht1, ht2);
            }

            {

                lasd::List<string> l;
                InsertM(ltestnum, ltesterr, l, true, string("ABBAA"));
                InsertM(ltestnum, ltesterr, l, true, string("BBAAA"));
                InsertM(ltestnum, ltesterr, l, true, string("ABABA"));

                lasd::HashTableOpnAdr<string> ht1(l);
                Exists(ltestnum, ltesterr, ht1, true, string("ABBAA"));
                Exists(ltestnum, ltesterr, ht1, true, string("BBAAA"));
                Exists(ltestnum, ltesterr, ht1, true, string("ABABA"));
                Exists(ltestnum, ltesterr, ht1, false, string("AAABB"));
            }

            {

                lasd::List<double> l;
                InsertM(ltestnum, ltesterr, l, true, 2.1);
                InsertM(ltestnum, ltesterr, l, true, 1.2);
                InsertM(ltestnum, ltesterr, l, true, 2.0);
                InsertM(ltestnum, ltesterr, l, true, 3.4);
                InsertM(ltestnum, ltesterr, l, true, 1.754);

                lasd::HashTableOpnAdr<double> ht1(move(l));
                Exists(ltestnum, ltesterr, ht1, true, 2.1);
                Exists(ltestnum, ltesterr, ht1, true, 1.2);
                Exists(ltestnum, ltesterr, ht1, true, 2.0);
                Exists(ltestnum, ltesterr, ht1, true, 3.4);
                Exists(ltestnum, ltesterr, ht1, true, 1.754);
                Exists(ltestnum, ltesterr, ht1, false, 10.2);
            }
            {

                lasd::List<int> l;
                for (ulong i = 0; i < 100; i += 2)
                {
                    InsertM(ltestnum, ltesterr, l, (int)i * 11);
                }
                lasd::HashTableOpnAdr<int> ht1, ht2(400), ht3(400, l), ht4(l);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                NonEqualHT(ltestnum, ltesterr, ht1, ht3);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht1 = move(ht2);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                ht2 = move(ht1);
                EqualHT(ltestnum, ltesterr, ht1, ht2);

                ht3 = move(ht4);
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                ht4 = move(ht3);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht1 = move(ht3);
                ht2 = move(ht4);
                EqualHT(ltestnum, ltesterr, ht1, ht2);
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                NonEqualHT(ltestnum, ltesterr, ht1, ht3);

                ht3.Clear();
                EqualHT(ltestnum, ltesterr, ht3, ht4);
                ht4.Clear();
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                InsertM(ltestnum, ltesterr, ht3, 127);
                InsertM(ltestnum, ltesterr, ht4, 127);
                EqualHT(ltestnum, ltesterr, ht3, ht4);

                ht3.Clear();
                NonEqualHT(ltestnum, ltesterr, ht3, ht4);

                lasd::HashTableOpnAdr<int> ht5(ht3);
                InsertM(ltestnum, ltesterr, ht5, 127);
                EqualHT(ltestnum, ltesterr, ht5, ht4);

                ht3 = ht5;
                EqualHT(ltestnum, ltesterr, ht3, ht5);

                ht3.Resize(0);
                Exists(ltestnum, ltesterr, ht3, false, 127);
                NonEqualHT(ltestnum, ltesterr, ht3, ht5);
                ht3.Resize(40);
            }

            {
                lasd::List<int> l;
                for (int i = 0; i < 100; i++)
                {
                    l.InsertAtFront(i * 1000 + 231);
                }

                lasd::HashTableOpnAdr<int> h1(1, l);

                Size(ltestnum, ltesterr, h1, true, 100);

                h1.Resize(101);

                Size(ltestnum, ltesterr, h1, true, 100);

                lasd::HashTableOpnAdr<int> h2;

                h2 = std::move(h1);

                h1.Resize(0);

                h1.Clear();

                lasd::HashTableOpnAdr<int> h3(h2);

                h2.Clear();

                h2.Resize(100);

                Size(ltestnum, ltesterr, h2, true, 0);

                int a = 0;
                for (unsigned long i = 0; i < 100; i++)
                {
                    a = i;
                    h2.Resize(i * 4 + 5);
                    h2.Resize(i);
                    InsertM(ltestnum, ltesterr, h2, std::move(a));
                }

                Size(ltestnum, ltesterr, h2, true, 100);
            }

            {
                lasd::HashTableOpnAdr<int> h1;
                h1.Clear();
                h1.Resize(0);
                Size(ltestnum, ltesterr, h1, true, 0);
                for (int i = 0; i < 100; i++)
                {
                    InsertM(ltestnum, ltesterr, h1, i * 2 + 43);
                }
                Size(ltestnum, ltesterr, h1, true, 100);
                lasd::HashTableOpnAdr<int> h2;
                h2 = h1;
                h1.Resize(30);
                h2.Resize(30);
                EqualHT(ltestnum, ltesterr, h1, h2);
                for (int i = 0; i < 100; i++)
                {
                    Remove(ltestnum, ltesterr, h1, i * 2 + 43);
                }
                Size(ltestnum, ltesterr, h1, true, 0);
                h1.Clear();
                Size(ltestnum, ltesterr, h1, true, 0);
                Remove(ltestnum, ltesterr, h1, false, 0);
            }

            {
                lasd::HashTableOpnAdr<int> h1(4);
                h1.Clear();
                Size(ltestnum, ltesterr, h1, true, 0);
                lasd::HashTableOpnAdr<int> h3(h1);
                lasd::HashTableOpnAdr<int> h2(std::move(h1));
                lasd::Vector<int> vec;
                lasd::Vector<int> vec2;
                lasd::Vector<int> vec3;
                lasd::HashTableOpnAdr<int> h4(vec);

                lasd::HashTableOpnAdr<int> h5(std::move(vec));

                lasd::HashTableOpnAdr<int> h6(6, vec2);

                Size(ltestnum, ltesterr, h6, true, 0);

                lasd::HashTableOpnAdr<int> h7(7, std::move(vec2));

                Size(ltestnum, ltesterr, h7, true, 0);

                h6 = h7;

                EqualHT(ltestnum, ltesterr, h6, h7);

                h6 = std::move(h7);
            }

            {
                lasd::HashTableOpnAdr<int> h1(4);
                InsertM(ltestnum, ltesterr, h1, 567);
                InsertM(ltestnum, ltesterr, h1, 568);
                InsertM(ltestnum, ltesterr, h1, 569);
                Size(ltestnum, ltesterr, h1, true, 3);
                Exists(ltestnum, ltesterr, h1, true, 567);
                Exists(ltestnum, ltesterr, h1, true, 568);
                Exists(ltestnum, ltesterr, h1, true, 569);

                h1.Resize(1);
                Exists(ltestnum, ltesterr, h1, true, 567);
                Exists(ltestnum, ltesterr, h1, true, 568);
                Exists(ltestnum, ltesterr, h1, true, 569);

                Remove(ltestnum, ltesterr, h1, true, 567);
                Remove(ltestnum, ltesterr, h1, true, 568);

                Exists(ltestnum, ltesterr, h1, false, 567);
                Exists(ltestnum, ltesterr, h1, false, 568);
                Exists(ltestnum, ltesterr, h1, true, 569);
            }
        }
        catch (...)
        {
            ltestnum++;
            ltesterr++;
            cout << endl
                 << "Unmanaged error! " << endl;
        }
    }

    void mytestHashTableInt(uint &testnum, uint &testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        cout << endl
             << "Begin of HashTable<int> Test" << endl;
        try
        {
            lasd::Vector<int> vec(350);
            for (int idx = 0; idx < 350; idx++)
            {
                vec[idx] = pow(-3, idx % 11) * ((71 * idx + 39) % 193);
                idx++;
                vec[idx] = pow(-5, idx % 7) * ((71 * idx + 39) % 193);
            }

            {
                lasd::HashTableClsAdr<int> ht;
                Empty(loctestnum, loctesterr, ht, true);
                InsertAllC(loctestnum, loctesterr, ht, false, vec);
                Size(loctestnum, loctesterr, ht, true, 345);

                ht.Clear();
                Empty(loctestnum, loctesterr, ht, true);
                ht.Resize(30);

                for (int i = 0; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 1; i < 350; i += 2)
                {
                    if (vec[i] == 44 || vec[i] == 0 || vec[i] == 54 || vec[i] == 75 || vec[i] == 93)
                    {
                        InsertC(loctestnum, loctesterr, ht, false, vec[i]);
                    }
                    else
                    {
                        InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                    }
                }
                Size(loctestnum, loctesterr, ht, true, 345);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                Remove(loctestnum, loctesterr, ht, true, 44);
                Remove(loctestnum, loctesterr, ht, true, 0);
                Remove(loctestnum, loctesterr, ht, true, 54);
                Remove(loctestnum, loctesterr, ht, true, 75);
                Remove(loctestnum, loctesterr, ht, true, 93);
                Size(loctestnum, loctesterr, ht, true, 340);

                Exists(loctestnum, loctesterr, ht, false, 44);
                Exists(loctestnum, loctesterr, ht, false, 0);
                Exists(loctestnum, loctesterr, ht, false, 54);
                Exists(loctestnum, loctesterr, ht, false, 75);
                Exists(loctestnum, loctesterr, ht, false, 93);

                InsertC(loctestnum, loctesterr, ht, true, 44);
                InsertC(loctestnum, loctesterr, ht, true, 0);
                InsertC(loctestnum, loctesterr, ht, true, 54);
                InsertC(loctestnum, loctesterr, ht, true, 75);
                InsertC(loctestnum, loctesterr, ht, true, 93);

                InsertC(loctestnum, loctesterr, ht, false, 44);
                InsertC(loctestnum, loctesterr, ht, false, 0);
                InsertC(loctestnum, loctesterr, ht, false, 54);
                InsertC(loctestnum, loctesterr, ht, false, 75);
                InsertC(loctestnum, loctesterr, ht, false, 93);
                Size(loctestnum, loctesterr, ht, true, 345);

                Exists(loctestnum, loctesterr, ht, true, 44);
                Exists(loctestnum, loctesterr, ht, true, 0);
                Exists(loctestnum, loctesterr, ht, true, 54);
                Exists(loctestnum, loctesterr, ht, true, 75);
                Exists(loctestnum, loctesterr, ht, true, 93);

                Remove(loctestnum, loctesterr, ht, vec);
                Empty(loctestnum, loctesterr, ht, true);

                InsertC(loctestnum, loctesterr, ht, vec);
                Size(loctestnum, loctesterr, ht, true, 345);
            }

            {
                lasd::HashTableOpnAdr<int> ht;
                Empty(loctestnum, loctesterr, ht, true);
                InsertAllC(loctestnum, loctesterr, ht, false, vec);
                Size(loctestnum, loctesterr, ht, true, 345);

                ht.Clear();
                Empty(loctestnum, loctesterr, ht, true);
                ht.Resize(30);

                for (int i = 0; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 1; i < 350; i += 2)
                {
                    if (vec[i] == 44 || vec[i] == 0 || vec[i] == 54 || vec[i] == 75 || vec[i] == 93)
                    {
                        InsertC(loctestnum, loctesterr, ht, false, vec[i]);
                    }
                    else
                    {
                        InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                    }
                }
                Size(loctestnum, loctesterr, ht, true, 345);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                Remove(loctestnum, loctesterr, ht, true, 44);
                Remove(loctestnum, loctesterr, ht, true, 0);
                Remove(loctestnum, loctesterr, ht, true, 54);
                Remove(loctestnum, loctesterr, ht, true, 75);
                Remove(loctestnum, loctesterr, ht, true, 93);
                Size(loctestnum, loctesterr, ht, true, 340);

                Exists(loctestnum, loctesterr, ht, false, 44);
                Exists(loctestnum, loctesterr, ht, false, 0);
                Exists(loctestnum, loctesterr, ht, false, 54);
                Exists(loctestnum, loctesterr, ht, false, 75);
                Exists(loctestnum, loctesterr, ht, false, 93);

                InsertC(loctestnum, loctesterr, ht, true, 44);
                InsertC(loctestnum, loctesterr, ht, true, 0);
                InsertC(loctestnum, loctesterr, ht, true, 54);
                InsertC(loctestnum, loctesterr, ht, true, 75);
                InsertC(loctestnum, loctesterr, ht, true, 93);

                InsertC(loctestnum, loctesterr, ht, false, 44);
                InsertC(loctestnum, loctesterr, ht, false, 0);
                InsertC(loctestnum, loctesterr, ht, false, 54);
                InsertC(loctestnum, loctesterr, ht, false, 75);
                InsertC(loctestnum, loctesterr, ht, false, 93);
                Size(loctestnum, loctesterr, ht, true, 345);

                Exists(loctestnum, loctesterr, ht, true, 44);
                Exists(loctestnum, loctesterr, ht, true, 0);
                Exists(loctestnum, loctesterr, ht, true, 54);
                Exists(loctestnum, loctesterr, ht, true, 75);
                Exists(loctestnum, loctesterr, ht, true, 93);

                Remove(loctestnum, loctesterr, ht, vec);
                Empty(loctestnum, loctesterr, ht, true);

                InsertC(loctestnum, loctesterr, ht, vec);
                Size(loctestnum, loctesterr, ht, true, 345);
            }
        }
        catch (...)
        {
            loctestnum++;
            loctesterr++;
            cout << endl
                 << "Unmanaged error! " << endl;
        }
        cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mytestHashTableDouble(uint &testnum, uint &testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        cout << endl
             << "Begin of HashTable<double> Test" << endl;
        try
        {
            lasd::Vector<double> vec(350);
            for (uint i = 0; i < 350; i++)
            {
                vec[i] = (pow(-2, i % 24) * ((61 * i + 29) % 127)) / (83 * pow(-3, i % 7));
            }

            {
                lasd::HashTableClsAdr<double> ht(73, vec);
                Size(loctestnum, loctesterr, ht, true, 344);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                lasd::HashTableClsAdr<double> ht2(200);

                NonEqualHT(loctestnum, loctesterr, ht, ht2);

                InsertC(loctestnum, loctesterr, ht2, true, vec[48]);
                Size(loctestnum, loctesterr, ht2, true, 1);

                ht2 = ht;
                EqualHT(loctestnum, loctesterr, ht, ht2);

                Remove(loctestnum, loctesterr, ht2, true, vec[48]);
                NonEqualHT(loctestnum, loctesterr, ht, ht2);

                Remove(loctestnum, loctesterr, ht, true, vec[15]);
                Remove(loctestnum, loctesterr, ht, true, vec[0]);
                Remove(loctestnum, loctesterr, ht, true, vec[117]);
                Remove(loctestnum, loctesterr, ht, true, vec[48]);
                Remove(loctestnum, loctesterr, ht, true, vec[71]);
                Size(loctestnum, loctesterr, ht, true, 339);

                Remove(loctestnum, loctesterr, ht, false, vec[15]);
                Remove(loctestnum, loctesterr, ht, false, vec[0]);
                Remove(loctestnum, loctesterr, ht, false, vec[117]);
                Remove(loctestnum, loctesterr, ht, false, vec[48]);
                Remove(loctestnum, loctesterr, ht, false, vec[71]);

                ht2 = move(ht);
                Size(loctestnum, loctesterr, ht2, true, 339);
                ht.Resize(0);

                ht = move(ht2);
                ht2 = ht;
                EqualHT(loctestnum, loctesterr, ht, ht2);

                lasd::HashTableClsAdr<double> ht3(move(ht));
                EqualHT(loctestnum, loctesterr, ht3, ht2);
                ht = ht2;

                lasd::HashTableClsAdr<double> ht4(ht);
                EqualHT(loctestnum, loctesterr, ht4, ht2);

                ht4.Resize(5);
                for (int i = 0; i < 350; i++)
                {
                    if (vec[i] == vec[15] || vec[i] == vec[0] || vec[i] == vec[117] || vec[i] == vec[48] || vec[i] == vec[71])
                    {
                        Exists(loctestnum, loctesterr, ht4, false, vec[i]);
                    }
                    else
                    {
                        Exists(loctestnum, loctesterr, ht4, true, vec[i]);
                    }
                }

                ht4.Clear();
                NonEqualHT(loctestnum, loctesterr, ht3, ht4);
                ht3.Clear();
                EqualHT(loctestnum, loctesterr, ht3, ht4);
                ht3.Resize(0);

                ht3 = ht4;
                ht4 = move(ht3);
                ht3 = ht4;
                EqualHT(loctestnum, loctesterr, ht3, ht4);

                lasd::HashTableClsAdr<double> ht5(move(ht3));
                InsertC(loctestnum, loctesterr, ht5, vec);
                Size(loctestnum, loctesterr, ht5, true, 344);
            }

            {
                lasd::HashTableOpnAdr<double> ht(73, vec);
                Size(loctestnum, loctesterr, ht, true, 344);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                lasd::HashTableOpnAdr<double> ht2(200);

                NonEqualHT(loctestnum, loctesterr, ht, ht2);

                InsertC(loctestnum, loctesterr, ht2, true, vec[48]);
                Size(loctestnum, loctesterr, ht2, true, 1);

                ht2 = ht;
                EqualHT(loctestnum, loctesterr, ht, ht2);

                Remove(loctestnum, loctesterr, ht2, true, vec[48]);
                NonEqualHT(loctestnum, loctesterr, ht, ht2);

                Remove(loctestnum, loctesterr, ht, true, vec[15]);
                Remove(loctestnum, loctesterr, ht, true, vec[0]);
                Remove(loctestnum, loctesterr, ht, true, vec[117]);
                Remove(loctestnum, loctesterr, ht, true, vec[48]);
                Remove(loctestnum, loctesterr, ht, true, vec[71]);
                Size(loctestnum, loctesterr, ht, true, 339);

                Remove(loctestnum, loctesterr, ht, false, vec[15]);
                Remove(loctestnum, loctesterr, ht, false, vec[0]);
                Remove(loctestnum, loctesterr, ht, false, vec[117]);
                Remove(loctestnum, loctesterr, ht, false, vec[48]);
                Remove(loctestnum, loctesterr, ht, false, vec[71]);

                ht2 = move(ht);
                Size(loctestnum, loctesterr, ht2, true, 339);
                ht.Resize(0);

                ht = move(ht2);
                ht2 = ht;
                EqualHT(loctestnum, loctesterr, ht, ht2);

                lasd::HashTableOpnAdr<double> ht3(move(ht));
                EqualHT(loctestnum, loctesterr, ht3, ht2);
                ht = ht2;

                lasd::HashTableOpnAdr<double> ht4(ht);
                EqualHT(loctestnum, loctesterr, ht4, ht2);

                ht4.Resize(5);
                for (int i = 0; i < 350; i++)
                {
                    if (vec[i] == vec[15] || vec[i] == vec[0] || vec[i] == vec[117] || vec[i] == vec[48] || vec[i] == vec[71])
                    {
                        Exists(loctestnum, loctesterr, ht4, false, vec[i]);
                    }
                    else
                    {
                        Exists(loctestnum, loctesterr, ht4, true, vec[i]);
                    }
                }

                ht4.Clear();
                NonEqualHT(loctestnum, loctesterr, ht3, ht4);
                ht3.Clear();
                EqualHT(loctestnum, loctesterr, ht3, ht4);
                ht3.Resize(0);

                ht3 = ht4;
                ht4 = move(ht3);
                ht3 = ht4;
                EqualHT(loctestnum, loctesterr, ht3, ht4);

                lasd::HashTableOpnAdr<double> ht5(move(ht3));
                InsertC(loctestnum, loctesterr, ht5, vec);
                Size(loctestnum, loctesterr, ht5, true, 344);
            }
        }
        catch (...)
        {
            loctestnum++;
            loctesterr++;
            cout << endl
                 << "Unmanaged error! " << endl;
        }
        cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mytestHashTableString(uint &testnum, uint &testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        cout << endl
             << "Begin of HashTable<string> Test" << endl;
        try
        {
            lasd::Vector<string> vec(350);

            vec[0] = "@";
            for (uint i = 1; i < 17; i++)
            {
                vec[i] = vec[i - 1] + static_cast<char>(33 + ((253 * i + 1001) % 94));
            }
            for (uint i = 17; i < 350; i++)
            {
                vec[i] = vec[i - 1];
                vec[i][i % 17] = static_cast<char>(33 + ((74 * i + 10841) % 94));
            }

            {
                lasd::HashTableClsAdr<string> ht(1);
                Empty(loctestnum, loctesterr, ht, true);

                InsertAllC(loctestnum, loctesterr, ht, true, vec);
                Empty(loctestnum, loctesterr, ht, false);
                Size(loctestnum, loctesterr, ht, true, 350);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 1; i < 350; i += 2)
                {
                    Remove(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 1; i < 350; i += 2)
                {
                    Exists(loctestnum, loctesterr, ht, false, vec[i]);
                }
                ht.Resize(120);

                for (int i = 0; i < 350; i += 2)
                {
                    Remove(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 0; i < 350; i += 2)
                {
                    Exists(loctestnum, loctesterr, ht, false, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 0);

                for (int i = 1; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 1; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, false, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 0; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 350);
            }

            {
                lasd::HashTableOpnAdr<string> ht(1);
                Empty(loctestnum, loctesterr, ht, true);

                InsertAllC(loctestnum, loctesterr, ht, true, vec);
                Empty(loctestnum, loctesterr, ht, false);
                Size(loctestnum, loctesterr, ht, true, 350);

                for (int i = 0; i < 350; i++)
                {
                    Exists(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 1; i < 350; i += 2)
                {
                    Remove(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 1; i < 350; i += 2)
                {
                    Exists(loctestnum, loctesterr, ht, false, vec[i]);
                }
                ht.Resize(120);

                for (int i = 0; i < 350; i += 2)
                {
                    Remove(loctestnum, loctesterr, ht, true, vec[i]);
                }

                for (int i = 0; i < 350; i += 2)
                {
                    Exists(loctestnum, loctesterr, ht, false, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 0);

                for (int i = 1; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 1; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, false, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 175);

                for (int i = 0; i < 350; i += 2)
                {
                    InsertC(loctestnum, loctesterr, ht, true, vec[i]);
                }
                Size(loctestnum, loctesterr, ht, true, 350);
            }
        }
        catch (...)
        {
            loctestnum++;
            loctesterr++;
            cout << endl
                 << "Unmanaged error! " << endl;
        }
        cout << "End of HashTable<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mytest()
    {
        uint ex3testnum = 0;
        uint ex3testerr = 0;

        uint ltestnum = 0;
        uint ltesterr = 0;
        cout << endl
             << "Begin of HashTableCLSADR Test" << endl;
        testHTCLSADR(ltestnum, ltesterr);
        mytestHashTableInt(ltestnum, ltesterr);
        mytestHashTableDouble(ltestnum, ltesterr);
        mytestHashTableString(ltestnum, ltesterr);
        cout << endl
             << "HashTable CLSADR (Errors/Tests: " << ltesterr << "/" << ltestnum << ")";
        cout << endl;

        cout << endl
             << "Begin of HashTableOPNADR Test" << endl;
        testHTOPNADR(ltestnum, ltesterr);
        cout << endl
             << "HashTable OPNADR (Errors/Tests: " << ltesterr << "/" << ltestnum << ")";
        cout << endl;

        cout << endl
             << "End of Exercise3 test (Errors/Tests: " << ex3testerr << "/" << ex3testnum << ")" << endl;

        cout << endl
             << "Goodbye!" << endl;
    }

};