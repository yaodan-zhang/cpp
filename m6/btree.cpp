/*
An improved version of binary search tree using RAII unique_ptr,
which takes care of memory management.
Customized functionality such as copy constructor and print tree/subtree are added.
*/
#include "btree.h"
#include <iostream>
using namespace mybtree;

int main() {
    btree bst(2);
    bst.insert(3);
    bst.insert(5);
    bst.insert(10);
    bst.insert(1);
    bst.insert(-1);
    bst.insert(22);
    cout << bst;

    auto subtree = bst.search(5);
    cout << subtree;
    return 0;
}