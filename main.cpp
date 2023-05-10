#include <bits/stdc++.h>
#include "AVLTree.cpp"
using namespace std;

int main(){
    AVLTree<int> test;
    test.insert(12);
    test.insert(5);
    test.insert(1);
    test.deleteNode(1);
    test.print();
}