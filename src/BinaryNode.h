#pragma once

#ifndef _BINARY_NODE
#define _BINARY_NODE

template <class T>
class BinaryNode
{
private:
    T item;                  // Data portion
    BinaryNode<T> *leftPtr;  // Pointer to left child
    BinaryNode<T> *rightPtr; // Pointer to right child

public:
    // constructors
    BinaryNode(const T &anItem)
    {
        item = anItem;
        leftPtr = 0;
        rightPtr = 0;
    }
    BinaryNode(const T &anItem,
               BinaryNode<T> *left,
               BinaryNode<T> *right)
    {
        item = anItem;
        leftPtr = left;
        rightPtr = right;
    }
    // setters
    void setItem(const T &anItem) { item = anItem; }
    void setLeftPtr(BinaryNode<T> *left) { leftPtr = left; }
    void setRightPtr(BinaryNode<T> *right) { rightPtr = right; }

    // getters
    T getItem() const { return item; }
    BinaryNode<T> *getLeftPtr() const { return leftPtr; }
    BinaryNode<T> *getRightPtr() const { return rightPtr; }

    // other functions
    bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif
