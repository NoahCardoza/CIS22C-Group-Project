//
//  LinkedList.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "HashNode.h"

template <class T>
class LinkedList
{
private:
	HashNode<T> *head;
	int length;

public:
	LinkedList();  //constructor
	~LinkedList(); //destructor

	//Linked List Operations
	int getLength() const { return length; }
	void insertNode(const T *);
	bool deleteNode(const T *, T **);

	void displayList() const;
	bool searchList(const T *, T **) const;
};

template <class T>
LinkedList<T>::LinkedList()
{
	head = new HashNode<T>; //head points to the sentinel node
	head->setNext(nullptr);
	length = 0;
}

//The insertNode function inserts a new node in a sorted linked list
template <class T>
void LinkedList<T>::insertNode(const T *dataIn)
{
	HashNode<T> *newNode; //A new node
	HashNode<T> *pCur;	  //To traverse the list
	HashNode<T> *pPre;	  //The previous node

	//Allocate a new node and store the pointer to object there
	newNode = new HashNode<T>;
	newNode->setItem(dataIn);

	//Initialize pointers
	pPre = head;
	pCur = head->getNext();

	//Find Location: skip all nodes whose ID is less than the dataIn->ID
	while (pCur && newNode->getItem() > pCur->getItem())
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
template <class T>
bool LinkedList<T>::deleteNode(const T *target, T **itemOut)
{
	HashNode<T> *pCur; //to traverse the lsit
	HashNode<T> *pPre; //to point to the previous node
	bool deleted = false;

	//Initialize pointers
	pCur = head->getNext();
	pPre = head;

	//Find node containing the target: Skip all nodes whose ID is less than the target
	while (pCur && pCur->getItem() < target)
	{
		pPre = pCur;
		pCur = pCur->getNext();
	}

	// If found, delete the node
	if (pCur && pCur->getItem() == target)
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
template <class T>
void LinkedList<T>::displayList() const
{
	HashNode<T> *pCur; // To move through the list

	// Position pCur: skip the head of the list.
	pCur = head->getNext();

	// While pCur is not nullptr, traverse the list.
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
template <class T>
bool LinkedList<T>::searchList(const T *target, T **dataOut) const
{
	bool found = false; // assume target not found
	HashNode<T> *pCur;	// To move through the list

	// Position pCur: skip the head of the list.
	pCur = head->getNext();
	// Find location: skip all nodes whose name is less than target's name
	while (pCur && pCur->getItem() < target)
	{
		pCur = pCur->getNext();
	}

	// If found, copy data to the output parameter, and change the flag to true
	if (pCur && pCur->getItem() == target)
	{
		*dataOut = pCur->getItem();
		found = true;
	}

	return found;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template <class T>
LinkedList<T>::~LinkedList()
{
	HashNode<T> *pCur;	// To traverse the list
	HashNode<T> *pNext; // To hold the address of the next node

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
#endif /* LinkedList_h */
