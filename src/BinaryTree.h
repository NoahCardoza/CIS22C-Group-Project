#pragma once
#pragma once
// Binary tree abstract base class

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template <class T>
class BinaryTree
{
protected:
	BinaryNode<T> *rootPtr; // ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree()
	{
		rootPtr = 0;
		count = 0;
	}

	virtual ~BinaryTree() { destroyTree(rootPtr); }

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	void clear()
	{
		destroyTree(rootPtr);
		rootPtr = 0;
		count = 0;
	}

	void inOrder(void visit(T)) const { _inorder(visit, rootPtr); }
	void printTree(void visit(T, int)) const { _printTree(visit, rootPtr, 1); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const T &newData) = 0;
	//virtual bool remove(const T &data) = 0;
	virtual bool search(const T &target, std::vector<T> *returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<T> *nodePtr);

	// internal traverse
	void _inorder(void visit(T), BinaryNode<T> *nodePtr) const;
	void _printTree(void visit(T, int), BinaryNode<T> *nodePtr, int level) const;
};

//Destroy the entire tree
template <class T>
void BinaryTree<T>::destroyTree(BinaryNode<T> *nodePtr)
{
	if (nodePtr) // != nullptr
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		//cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
		delete nodePtr;
	}
}

//Inorder Traversal
template <class T>
void BinaryTree<T>::_inorder(void visit(T), BinaryNode<T> *nodePtr) const
{
	if (nodePtr) // != nullptr
	{
		T item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//Prints tree as an indented list
template <class T>
void BinaryTree<T>::_printTree(void visit(T, int), BinaryNode<T> *nodePtr, int level) const
{
	if (nodePtr) // != nullptr  // added by Omar
	{
		for (T item : nodePtr->getItems())
		{
			visit(item, level);
		}

		level++;
		_printTree(visit, nodePtr->getRightPtr(), level);
		_printTree(visit, nodePtr->getLeftPtr(), level);
	}
}

#endif
