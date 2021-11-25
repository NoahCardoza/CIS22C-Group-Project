#pragma once
// Binary Search Tree ADT

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include <vector>
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
	// insert a node at the correct location
	bool insert(const T &item);
	// remove a node if found
	BinaryNode<T> *remove(const T &target);
	// find a target node
	bool search(const T &target, std::vector<T> *returnedItem) const;
	// find the smallest node
	bool findSmallest(T &returnedItem) const;
	// find the largest node
	bool findLargest(T &returnedItem) const;

private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNode);

	// search for target node
	bool _search(BinaryNode<T> *treePtr, const T target, std::vector<T> *returnedItem) const;

	// find the smallest node
	BinaryNode<T> *_findSmallest(BinaryNode<T> *nodePtr, T &smallest) const;

	// find the largest node
	BinaryNode<T> *_findLargest(BinaryNode<T> *nodePtr, T &smallest) const;
};

///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template <class T>
bool BinarySearchTree<T>::insert(const T &newEntry)
{
	BinaryNode<T> *newNodePtr = new BinaryNode<T>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or nullptr
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template <class T>
bool BinarySearchTree<T>::search(const T &anEntry, std::vector<T> *returnedItem) const
{
	return _search(this->rootPtr, anEntry, returnedItem);
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template <class T>
BinaryNode<T> *BinarySearchTree<T>::_insert(BinaryNode<T> *nodePtr,
																						BinaryNode<T> *newNodePtr)
{
	if (!nodePtr && this->isEmpty()) // == nullptr
	{
		nodePtr = newNodePtr;
		this->count++;
		return nodePtr;
	}
	if (nodePtr)
	{
		if ((nodePtr->getItem()) > (newNodePtr->getItem()))
		{
			if (!_insert(nodePtr->getLeftPtr(), newNodePtr))
			{
				nodePtr->setLeftPtr(newNodePtr);
				this->count++;
			}
		}
		else
		{
			if (!_insert(nodePtr->getRightPtr(), newNodePtr))
			{
				nodePtr->setRightPtr(newNodePtr);
				this->count++;
			}
		}
	}
	return nodePtr;
}

//Implementation for the search operation
// - return nullptr if target not found, otherwise
// - returns a pointer to the node that matched the target
template <class T>
bool BinarySearchTree<T>::_search(BinaryNode<T> *nodePtr, const T target, std::vector<T> *returnedItem) const
{
	if (nodePtr == nullptr)
	{
		return false;
	}

	if (*(nodePtr->getItem()) > *(target))
	{
		return _search(nodePtr->getLeftPtr(), target, returnedItem);
	}
	else
	{
		if (*(nodePtr->getItem()) < *(target))
		{
			return _search(nodePtr->getRightPtr(), target, returnedItem);
		}
		else
		{
			returnedItem->push_back(nodePtr->getItem());
			if (nodePtr->getRightPtr() != nullptr && (nodePtr->getRightPtr()->getItem()) == target) // if right node is not null and equal target
			{
				return _search(nodePtr->getRightPtr(), target, returnedItem);
			}
			return true;
		}
	}
	return false;
}

//-Implementation for the remove operation
// - return true if target is found and deleted, otherwise
// - returns false if the node is not found
template <class T>
BinaryNode<T> *BinarySearchTree<T>::remove(const T &target)
{
	BinaryNode<T> *parent = nullptr;
	BinaryNode<T> *cur = this->rootPtr;
	while (cur != nullptr)
	{ // Search for node
		if (cur->getItem() == target)
		{																																		 // Node found
			if (cur->getLeftPtr() == nullptr && cur->getRightPtr() == nullptr) // Remove leaf node
			{
				if (parent == nullptr) // Node is root
					this->rootPtr == nullptr;
				else if (parent->getLeftPtr() == cur)
					parent->setLeftPtr() == nullptr;
				else
					parent->setRightPtr() == nullptr;
			}
			else if (cur->getRightPtr() == nullptr) // Remove node with only left child
			{
				if (parent == nullptr) // Node is root
					this->rootPtr = cur->getLeftPtr();
				else if (parent->getLeftPtr() == cur)
					parent->setLeftPtr() = cur->getLeftPtr();
				else
					parent->setRightPtr() = cur->getLeftPtr();
			}
			else if (cur->getLeftPtr() == nullptr) // Remove node with only right child
			{
				if (parent == nullptr) // Node is root
					this->rootPtr = cur->getRightPtr();
				else if (parent->getLeftPtr() == cur)
					parent->setLeftPtr() = cur->getLeftPtr();
				else
					parent->setRightPtr() = cur->getRightPtr();
			}
			else // Remove node with two children
			{
				// Find successor (leftmost child of right subtree)
				BinaryNode<T> *suc = cur->getRightPtr();
				while (suc->getLeftPtr() != nullptr)
				{
					suc = suc->getLeftPtr();
				}
				T successorDataCopy = suc->getItem();		//  Create copy of suc's data
				_remove(this->rootPtr, suc->getItem()); // Remove successor
				cur->setItem() = successorDataCopy;			//  Assign cur's data with successorData
			}
			return true; // Node found and removed
		}
		else if (cur->getItem() < target) // Search right
		{
			parent = cur;
			cur = cur->getRightPtr();
		}
		else
		{ // Search left
			parent = cur;
			cur = cur->getLeftPtr();
		}
	}
	return false; // Node not found
}

#endif
