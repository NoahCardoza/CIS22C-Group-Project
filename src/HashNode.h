//
//  HashNode.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashNode_h
#define HashNode_h

template<class ItemType>
class HashNode
{
private:
    ItemType* ptrItem;
    HashNode *next;
    int nCollision;
    
public:
    //constructors
    HashNode() {next = NULL; nCollisions = 0;}
    HashNode(ItemType* pItem ) {ptrItem = pItem; next = NULL; nCollision = 0;}
    HashNode(ItemType* pItem, HashNode* nextPtr, int nCol)
            {ptrItem = pItem; nextPtr = NULL; nCollision = nCol;}
    
    //setters
    void setItem(const ItemType* pItem) {ptrItem = pItem;}
    void setNext(HashNode* nextPtr) {next = nextPtr;}
    void setNoCollisions(int nCol) {noCollisions = nCol;}
    
    //getters
    ItemType* getItem() const {return ptrItem;}
    HashNode* getNext() const {return next;}
    int getNoCollisions() const {return noCollisions;}
};

#endif /* HashNode_h */
