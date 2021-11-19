//
//  HashTable.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashTable_h
#define HashTable_h
#include "LinkedList.h"

template <class T>
class HashTable
{
private:
    LinkedList<T> *hashAry;
    int hashSize;
    int count;
    int hash(const T &key);

public:
    HashTable()
    {
        count = 0;
        hashSize = 53;
        hashAry = new HashNode<T>[hashSize];
    }
    HashTable(int n)
    {
        count = 0;
        hashSize = n;
        hashAry = new HashNode<T>[hashSize];
    }
    ~HashTable() { delete[] hashAry; }

    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    int getLengthOfLongest() const;
    void displayStatistics();

    bool isEmpty() const { return count == 0; }
    bool insert(const T *itemIn);
    bool remove(T **itemOut, const T *key);
    bool search(T **itemOut, const T *key);
    int newSize();
    void rehash();
    bool isPrime(int);
    bool getListItem(T &dataOut);
};

#endif /* HashTable_h */
