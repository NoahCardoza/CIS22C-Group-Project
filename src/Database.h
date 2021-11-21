#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "BinarySearchTree.h"
#include "HashTable.h"

using namespace std;

using std::string;

// TODO: figure out how to use interfaces and inherit
// from it for Patient class

template <class T>
class Database
{
private:
  bool opened = false;
  BinarySearchTree<T *> bst;
  HashTable<T> hashmap;
  vector<T *> records;
  virtual string getHeader() = 0;

public:
  bool open(string filename);
  bool save(string filename);
  T *primarySearch(T *search);
  T *secondarySearch(T *search);

  /**
   * Empties the vector holding the
   * pointers to the records in the
   * database and frees them
   */
  ~Database(void)
  {
    T *record;

    while (!records.empty())
    {
      record = records.back();
      records.pop_back();
      delete record;
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
bool Database<T>::open(string filename)
{
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
      bst.insert(record);
      hashmap.insert(record);
      records.push_back(record);
      record = new T();
    }
  }

  // delete the left over empty record
  delete record;

  opened = true;

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
bool Database<T>::save(string filename)
{
  if (!opened)
  {
    // we can't save a database that hasn't been opened
    return false;
  }

  ofstream out(filename);

  out << getHeader() << endl;

  // TODO: iterate the HashTable to write
  // in the same order
  for (auto const &record : records)
  {
    record->toStream(&out);
  }

  out.close();

  return true;
}

template <class T>
T *Database<T>::primarySearch(T *)
{
  T *ret;

  if (hashmap.search(search, ret))
  {
    return ret;
  };

  return nullptr;
}

template <class T>
T *Database<T>::secondarySearch(T *search)
{
  T *ret;

  if (bst.search(search, ret))
  {
    return ret;
  };

  return nullptr;
}
#endif
