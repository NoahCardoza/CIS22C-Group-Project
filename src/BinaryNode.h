/**
 * @author Omar Hafud
 * 
 * This class is used by the BinaryTree and BinarySearchTree subclass.
 * It's a wrapper for all the items stored in the tree. It uses a vector internally
 * to consolidate items of the same value.
 */

#pragma once
#include <vector>

#ifndef _BINARY_NODE
#define _BINARY_NODE

template <class T>
class BinaryNode
{
private:
    std::vector<T> items;    // Data portion
    BinaryNode<T> *leftPtr;  // Pointer to left child
    BinaryNode<T> *rightPtr; // Pointer to right child

public:
    // constructors
    BinaryNode(const T anItem)
    {
        items.push_back(anItem);
        leftPtr = 0;
        rightPtr = 0;
    }

    // setters
    void setLeftPtr(BinaryNode<T> *left) { leftPtr = left; }
    void setRightPtr(BinaryNode<T> *right) { rightPtr = right; }

    // getters
    std::vector<T> getItems() const { return items; }
    T getItem() const { return items[0]; }
    T removeItem(T search)
    {
        int i = 0;
        for (auto item : items)
        {
            if (item->getId() == search->getId())
            {
                items.erase(items.begin() + i);
                return item;
            }
            i++;
        }
        return nullptr;
    }
    bool isEmpty()
    {
        return items.size() == 0;
    };

    void copyNode(BinaryNode<T> *node)
    {
        items = node->getItems();
    };

    void addItem(T item)
    {
        items.push_back(item);
    }
    BinaryNode<T> *getLeftPtr() const { return leftPtr; }
    BinaryNode<T> *getRightPtr() const { return rightPtr; }
};

#endif
