#pragma once
#pragma once
// Binary tree abstract base class
// Created by A. Student
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"


template<class T>
class BinaryTree
{
protected:
	BinaryNode<T>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<T>& tree) { }
	virtual ~BinaryTree() { destroyTree(rootPtr); }

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(T&)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(T&)) const { _inorder(visit, rootPtr); }
	void postOrder(void visit(T&)) const { _postorder(visit, rootPtr); }
	void printTree(void visit(T&, int)) const { _printTree(visit, rootPtr, 1); }
	void printLeafNodes(void visit(T&)) const { _printLeafNodes(visit, rootPtr); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const T& newData) = 0;
	//virtual bool remove(const T &data) = 0;
	virtual bool search(const T& target, T& returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<T>* nodePtr);

	// internal traverse
	void _preorder(void visit(T&), BinaryNode<T>* nodePtr) const;
	void _inorder(void visit(T&), BinaryNode<T>* nodePtr) const;
	void _postorder(void visit(T&), BinaryNode<T>* nodePtr) const;
	void _printTree(void visit(T&, int), BinaryNode<T>* nodePtr, int level) const;
	void _printLeafNodes(void visit(T&), BinaryNode<T>* rootPtr) const;
};

//Destroy the entire tree
template<class T>
void BinaryTree<T>::destroyTree(BinaryNode<T>* nodePtr)
{
	if (nodePtr) // != NULL
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		//cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
		delete nodePtr;
	}
}

//Preorder Traversal
template<class T>
void BinaryTree<T>::_preorder(void visit(T&), BinaryNode<T>* nodePtr) const
{
	/* Write your code here */
	if (nodePtr) // != NULL    // added by Omar
	{
		T item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}

}

//Inorder Traversal
template<class T>
void BinaryTree<T>::_inorder(void visit(T&), BinaryNode<T>* nodePtr) const
{
	if (nodePtr) // != NULL
	{
		T item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//Postorder Traversal
template<class T>
void BinaryTree<T>::_postorder(void visit(T&), BinaryNode<T>* nodePtr) const
{
	/* Write your code here */
	if (nodePtr) {// added by Omar
		T item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_postorder(visit, nodePtr->getRightPtr());
	}
}

//Prints tree as an indented list
template<class T>
void BinaryTree<T>::_printTree(void visit(T&, int), BinaryNode<T>* nodePtr, int level) const
{
	/* Write your code here */
	if (nodePtr) // != NULL  // added by Omar
	{
		T item = nodePtr->getItem();
		visit(item, level);
		level++;
		_printTree(visit, nodePtr->getRightPtr(), level);
		_printTree(visit, nodePtr->getLeftPtr(), level);
	}
}

template<class T>
void BinaryTree<T>::_printLeafNodes(void visit(T&), BinaryNode<T>* nodePtr) const {

	if (!nodePtr) // != NULL
		return;

	if (nodePtr->isLeaf())
	{
		T item = nodePtr->getItem();
		visit(item);
		return;
	}

	if (nodePtr->getLeftPtr())
		_printLeafNodes(visit, nodePtr->getLeftPtr());
	if (nodePtr->getRightPtr())
		_printLeafNodes(visit, nodePtr->getRightPtr());
}

#endif

