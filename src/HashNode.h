/*
 *
  This is a Header file for the Hash node class
  Written by: Sarina Karki
  IDE: Xcode
  HashNode is created as the linked list node, containing the pointer to the object 
  and a next pointer to the next HashNode
  *
  */

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
