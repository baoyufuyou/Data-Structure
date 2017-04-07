#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class AVLTree {
private:
    struct AVLNode {
        AVLNode (const T &element, AVLNode *lt, AVLNode *rt, int h = 0)
            : ele(element), left(lt), right(rt), height(h)
        {}
        T ele;
        AVLNode *left;
        AVLNode *right;
        int height;
    };

public:
    AVLTree() : root(nullptr) {}
    AVLTree(const AVLTree &rhs) { operator=(rhs); }
    ~AVLTree() { makeEmpty(); }

public:
    const AVLTree &operator=(const AVLTree &rhs)
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
    int height(AVLNode *t) const { return t == nullptr ? -1 : t->height; }

    AVLNode *clone(AVLNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AVLNode(t->ele, clone(t->left), clone(t->right));
    }
    AVLNode *findMin(AVLNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    AVLNode *findMax(AVLNode *t) const
    {
        if (t != nullptr) {
            while (t->right != nullptr)
                t = t->right;
        }
        return t;
    }
    bool contains(const T &x, AVLNode *t)
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
    void printDepth(const T &x, int depth = 0) const
    {
        while (depth--)
            cout << "\t";
        cout << "[" << x << "]" << endl;
    }
    void printTree(AVLNode *t, int depth = 0) const
    {
        if (t == nullptr)
            return; // do nothing
        printTree(t->left, depth + 1);
        printDepth(t->ele, depth); //���ŵ�λ�þ�����ǰ�к������
        printTree(t->right, depth + 1);
    }
    void makeEmpty(AVLNode *&t)
    {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    // ������1���󣬽ڵ�������һ��˳ʱ����ת
    void rotateWithLeft(AVLNode *&k2)
    {
        AVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1; // �������߶Ⱦ���k2�ĸ߶�

        k2 = k1; // ��֤��һ��ڵ����ӵ���ת��Ľڵ�
    }
    // ������4���ң��ڵ���Ҷ���һ����ʱ����ת
    void rotateWithRight(AVLNode *&k1)
    {
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(k1->height, height(k2->right)) + 1; // �������߶Ⱦ���k2�ĸ߶�

        k1 = k2; // ��֤��һ��ڵ����ӵ���ת��Ľڵ�
    }
    // ������2���ң��ڵ�����������ʱ����ת�����Žڵ�˳ʱ����ת
    void doubleRotateWithLeft(AVLNode *&k3)
    {
        //rotateWithRight(k3->left);
        //rotateWithLeft(k3);

        //ex 3.26 ��дһ��˫��ת��Ч�ʸ������ε���ת
        //������ת���̲����ܽ����
        AVLNode *k1 = k3->left;
        AVLNode *k2 = k1->right;

        k1->right = k2->left;
        k3->left = k2->right;
        k2->left = k1;
        k2->right = k3;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k2->height = max(k1->height, k3->height) + 1;

        k3 = k2; // ��֤��һ��ڵ����ӵ���ת��Ľڵ�
    }
    // ������3���󣬽ڵ���Ҷ�����˳ʱ����ת�����Žڵ���ʱ����ת
    void doubleRotateWithRight(AVLNode *&k1) 
    {
        //rotateWithLeft(k3->right);
        //rotateWithRight(k3);

        //ex 3.26 ��дһ��˫��ת��Ч�ʸ������ε���ת
        //������ת���̲����ܽ����
        AVLNode *k3 = k1->right;
        AVLNode *k2 = k3->left;

        k1->right = k2->left;
        k3->left = k2->right;
        k2->left = k1;
        k2->right = k3;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k2->height = max(k1->height, k3->height) + 1;

        k1 = k2; // ��֤��һ��ڵ����ӵ���ת��Ľڵ�
    }

    void insert(const T &x, AVLNode *&t)
    {
        if (t == nullptr)
            t = new AVLNode(x, nullptr, nullptr);
        else if (x < t->ele) {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->ele)
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else if (t->ele < x) {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (t->right->ele < x)
                    rotateWithRight(t);
                else
                    doubleRotateWithRight(t);
            }
        } else
            ; //do nothing
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    //AVLTreeɾ���ڵ��˼·:
    //1.����������һ��ɾ���ڵ�
    //2.���¼���ڵ�߶�
    //3.����Ƿ�����ƽ����������������Ҫ����
    void remove(const T &x, AVLNode *&t)
    {
        if (t == nullptr)
            return; //not found, do nothing
        if (x < t->ele) {
            remove(x, t->left);

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //ɾ��������һ���ڵ㣬��Ҫ�ж��ң���
            if (height(t->right) - height(t->left) == 2) {
                if (height(t->right->right) >= height(t->right->left))
                    rotateWithRight(t);
                else
                    doubleRotateWithRight(t);
            }
        } else if (t->ele < x) {
            remove(x, t->right);

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //ɾ��������һ���ڵ㣬��Ҫ�ж�����
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->left) >= height(t->left->right))
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else if (t->left != nullptr && t->right != nullptr) { //2 children
            t->ele = findMin(t->right)->ele; //������������Сֵ�����ǰֵ
            remove(t->ele, t->right); //ɾ������������Сֵ

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //ɾ��������һ���ڵ㣬��Ҫ�ж�����
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->left) >= height(t->left->right))
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else {
            AVLNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }

private:
    AVLNode *root;
};

#endif //AVLTREE_H