#include <string>
#include <vector>
#include <assert.h>

#include "../src/BinarySearchTree.h"
#include "../src/Patient.h"

void populate_tree(BinarySearchTree<Patient *> &tree);

int main(void)
{
  BinarySearchTree<Patient *> bst;
  Patient query;
  Patient *result;
  vector<Patient *> patients;

  populate_tree(bst);

  query.setName("Samwise Gamgee");       // create out query instance
  assert(bst.search(&query, &patients)); // confirm a match was found
  assert(patients.size() == 3);          // confim all matches were found
  patients.clear();                      // clear the vector

  query.setName("Christian Singh");      // search for a name we've had problems with
  assert(bst.search(&query, &patients)); // confirm matches were found
  assert(patients.size() == 3);          // confim all matches were found
  patients.clear();                      // clear the vector

  query.setId("christian-2");                         // an id is required to delete a specific node from the bst
  result = bst.remove(&query);                        // remove the matching element and return it
  assert(result && result->getId() == "christian-2"); // make sure the correct item was returned
  query.setId("");                                    // unset the id; we don't need it
  assert(bst.search(&query, &patients));              // confirm matches were found
  assert(patients.size() == 2);                       // confim the record was deleted
  patients.clear();                                   // clear the vector
  delete result;                                      // free the memory

  return 0;
}

void populate_tree(BinarySearchTree<Patient *> &tree)
{
  tree.insert(new Patient("frodo-1", "Frodo Baggins"));
  tree.insert(new Patient("alfrid-1", "Alfrid Lickspittle"));
  tree.insert(new Patient("samwise-1", "Samwise Gamgee"));
  tree.insert(new Patient("samwise-2", "Samwise Gamgee"));
  tree.insert(new Patient("samwise-3", "Samwise Gamgee"));
  tree.insert(new Patient("christian-1", "Christian Singh"));
  tree.insert(new Patient("christian-2", "Christian Singh"));
  tree.insert(new Patient("christian-3", "Christian Singh"));
}