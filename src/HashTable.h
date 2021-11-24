//
//  HashTable.h
//  CIS_22C_PROJECT
//
//  Created by Sarina Karki on 11/6/21.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
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
    HashTable()
    {
        count = 0;
        hashSize = 53;
        collisionCount = 0;
        hashAry = new LinkedList<T>[hashSize];
    }
    HashTable(int n)
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
    bool remove(T *itemOut, const T *key);
    bool search(T *itemOut, const T *key);
    int newSize();
    void rehash();
    bool isPrime(int);
    bool getListItem(T **dataOut);
};

/*~*~*~*
   Hash function: using pseudorandom generation
*~**/
template <class T>
int HashTable<T>::hash(const T *key)
{
    std::string pkey = key->getId();
    int sum = 0;
    for (int i = 0; i < pkey.size(); i++)
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
    int homeAddr = hash(itemIn);
    bool duplicate;
    T *itemOut = nullptr;

    duplicate = hashAry[homeAddr].searchList(itemIn, itemOut);
    if (duplicate == false)
    {
        hashAry[homeAddr].insertNode(itemIn);
        if (hashAry[homeAddr].getLength() == 1)
        {
            count++;
            double loadfactor = getLoadFactor();
            if (loadfactor >= 75)
            {
                rehash();
            }
        }
        else
        {
            collisionCount++;
        }
        return true;
    }
    return false;
}

/*~*~*~*
   hash search - chaining
   if found:
      - copy data to itemOut
   if not found, returns false
 *~**/
template <class T>
bool HashTable<T>::search(T *result, const T *query)
{
    hashAry[hash(query)].displayList();

    return hashAry[hash(query)]
        .searchList(query, result);
}

/*~*~*~*
   Removes the item with the matching key from the hash table
*~**/
template <class T>
bool HashTable<T>::remove(T *itemOut, const T *key)
{
    int homeAddr = hash(key);
    bool deleted = false;
    deleted = hashAry[homeAddr].deleteNode(key, itemOut);
    if (hashAry[homeAddr].getLength() == 0)
    {
        count--;
    }

    return deleted;
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

/*~*~*~*
   displayStatistics() print out:
    -load factor
    -total collision count
    -length of the longest linked list
    -number of linked lists
    -size of the hash table
*~**/
template <class T>
void HashTable<T>::displayStatistics()
{
    std::cout << "~*-----------Statistics-----------*~" << std::endl;
    std::cout << "Load factor: " << getLoadFactor() << "%" << std::endl;
    std::cout << "Total collision count: " << getCollisionCount() << std::endl;
    std::cout << "Length of the longest linked list: " << getLengthOfLongest() << std::endl;
    std::cout << "Number of linked lists: " << count << std::endl;
    std::cout << "Size of hash table: " << hashSize << std::endl;
    std::cout << "----------------------------------" << std::endl;
}

/*~*~*~*
   newSize()returns the next prime number of 2 * hashSize to determine the hashSize for the new hash table.
*~**/
template <class T>
int HashTable<T>::newSize()
{
    int number;
    number = hashSize * 2;
    if (number <= 1)
        return 2;

    int prime = number;
    bool found = false;

    // Loop continuously until isPrime returns
    while (!found)
    {
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
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
    std::cout << "Rehashing the hash table" << std::endl;
    int oldSize = hashSize;
    LinkedList<T> *oldAry = hashAry;

    hashSize = newSize();
    hashAry = new LinkedList<T>[hashSize];
    T *itemOut;
    count = 0;
    for (int i = 0; i < oldSize; i++)
    {
        while (oldAry[i].getLength() != 0)
        {
            itemOut = oldAry[i].pop(); //STACK
            insert(itemOut);
        }
    }
    delete[] oldAry;
}

#endif /* HashTable_h */