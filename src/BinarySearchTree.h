#pragma once
// Binary Search Tree ADT that creates a tree of pointers to data base object of pateints.
// it manipulates the objects by either inserting objects, removing objects, and searching for
// an objects.
// BST inherits Binary Tree.

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include <vector>
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
	bool insert(const T &item);																				// wrapper function to insert new nodes. True if inserted, false if not.																				// insert a node at the correct location
	T remove(const T target);																					// wrapper function to remove a node. Return removed node oif found.																				// remove a node if found
	bool search(const T &target, std::vector<T> *returnedItem) const; // find a target node. Treu if found, false if not.
private:
	BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNode);										// internal insert node: insert newNode in nodePtr subtree.
	BinaryNode<T> *_remove(BinaryNode<T> *root, const T target, T *deleted, bool force);			// internal remove found node and returns a removed node.
	bool _search(BinaryNode<T> *treePtr, const T target, std::vector<T> *returnedItem) const; // internal search for target node and returns true if found nodes.
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
	}
	else
	{
		this->rootPtr = _insert(this->rootPtr, newNodePtr);
	}

	this->count++;

	return true;
}

// - Wrapper function.
// - it calls the private _search function that returns bool.
// - if found a node or a vector of duplicate node pointers or nullptr.
// - if found, it refrences data from that node and sends it back to the caller.
// - or uses a vector of duplicate found nodes.
template <class T>
bool BinarySearchTree<T>::search(const T &anEntry, std::vector<T> *returnedItem) const
{
	return _search(this->rootPtr, anEntry, returnedItem);
}

//////////////////////////// private functions ////////////////////////////////////////////

// - Implementation of the private insert operation.
// - it insert a new node into the BST in inorder and return a pointer
// - to inserted node.
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
	else if ((*newNode->getItem()) > (*node->getItem()))
	{
		node->setRightPtr(_insert(node->getRightPtr(), newNode));
	}
	else
	{
		node->addItem(newNode->getItem());
	}

	return node;
}

// - Implementation for the search operation
// - return nullptr if target not found, otherwise
// - returns a true. It uses vector of pointers if duplicate nodes foind.
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
		*returnedItem = nodePtr->getItems();

		return true;
	}
	return false;
}

// - Implementation for the remove operation
// - wrapper function calls private function _remove(). it returns
// - removed node true if target is found and deleted.
template <class T>
T BinarySearchTree<T>::remove(const T target)
{
	T deleted = nullptr;

	this->rootPtr = _remove(this->rootPtr, target, &deleted, false);

	if (deleted)
	{
		this->count--;
	}

	return deleted;
}

// - private remove function.
// - it returns removed node if found. it replaces the mostleft node with
// - the removed node.

template <class T>
BinaryNode<T> *BinarySearchTree<T>::_remove(BinaryNode<T> *root, const T key, T *deleted, bool force)
{
	// base case
	if (root == nullptr)
		return root;

	// search the left subtree
	if (*key < *root->getItem())
		root->setLeftPtr(_remove(root->getLeftPtr(), key, deleted, force));

	// search the right subtree
	else if (*key > *root->getItem())
		root->setRightPtr(_remove(root->getRightPtr(), key, deleted, force));

	// deleted the node
	else
	{
		T item = root->removeItem(key);

		if (!item)
		{
			return root;
		}

		*deleted = item;

		if (!force && !root->isEmpty())
		{
			return root;
		};

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
		// root->setItem(temp->getItem());
		root->copyNode(temp);

		// Delete the inorder successor
		T dummy;
		root->setRightPtr(_remove(root->getRightPtr(), temp->getItem(), &dummy, true));
	}

	return root;
}

#endif
