//
//  HashTable.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashTable_h
#define HashTable_h
#include "LinkedList.h"

template<class ItemType>
class HashTable
{
private:
    LinkedList<ItemType>* hashAry;
    int hashSize;
    int count;
    int hash(const ItemType &key);
    
public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
    HashTable(int n)    { count = 0; hashSize = n; hashAry = new HashNode<ItemType>[hashSize]; }
    ~HashTable(){ delete [] hashAry; }

    int getCount() const    { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return 100.0 * count / hashSize; }
    int getLengthOfLongest() const;
    void displayStatistics();
    
    bool isEmpty() const    { return count == 0; }
    bool insert( const ItemType* itemIn);
    bool remove( ItemType** itemOut, const ItemType* key);
    bool search( ItemType** itemOut, const ItemType* key);
    int newSize();
    void rehash();
    bool isPrime(int);
    bool getListItem(ItemType& dataOut);
}

/*~*~*~*
  A hash function: using pseudorandum generation
 *~**/
template<class ItemType>
int HashTable<ItemType>::hash(const ItemType* key)
{
    string Ikey = key->getID();

    
}
#endif /* HashTable_h */
