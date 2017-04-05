#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class BinarySearchTree {
private:
    struct BinaryNode {
        BinaryNode (const T &element, BinaryNode *lt, BinaryNode *rt)
            : ele(element), left(lt), right(rt)
        {}
        T ele;
        BinaryNode *left;
        BinaryNode *right;
    };

public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree &rhs) { operator=(rhs); }
    ~BinarySearchTree() { makeEmpty(); }

public:
    const BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    const T &findMin() const { return findMin(root)->ele; } //Ӧ��֤�ǿյ���
    const T &findMax() const { return findMax(root)->ele; } //Ӧ��֤�ǿյ���
    bool contains(const T &x) { return contains(x, root); }
    bool empty() const { return root == nullptr; }
    void printTree() const { printTree(root); }

    void makeEmpty() { makeEmpty(root); }
    void insert(const T &x) { insert(x, root); }
    void remove(const T &x) { remove(x, root); }

private:
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new BinaryNode(t->ele, clone(t->left), clone(t->right));
    }
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr) {
            while (t->right != nullptr)
                t = t->right;
        }
        return t;
    }
    bool contains(const T &x, BinaryNode *t)
    {
        if (t == nullptr)
            return false;
        else if (x < t->ele)
            return contains(x, t->left);
        else if (t->ele < x)
            return contains(x, t->right);
        else
            return true;
    }
    void printTree(BinaryNode *t) const
    {
        if (t == nullptr)
            return;
        cout << t->ele << endl; //���ŵ�λ�þ�����ǰ�к������
        printTree(t->left);
        printTree(t->right);
    }
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    void insert(const T &x, BinaryNode *&t) const
    {
        if (t == nullptr)
            t = new BinaryNode(x, nullptr, nullptr);
        else if (x < t->ele)
            insert(x, t->left);
        else if (t->ele < x)
            insert(x, t->right);
        else
            return; //do nothing
    }
    void remove(const T &x, BinaryNode *&t) const
    {
        if (t == nullptr)
            return; //not found, do nothing
        if (x < t->ele)
            remove(x, t->left);
        else if (t->ele < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) { //2 children
            t->ele = findMin(t->right)->ele; //������������Сֵ�����ǰֵ
            remove(t->ele, t->right); //ɾ������������Сֵ
        } else {
            BinaryNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }

private:
    BinaryNode *root;
};

#endif //BINARYSEARCHTREE_H