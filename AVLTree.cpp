#include "AVLTree.h"


template<typename T>
AVLTree<T>::AVLTree() {
    root = nullptr;
    SIZE = 0;
}


template<typename T>
void AVLTree<T>::insert(const T& value) {
    insert(value, root);
}


template<typename T>
void AVLTree<T>::print(){
    printInOrder(root);
    cout << '\n';
}


template<typename T>        
void AVLTree<T>::deleteNode(const T& value) {
    deleteNode(value, root);
}


template<typename T>
int AVLTree<T>::getHeight(Node<T>*& node) const{
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}


template<typename T>
int AVLTree<T>::getBalanceFactor(Node<T>*& node) const{
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


template<typename T>
void AVLTree<T>::updateHeight(Node<T>*& node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}


template<typename T>
void AVLTree<T>::leftRotation(Node<T>*& node) {
    // store the right node
    Node<T>* Rnode = node->right;
    // store the right left node
    Node<T>* RLnode = Rnode->left;
    // make the left of the right node equal the parent node
    Rnode->left = node;
    // make the right node of the parent equal to the right left node
    node->right = RLnode;
    // recalculate the height
    updateHeight(node);
    updateHeight(Rnode);
    // replace the right node to it's place
    node = Rnode;
}


template<typename T>
void AVLTree<T>::rightRotation(Node<T>*& node) {
    // store the left node
    Node<T>* Lnode = node->left;
    // store the left right node
    Node<T>* LRnode = Lnode->right;
    // make the right of the left node equal the parent node
    Lnode->right = node;
    // make the left node of the parent equal to the left right node
    node->left = LRnode;
    // recalculate the height
    updateHeight(node);
    updateHeight(Lnode);
    // replace the left node to it's place
    node = Lnode;
}


template<typename T>
void AVLTree<T>::balance(Node<T>*& node) {
    int balanceFactor = getBalanceFactor(node);

    // left case
    if (balanceFactor > 1) {
        // left right violation
        if (getBalanceFactor(node->left) < 0)
            leftRotation(node->left);
        // left left
        rightRotation(node);
    }
    
    // right case
    else if (balanceFactor < -1) {
        // right left
        if (getBalanceFactor(node->right) > 0)
            rightRotation(node->right);
        // right right
        leftRotation(node);
    }

    // update height of the node (will be called from leafs to the root)
    updateHeight(node);
}


template<typename T>
void AVLTree<T>::insert(const T& value, Node<T>*& node) {
    // base case reach empty node
    if (node == nullptr){
        node = new Node<T>(value);
        SIZE++;
        return;
    }
    // if value is less than the value in the current node go left
    if (value < node->value)
        insert(value, node->left);
    // else go right
    else
        insert(value, node->right);
    // balance and keep balance while back track until reach the root
    balance(node);
}


template<typename T>
void AVLTree<T>::printInOrder(Node<T>*& node){
    // base case
    if (node == nullptr) {
        return;
    }
    printInOrder(node->left);
    cout << node->value << ' ';
    printInOrder(node->right);
}


template<typename T>
void AVLTree<T>::deleteNode(const T& value, Node<T>*& node) {
    // if node not found
    if (node == nullptr)
        return;
    // if value less than the value in the current node (move left)
    if (value < node->value)
        deleteNode(value, node->left);
    // if the value greate thant the value in the current node (move right)
    else if (value > node->value)
        deleteNode(value, node->right);

    // if found
    else{
        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
            // this return will backtrack
            return;
        }

        // Case 2: Node has one child
        if (node->left == nullptr) {
            // swap thier places
            swap(node, node->right);
            // remove it after swapping
            delete node->right;
            node->right = nullptr;
            return;
        }
        else if (node->right == nullptr) {
            // swap thier places
            swap(node, node->left);
            // remove it after swapping
            delete node->left;
            node->left = nullptr;
            return;
        }

        // Case 3: Node has two children
        // find successor
        Node<T>* successor = node->right;
        while (successor->left != nullptr)
            successor = successor->left;
        // put a copy from the successor in my place
        node->value = successor->value;
        // remove the successor (we must remove it by function calling to update height from depth and balance from depth)
        deleteNode(successor->value, node->right);
    }
    balance(node);
}


template<typename T>
bool AVLTree<T>::empty() const{
    return SIZE == 0;
}


template<typename T>
int AVLTree<T>::size() const{
    return SIZE;
}


template<typename T>
bool AVLTree<T>::search(const T& key, Node<T>*& node) const{
    if(node == nullptr)
        return false;
    if(node->value == key)
        return true;
    else if(node->value > key)
        return search(key, node->left);
    else
        return search(key, node->right);
}


template<typename T>
bool AVLTree<T>::isExsit(const T& key) const{
    return search(key, root);
}