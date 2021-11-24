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
	bool remove(const T &item);
	// find a target node
	bool search(const T &target, T &returnedItem) const;
	// find the smallest node
	bool findSmallest(T &returnedItem) const;
	// find the largest node
	bool findLargest(T &returnedItem) const;

private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNode);

	// search for target node
	BinaryNode<T> *_search(BinaryNode<T> *treePtr, const T &target) const;

	// find the smallest node
	BinaryNode<T> *_findSmallest(BinaryNode<T> *nodePtr, T &smallest) const;

	// find the largest node
	BinaryNode<T> *_findLargest(BinaryNode<T> *nodePtr, T &smallest) const;

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<T>* _remove(BinaryNode<T>* nodePtr, const T target, bool &success);

	// delete target node from tree, called by internal remove node
	BinaryNode<T>* _removeNode(BinaryNode<T>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<T>* _removeLeftmostNode(BinaryNode<T>* nodePtr, T &successor);
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
bool BinarySearchTree<T>::search(const T &anEntry, T &returnedItem) const
{
	BinaryNode<T> *temp = nullptr;
	/* Write your code here */
	temp = _search(this->rootPtr, anEntry);
	if (!temp)
	{
		return false;
	}
	returnedItem = temp->getItem();
	return true;
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
		if (*(nodePtr->getItem()) > *(newNodePtr->getItem()))
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
BinaryNode<T>* BinarySearchTree<T>::_search(BinaryNode<T> *nodePtr,
											const T &target) const
{
	BinaryNode<T>*> found() = nullptr; 

	if (nodePtr == nullptr)
	{
		return found;
	}

	if (*(nodePtr->getItem()) > *(target))
	{
		return _search(nodePtr->getLeftPtr(), target);
	}
	else
	{
		if (*(nodePtr->getItem()) < *(target))
		{
			return _search(nodePtr->getRightPtr(), target);
		}
		else
		{
			found = nodePte;
			return found;
		}
	}
}

template <class T>
bool remove(const T &item)
{
   parent = null
   cur = tree⇢root
   while (cur is not null) { // Search for node
      if (cur⇢key == key) { // Node found 
         if (cur⇢left is null && cur⇢right is null) { // Remove leaf
            if (par is null) // Node is root
               tree⇢root = null
            else if (par⇢left == cur) 
               par⇢left = null
            else
               par⇢right = null
         }
         else if (cur⇢right is null) {                // Remove node with only left child
            if (par is null) // Node is root
               tree⇢root = cur⇢left
            else if (par⇢left == cur) 
               par⇢left = cur⇢left
            else
               par⇢right = cur⇢left
         }
         else if (cur⇢left is null) {                // Remove node with only right child
            if (par is null) // Node is root
               tree⇢root = cur⇢right
            else if (par⇢left == cur) 
               par⇢left = cur⇢right
            else
               par⇢right = cur⇢right
         }
         else {                                      // Remove node with two children
            // Find successor (leftmost child of right subtree)
            suc = cur⇢right
            while (suc⇢left is not null)
               suc = suc⇢left
            successorData = Create copy of suc's data
            BSTRemove(tree, suc⇢key)     // Remove successor
            Assign cur's data with successorData
         }
         return // Node found and removed
      }
      else if (cur⇢key < key) { // Search right
         par = cur
         cur = cur⇢right
      }
      else {                     // Search left
         par = cur
         cur = cur⇢left
      }
   }
   return // Node not found
	   _remove(BinaryNode<T>* nodePtr, const T target, bool &success);
	   _removeNode(BinaryNode<T>* targetNodePtr);
	   _removeLeftmostNode(BinaryNode<T>* nodePtr, T &successor);// remove most left node
}
	



#endif
