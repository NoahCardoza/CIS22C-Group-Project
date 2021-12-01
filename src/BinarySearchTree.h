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
	bool insert(const T &item);																				// insert a node at the correct location
	T remove(const T target);																					// remove a node if found
	bool search(const T &target, std::vector<T> *returnedItem) const; // find a target node
private:
	BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNode); // internal insert node: insert newNode in nodePtr subtree
	BinaryNode<T> *_remove(BinaryNode<T> *root, const T target, T *deleted);
	bool _search(BinaryNode<T> *treePtr, const T target, std::vector<T> *returnedItem) const; // search for target node
};

///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template <class T>
bool BinarySearchTree<T>::insert(const T &newEntry)
{
	BinaryNode<T> *newNodePtr = new BinaryNode<T>(newEntry);
	if (this->isEmpty())
	{
		this->rootPtr = newNodePtr;
		this->count++;
	}
	else
	{
		this->rootPtr = _insert(this->rootPtr, newNodePtr);
	}

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
BinaryNode<T> *BinarySearchTree<T>::_insert(BinaryNode<T> *node, BinaryNode<T> *newNode)
{
	if (!node)
	{
		return newNode;
	}

	if ((*newNode->getItem()) < (*node->getItem()))
	{
		node->setLeftPtr(_insert(node->getLeftPtr(), newNode));
	}
	else
	{
		node->setRightPtr(_insert(node->getRightPtr(), newNode));
	}

	return node;
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
	else if (*(nodePtr->getItem()) < *(target))
	{
		return _search(nodePtr->getRightPtr(), target, returnedItem);
	}
	else
	{
		BinaryNode<T> *cur = nodePtr;

		while (cur && *(cur->getItem()) == *(target))
		{
			returnedItem->push_back(cur->getItem());
			cur = cur->getRightPtr();
		}

		return true;
	}
	return false;
}

//-Implementation for the remove operation
// - return true if target is found and deleted, otherwise
// - returns false if the node is not found
template <class T>
T BinarySearchTree<T>::remove(const T target)
{
	T deleted = nullptr;

	this->rootPtr = _remove(this->rootPtr, target, &deleted);

	return deleted;
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::_remove(BinaryNode<T> *root, const T key, T *deleted)
{
	// base case
	if (root == nullptr)
		return root;

	// search the left subtree
	if (*key < *root->getItem())
		root->setLeftPtr(_remove(root->getLeftPtr(), key, deleted));

	// search the right subtree
	else if (*key > *root->getItem())
		root->setRightPtr(_remove(root->getRightPtr(), key, deleted));

	// deleted the node
	else if (key->getId() == root->getItem()->getId())
	{
		// save the pointer to the soon to be deleted item
		*deleted = root->getItem();

		// node has no child
		if (root->getLeftPtr() == nullptr and root->getRightPtr() == nullptr)
			return nullptr;

		// node with only one child or no child
		else if (root->getLeftPtr() == nullptr)
		{
			BinaryNode<T> *temp = root->getRightPtr();
			delete root;
			return temp;
		}
		else if (root->getRightPtr() == nullptr)
		{
			BinaryNode<T> *temp = root->getLeftPtr();
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor
		// (smallest in the right subtree)
		BinaryNode<T> *temp = root->getRightPtr();
		while (temp && temp->getLeftPtr() != nullptr)
			temp = temp->getLeftPtr();

		// Copy the inorder successor's content to this node
		root->setItem(temp->getItem());

		// Delete the inorder successor
		T dummy;
		root->setRightPtr(_remove(root->getRightPtr(), temp->getItem(), &dummy));
	}
	else
	{
		root->setRightPtr(_remove(root->getRightPtr(), key, deleted));
	}

	return root;
}

#endif
