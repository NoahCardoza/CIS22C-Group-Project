//
//  LinkedList.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef LinkedList_h
#define LinkedList_h

#include "HashNode.h"

template <class ItemType>
class LinkedList
{
private:
    HashNode <ItemType>* head;
    int length;
    
public:
    LinkedList();  //constructor
    ~LinkedList(); //destructor
    
    //Linked List Operations
    int getLength() const {return length;}
    void insertNode(const ItemType*);
    bool deleteNode(const ItemType*, ItemType* );
    
    void displayList() const;
    bool searchList(const ItemType*, ItemType*) const;
};

template <class ItemType>
LinkedList <ItemType>::LinkedList()
{
    head = new HashNode<ItemType>; //head points to the sentinel node
    head->setNext(NULL);
    length = 0;
}

//The insertNode function inserts a new node in a sorted linked list
void LinkedList<ItemType>::insertNode(const ItemType* dataIn)
{
    HashNode<ItemType> *newNode; //A new node
    HashNode<ItemType> *pCur; //To traverse the list
    HashNode<ItemType> *pPre; //The previous node
    
    //Allocate a new node and store the pointer to object there
    newNode = new HashNode<ItemType>;
    newNode->setItem(dataIn);
    
    //Initialize pointers
    pPre = head;
    pCur = head->getNext();
    
    //Find Location: skip all nodes whose ID is less than the dataIn->ID
    while (pCur && newNode->getItem()->getID() > pCur->getItem()->getID())
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }
    
    //Insert the new node between pPre and pCur
    pPre->setNext(newNode);
    if (pCur)
    {
        newNode->setNext(pCur);
    }
    
    //Update the counter
    length++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************
template <class ItemType>
bool LinkedList<Itemtype>::deleteNode(const ItemType* target, Itemtype** itemOut)
{
    HashNode<ItemType> *pCur; //to traverse the lsit
    HashNode<ItemType> *pPre; //to point to the previous node
    bool deleted = false;
    
    //Initialize pointers
    pCur = head->getNext();
    pPre = head;
    
    //Find node containing the target: Skip all nodes whose ID is less than the target
    while(pCur && pCur->getItem()->getID() < target->getID())
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }
    
    // If found, delete the node
    if (pCur && pCur->getItem()->getID() == target.getID())
    {
        pPre->setNext(pCur->getNext());
        *itemOut = pCur->getItem();
        
        delete pCur;
        deleted = true;
        length--;
    }
    
    return deleted;

}

//**************************************************
// displayList shows the value
// stored in each node of the linked list
// pointed to by head, except the sentinel node
//**************************************************
template <class ItemType>
void LinkedList<ItemType>::displayList() const
{
     HashNode<ItemType> *pCur;  // To move through the list

     // Position pCur: skip the head of the list.
     pCur = head->getNext();

     // While pCur is not NULL, traverse the list.
     while (pCur)
     {
         // Display the value in this node.
         
          std::cout << pCur->getItem();
         
         // Move to the next node.
         pCur = pCur->getNext();
    }
    std::cout << std::endl;
}

//**************************************************
// The searchList function looks for a target college
// in the sorted linked list: if found, returns true
// and copies the data in that node to the output parameter
//**************************************************
template <class ItemType>
bool LinkedList<ItemType>::searchList(const ItemType* target, ItemType** dataOut) const
{
    bool found = false; // assume target not found
    HashNode<ItemType> *pCur;         // To move through the list
    
    // Position pCur: skip the head of the list.
    pCur = head->getNext();
    // Find location: skip all nodes whose name is less than target's name
    while(pCur && pCur->getItem()->getID() < target->getID()){
        pCur = pCur->getNext();
    }
 
 
    // If found, copy data to the output parameter, and change the flag to true
    if(pCur && pCur->getItem()->getID() == target->getID()){
        *dataOut = pCur->getItem();
        found = true;
    }

    return found;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    HashNode<ItemType> *pCur;     // To traverse the list
    HashNode<ItemType> *pNext;    // To hold the address of the next node
    
    // Position nodePtr: skip the head of the list
    pCur = head->getNext();
    // While pCur is not at the end of the list...
    while(pCur)
    {
        // Save a pointer to the next node.
        pNext = pCur->getNext();
        
        // Delete the current node.
        delete pCur;
        
         // Position pCur at the next node.
        pCur = pNext;
    }
    
    delete head; // delete the sentinel node
}
#endif /* LinkedList_h */
