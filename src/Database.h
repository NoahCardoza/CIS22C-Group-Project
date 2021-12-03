#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Patient.h"

using namespace std;

using std::string;

template <class T>
class HashMapSaveToFileIter : public LinkedListIterator<T>
{
private:
  ofstream *stream;

public:
  HashMapSaveToFileIter(ofstream *stream)
  {
    this->stream = stream;
  }

  void cb(T record)
  {
    record->toStream(stream);
  }
};

template <class T>
class Database
{
private:
  bool opened = false;
  BinarySearchTree<T *> *bst = nullptr;
  HashTable<T> *hashmap = nullptr;
  virtual std::string getHeader() = 0;

public:
  bool isOpen() { return opened; };
  int size() { return bst && bst->getCount() || 0; };
  bool open(std::string filename);
  bool create();
  bool close();
  bool save(std::string filename);
  bool primarySearch(T *search, T **result);
  bool secondarySearch(T *search, std::vector<T *> &ret);
  bool remove(T *query, T **result);
  bool insert(T *item);
  void displayData(void visit(T *));
  void displayStatistics();
  void displayDataIndented(void visit(T *, int));
  static void free(T *record)
  {
    delete record;
  };

  /**
   * Empties the vector holding the
   * pointers to the records in the
   * database and frees them
   */
  ~Database(void)
  {
    if (opened)
    {
      bst->inOrder(free);
      delete hashmap;
      delete bst;
    }
  }
};

/**
 * Accept a string representing the path
 * to a CSV file that contains the
 * information needed to populate
 * the database.
 *
 * Returns success code.
 */
template <class T>
bool Database<T>::open(std::string filename)
{
  vector<T *> records;
  if (opened)
  {
    // you can't open a new database file
    // while one is already opened
    return false;
  }

  ifstream in(filename);

  if (!in)
  {
    return false;
  }

  T *record = new T();

  in.ignore(127, '\n'); // read past the CSV header

  while (in.good())
  {
    if (record->fromStream(&in))
    {
      records.push_back(record);
      record = new T();
    }
  }

  in.close();

  // delete the left over empty record
  delete record;

  bst = new BinarySearchTree<T *>();
  hashmap = new HashTable<T>(HashTable<T>::calculateHashSize(records.size()));

  for (auto record : records)
  {
    bst->insert(record);
    hashmap->insert(record);
  }

  opened = true;

  return true;
}

template <class T>
bool Database<T>::create()
{
  if (opened)
  {
    return false;
  }

  bst = new BinarySearchTree<T *>();
  hashmap = new HashTable<T>;

  opened = true;

  return true;
}

/**
 * Close the database freeing all the
 * pointers ready to close the program
 * or open another file.
 *
 * Don't forget to save!
 *
 * Returns success code.
 */
template <class T>
bool Database<T>::close()
{
  if (!opened)
  {
    // you can't close and unopened db
    return false;
  }

  bst->inOrder(free);

  delete bst;
  delete hashmap;

  opened = false;

  return true;
}

/**
 * Accept a string representing the path
 * for which the database in memory will
 * be saved to the filesystem.
 *
 * Returns success code.
 */
template <class T>
bool Database<T>::save(std::string filename)
{
  if (!opened)
  {
    // we can't save a database that hasn't been opened
    return false;
  }

  ofstream out(filename);

  out << getHeader() << endl;

  HashMapSaveToFileIter<T *> iter(&out);
  hashmap->iterate(&iter);

  out.close();

  return true;
}

template <class T>
bool Database<T>::primarySearch(T *search, T **result)
{
  return hashmap->search(search, result);
}

template <class T>
bool Database<T>::secondarySearch(T *search, std::vector<T *> &ret)
{
  return bst->search(search, &ret);
}

template <class T>
bool Database<T>::insert(T *item)
{
  if (hashmap->insert(item) && bst->insert(item))
  {
    return true;
  }

  return false;
}

template <class T>
bool Database<T>::remove(T *query, T **result)
{
  if (hashmap->remove(query, result))
  {
    if (bst->remove(*result))
    {
      return true;
    }
  }

  return false;
}

template <class T>
void Database<T>::displayData(void visit(T *))
{
  bst->inOrder(visit);
}

template <class T>
void Database<T>::displayStatistics()
{
  hashmap->displayStatistics();
}

template <class T>
void Database<T>::displayDataIndented(void visit(T *, int))
{
  bst->printTree(visit);
}

#endif
