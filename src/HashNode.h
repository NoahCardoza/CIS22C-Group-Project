//
//  HashNode.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.

#ifndef HashNode_h
#define HashNode_h

template <class T>
class HashNode
{
private:
    T ptrItem;
    HashNode<T> *next;

public:
    //constructors
    HashNode()
    {
        next = nullptr;
    }

    HashNode(T pItem)
    {
        ptrItem = pItem;
    }

    //setters
    void setItem(T pItem) { ptrItem = pItem; }
    void setNext(HashNode<T> *nextPtr) { next = nextPtr; }

    //getters
    T getItem() const { return ptrItem; }
    HashNode<T> *getNext() const { return next; }
};

#endif /* HashNode_h */
