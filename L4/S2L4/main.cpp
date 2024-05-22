#include <iostream>
#include <locale>
#include "BTree.hpp"
#include "TestTraversal.hpp"
#include "TestMethods.hpp"
#include "TestBoundaryCases.hpp"
#include "view.hpp"

#include <iostream>


int main() {
    setlocale(LC_ALL, "Russian");
    TestTraversals();
    TestMethods();
    TestBoundaryCases();
    run();

    return 0;
}