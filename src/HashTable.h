//
//  HashTable.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <vector>
#include <iomanip>
#include "LinkedList.h"

template <class T>
class HashTable
{
private:
    LinkedList<T> *hashAry;
    int hashSize;
    int count;
    int collisionCount;
    int hash(const T *key);

public:
    HashTable(int n = 11)
    {
        count = 0;
        hashSize = n;
        collisionCount = 0;
        hashAry = new LinkedList<T>[hashSize];
    }
    ~HashTable() { delete[] hashAry; }

    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    int getCollisionCount() const { return collisionCount; }
    int getLengthOfLongest() const;
    void displayStatistics();

    bool isEmpty() const { return count == 0; }
    bool insert(T *itemIn);
    bool remove(const T *key, T **itemOut);
    bool search(const T *key, T **itemOut);
    void rehash();

    bool getListItem(T **dataOut);

    void iterate(LinkedListIterator<T *> *iter);

    static int calculateHashSize(int);
    static bool isPrime(int);
};

/*~*~*~*
   Hash function: using pseudorandom generation
*~**/
template <class T>
int HashTable<T>::hash(const T *key)
{
    std::string pkey = key->getId();
    int sum = 0;
    for (int i = 0; i < (int)pkey.size(); i++)
    {
        sum += pkey[i];
    }
    return (3 * sum + 7) % hashSize;
}

/*~*~*~*
   Insert an item into the hash table
   It rejects duplicates
*~**/
template <class T>
bool HashTable<T>::insert(T *itemIn)
{
    LinkedList<T> *home = hashAry + hash(itemIn);

    T *dummy = nullptr;

    if (!home->getLength())
    {
        count++;
    }
    else if (home->searchList(itemIn, &dummy))
    {
        return false;
    }
    else
    {
        collisionCount++;
    }

    home->insertNode(itemIn);

    if (getLoadFactor() >= 75)
    {
        rehash();
    }

    return true;
}

/*~*~*~*
   hash search - chaining
   if found:
      - copy data to itemOut
   if not found, returns false
 *~**/
template <class T>
bool HashTable<T>::search(const T *query, T **result)
{
    return hashAry[hash(query)]
        .searchList(query, result);
}

/*~*~*~*
   Removes the item with the matching key from the hash table
*~**/
template <class T>
bool HashTable<T>::remove(const T *key, T **itemOut)
{
    int homeAddr = hash(key);
    bool success;

    success = hashAry[homeAddr].deleteNode(key, itemOut);

    if (hashAry[homeAddr].getLength() == 0)
    {
        count--;
    }
    else
    {
        collisionCount--;
    }

    return success;
}

/*~*~*~*
   getLengthOfLongest traverses the hash table to find the longest linked list
   and return the length of the longest linked list.
*~**/
template <class T>
int HashTable<T>::getLengthOfLongest() const
{
    int max = hashAry[0].getLength();
    int i = 1;
    while (i < hashSize)
    {
        if (max < hashAry[i].getLength())
        {
            max = hashAry[i].getLength();
        }
        i++;
    }
    return max;
}

/**
 * displayStatistics() print out:
 *   -load factor
 *   -total collision count
 *   -length of the longest linked list
 *   -number of linked lists
 *   -size of the hash table 
**/
template <class T>
void HashTable<T>::displayStatistics()
{
    std::cout << "┌────────-== Statistics ==-─────────┬──────────┐" << std::endl;
    std::cout << "│ Load factor                       │ " << std::left << std::setprecision(4) << std::setw(5) << getLoadFactor() << "%   │" << std::endl;
    std::cout << "├───────────────────────────────────┼──────────┤" << std::endl;
    std::cout << "│ Total collision count             │ " << std::left << std::setw(8) << getCollisionCount() << " │" << std::endl;
    std::cout << "├───────────────────────────────────┼──────────┤" << std::endl;
    std::cout << "│ Length of the longest linked list │ " << std::left << std::setw(8) << getLengthOfLongest() << " │" << std::endl;
    std::cout << "├───────────────────────────────────┼──────────┤" << std::endl;
    std::cout << "│ Number of linked lists            │ " << std::left << std::setw(8) << count << " │" << std::endl;
    std::cout << "├───────────────────────────────────┼──────────┤" << std::endl;
    std::cout << "│ Size of hash table                │ " << std::left << std::setw(8) << hashSize << " │" << std::endl;
    std::cout << "└───────────────────────────────────┴──────────┘" << std::endl;
}

/*~*~*~*
   calculateHashSize() returns the next prime number of 2 * hashSize to determine the hashSize for the new hash table.
*~**/
template <class T>
int HashTable<T>::calculateHashSize(int n)
{
    n = n * 2;

    if (n <= 1)
        return 2;

    // Loop continuously until isPrime returns
    while (1)
    {
        n++;
        if (isPrime(n))
            return n;
    }
}

/*~*~*~*
   isPrime returns true if the number is prime and returns false otherwise
*~**/
template <class T>
bool HashTable<T>::isPrime(int n)
{

    for (int i = 2; i < n / 2; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

/*~*~*~*
   rehash() creates a new hash table with hashSize = the next prime number of 2 * original hash size, reallocate all items to the new hash table, and finally delete the old hash table.
*~**/
template <class T>
void HashTable<T>::rehash()
{
    int oldSize = hashSize;
    LinkedList<T> *oldAry = hashAry;

    hashSize = calculateHashSize(hashSize);
    hashAry = new LinkedList<T>[hashSize];

    count = 0;
    for (int i = 0; i < oldSize; i++)
    {
        while (oldAry[i].getLength() > 0)
        {
            insert(oldAry[i].pop());
        }
    }
    delete[] oldAry;
}

/*~*~*~*
   rehash() creates a new hash table with hashSize = the next prime number of 2 * original hash size, reallocate all items to the new hash table, and finally delete the old hash table.
*~**/
template <class T>
void HashTable<T>::iterate(LinkedListIterator<T *> *iter)
{
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAry[i].getLength())
        {
            hashAry[i].iterate(iter);
        }
    }
}

#endif /* HashTable_h */