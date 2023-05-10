#include <bits/stdc++.h>
#include "AVLTree.cpp"
using namespace std;

int main(){
    AVLTree<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(3);
    test.insert(4);
    test.insert(5);
    test.insert(6);
    test.insert(7);
    test.insert(8);
    test.insert(9);
    test.insert(10);
    test.deleteNode(1);
    test.print();
}