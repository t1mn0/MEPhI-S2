#include <cassert>
#include "BTree.hpp"

int reduceFunc(const int& a, const int& b) {
    return a + b;
}

void TestMethods() {
    BTree<int> tree(new BTreeNode<int>(1));

    assert(1 == tree.getRoot()->value);

    for (int i = 2; i < 11; ++i) {
        if (i % 2) {
            tree.rinsert(i);
        }
        else {
            tree.insert(i);
        }
    }

    int originalDepth = tree.max_depth();

    tree.balance();

    assert(originalDepth >= tree.max_depth());

    // Удаление листьев (без потомков)
    tree.erase(4);
    tree.erase(7);
    tree.erase(10);
    // Удаление узлов с двумя потомками
    tree.erase(2);
    tree.erase(8);
    // Удаление листьев (без потомков)
    tree.erase(1);
    tree.erase(9);
    // Удаление узлов с одним потомком и последнего узла:
    tree.erase(5);
    tree.erase(3);
    tree.erase(6);

    
    assert(tree.getRoot() == nullptr);

    for (int i = 1; i <= 12; ++i) {
        tree.insert(i);
    }

    tree.balance();

    tree.map([](int a) {return a * 10; });
    int sum = tree.reduce(0, reduceFunc);
    // ((12 + 1) * 12 / 2) * 10
    assert(sum == 780);

    BTree<int>* newtree1 = tree.clone_tree(tree.search_node(90));
    BTree<int>* newtree2 = tree.clone_tree(tree.search_node(40));
    BTree<int>* newtree3 = tree.clone_tree(tree.search_node(120));

    MutableArraySequence<int> lpr1 = newtree1->LPR();
    MutableArraySequence<int> rlpr1 = newtree1->rLPR();

    MutableArraySequence<int> plr2 = newtree1->PLR();
    MutableArraySequence<int> rplr2 = newtree1->rPLR();

    MutableArraySequence<int> rlp3 = newtree1->RLP();
    MutableArraySequence<int> rrlp3 = newtree1->rRLP();

    assert(lpr1.get_size() == rlpr1.get_size());
    assert(plr2.get_size() == rplr2.get_size());
    assert(rlp3.get_size() == rrlp3.get_size());

    for (int i = 0; i < lpr1.get_size(); ++i) {
        assert(lpr1[i] == rlpr1[i]);
    }

    for (int i = 0; i < plr2.get_size(); ++i) {
        assert(plr2[i] == rplr2[i]);
    }

    for (int i = 0; i < rlp3.get_size(); ++i) {
        assert(rlp3[i] == rrlp3[i]);
    }


    BTree<int> newtree4(new BTreeNode<int>(1));
    for (int i = 2; i < 13; ++i) {
        if (i % 2) {
            newtree4.rinsert(i);
        }
        else {
            newtree4.insert(i);
        }
    }

    newtree4.balance();
    newtree4.map([](int a) {return a * 10; });

    assert(tree.is_subtree(tree.getRoot(), newtree1->getRoot()));
    assert(tree.is_subtree(tree.getRoot(), newtree2->getRoot()));
    assert(tree.is_subtree(tree.getRoot(), newtree3->getRoot()));
    assert(tree.is_subtree(tree.getRoot(), newtree4.getRoot()));

    newtree1->erase(110); // Удаление узла с двумя потомками
    newtree2->erase(40); // Удаление узла с одним потомком
    newtree3->erase(120); // Удаление листа
    newtree4.erase(120); // Удаление листа

    assert(tree.is_subtree(tree.getRoot(), newtree1->getRoot()) == false);
    assert(tree.is_subtree(tree.getRoot(), newtree2->getRoot()) == true);
    assert(tree.is_subtree(tree.getRoot(), newtree3->getRoot()) == true);
    assert(tree.is_subtree(tree.getRoot(), newtree4.getRoot()) == false);
}