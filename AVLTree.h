#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T value;
    int height;
    Node<T>* left;
    Node<T>* right;

    Node(T value) {
        this->value = value;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
class AVLTree {
    private:
        int SIZE;
        Node<T>* root;

        int getHeight(Node<T>*& node) const;
        int getBalanceFactor(Node<T>*& node) const;
        void updateHeight(Node<T>*& node);
        void leftRotation(Node<T>*& node);
        void rightRotation(Node<T>*& node);
        void balance(Node<T>*& node);
        void insert(const T& value, Node<T>*& node);
        void printInOrder(Node<T>*& node);
        void deleteNode(const T& value, Node<T>*& node);
        bool search(const T& key, Node<T>*& curr) const;

    public:
        AVLTree();
        void insert(const T& value);
        void print();
        void deleteNode(const T& value);
        bool empty() const;
        int size() const;
        bool isExsit(const T& key) const;
};