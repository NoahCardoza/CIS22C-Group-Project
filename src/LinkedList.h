//
//  LinkedList.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef LinkedList_h
#define LinkedList_h

#include "HashNode.h"

/**
 * An interface used to iterate the linked list. It used a callback method
 * so information can be stored in the instance (to be accesed later in the
 * callback method) via the constructor of the subclassed instance.
 */
template <class T>
class LinkedListIterator
{
public:
	virtual void cb(T) = 0;
};

template <class T>
class LinkedList
{
private:
	HashNode<T *> *head;
	int length;

public:
	LinkedList();	 //constructor
	~LinkedList(); //destructor

	//Linked List Operations
	int getLength() const { return length; }
	void insertNode(T *dataIn);
	bool deleteNode(const T *, T **);

	void displayList() const;
	bool searchList(const T *target, T **dataOut) const;

	T *pop();
	void iterate(LinkedListIterator<T *> *iter);
};

template <class T>
LinkedList<T>::LinkedList()
{
	head = new HashNode<T *>; //head points to the sentinel node
	head->setNext(nullptr);
	length = 0;
}

//The insertNode function inserts a new node in a sorted linked list
template <class T>
void LinkedList<T>::insertNode(T *dataIn)
{
	HashNode<T *> *newNode; // A new node

	// Allocate a new node and store the pointer to object there
	newNode = new HashNode<T *>;
	newNode->setItem(dataIn);
	newNode->setNext(head->getNext());
	head->setNext(newNode);

	// Update the counter
	length++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************
template <class T>
bool LinkedList<T>::deleteNode(const T *target, T **itemOut)
{
	HashNode<T *> *pCur; //to traverse the lsit
	HashNode<T *> *pPre; //to point to the previous node

	//Initialize pointers
	pCur = head->getNext();
	pPre = head;

	//Find node containing the target: Skip all nodes whose ID is less than the target
	while (pCur)
	{
		if (*pCur->getItem() == *target)
		{
			pPre->setNext(pCur->getNext());

			*itemOut = pCur->getItem();

			delete pCur;

			length--;

			return true;
		}

		pPre = pCur;
		pCur = pCur->getNext();
	}

	return false;
}

//**************************************************
// displayList shows the value
// stored in each node of the linked list
// pointed to by head, except the sentinel node
//**************************************************
template <class T>
void LinkedList<T>::displayList() const
{
	HashNode<T *> *pCur; // To move through the list

	// Position pCur: skip the head of the list.
	pCur = head->getNext();

	// While pCur is not nullptr, traverse the list.
	while (pCur)
	{
		// Display the value in this node.
		pCur = pCur->getNext();
	}
}

//**************************************************
// The searchList function looks for a target college
// in the sorted linked list: if found, returns true
// and copies the data in that node to the output parameter
//**************************************************
template <class T>
bool LinkedList<T>::searchList(const T *target, T **dataOut) const
{
	HashNode<T *> *pCur; // To move through the list

	// Position pCur: skip the head of the list.
	pCur = head->getNext();

	// Find location: skip all nodes whose name is less than target's name
	while (pCur)
	{
		if ((*pCur->getItem()) == (*target))
		{
			*dataOut = pCur->getItem();
			return true;
		}
		pCur = pCur->getNext();
	}

	return false;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template <class T>
LinkedList<T>::~LinkedList()
{
	HashNode<T *> *pCur;	// To traverse the list
	HashNode<T *> *pNext; // To hold the address of the next node

	// Position nodePtr: skip the head of the list
	pCur = head->getNext();
	// While pCur is not at the end of the list...
	while (pCur)
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

template <class T>
T *LinkedList<T>::pop()
{
	HashNode<T *> *next;
	T *item;

	next = head->getNext();
	item = next->getItem();
	head->setNext(next->getNext());
	length--;

	delete next;
	return item;
}

template <class T>
void LinkedList<T>::iterate(LinkedListIterator<T *> *iter)
{
	HashNode<T *> *pCur = head->getNext();

	while (pCur)
	{
		iter->cb(pCur->getItem());
		pCur = pCur->getNext();
	}
}

#endif /* LinkedList_h */
