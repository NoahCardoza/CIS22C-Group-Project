#include <string>
#include <assert.h>

#include "../src/BinarySearchTree.h"
#include "../src/Patient.h"

void populate_tree(BinarySearchTree<Patient *> &tree);

int main(void)
{
  BinarySearchTree<Patient *> bst;
  Patient query;
  Patient *result = nullptr;

  populate_tree(bst);

  // create out query instance
  query.setName("Samwise Gamgee");

  // confirm a match was found
  assert(bst.search(&query, result));

  // confirm the result pointer was set
  assert(result);

  // confim the right record was returned
  assert(result->getAge() == 20);

  // test that we infact are dealing with a pointer
  result->setAge(23);
  result = nullptr;

  assert(bst.search(&query, result));
  assert(result);

  // make sure the ealier changes actually mutated the instance
  assert(result->getAge() == 23);

  // TODO: test delete
  // TODO: test other required functions
  // TODO: free memory

  return 0;
}

void populate_tree(BinarySearchTree<Patient *> &tree)
{
  Patient *record;

  record = new Patient();
  record->setName("Frodo Baggins");
  record->setAge(21);

  tree.insert(record);

  record = new Patient();
  record->setName("Alfrid Lickspittle");
  record->setAge(31);

  tree.insert(record);

  record = new Patient();
  record->setName("Samwise Gamgee");
  record->setAge(20);

  tree.insert(record);
}