#include <iostream>
#include <locale>
#include "TestTraversal.hpp"


int main() {
    setlocale(LC_ALL, "Russian");
    TestTraversals();

    /*
    BTree<int> myTree(new BTreeNode<int>(6));
    myTree.insert(4);
    myTree.insert(8);
    myTree.insert(2);
    myTree.insert(5);
    myTree.insert(7);
    myTree.insert(9);
    myTree.insert(1);
    myTree.insert(3);
    myTree.insert(10);
    myTree.insert(11);
    myTree.insert(15);

    myTree.balance();

    myTree.generateDotRepresentation("myTree.dot");
    std::system("dot -Tpng myTree.dot -o myTree.png");
    */

    return 0;
}