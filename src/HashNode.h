//
//  HashNode.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashNode_h
#define HashNode_h

template <class T>
class HashNode
{
private:
	T *ptrItem;
	HashNode *next;
	int collisions;

public:
	//constructors
	HashNode()
	{
		next = nullptr;
		collisions = 0;
	}
	HashNode(T *pItem)
	{
		ptrItem = pItem;
		next = nullptr;
		collisions = 0;
	}
	HashNode(T *pItem, HashNode *nextPtr, int col)
	{
		ptrItem = pItem;
		nextPtr = nullptr;
		collisions = col;
	}

	//setters
	void setItem(const T *pItem) { ptrItem = pItem; }
	void setNext(HashNode *nextPtr) { next = nextPtr; }
	void setCollisions(int col) { collisions = col; }

	//getters
	T *getItem() const { return ptrItem; }
	HashNode *getNext() const { return next; }
	int getCollisions() const { return collisions; }
};

#endif /* HashNode_h */
