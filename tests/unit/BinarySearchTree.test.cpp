#include <string>
#include <vector>
#include <assert.h>

#include "../../src/BinarySearchTree.h"
#include "../../src/Patient.h"

void populate_tree(BinarySearchTree<Patient *> &tree);

template <class T>
class BinarySearchTreeTester : public BinarySearchTree<T>
{
public:
  void test_deleteing_root_node()
  {
    Patient query("frodo-1", "Frodo Baggins");
    Patient *result;
    result = this->remove(&query);

    assert(result->getId() == "frodo-1");
  }
};

int main(void)
{
  BinarySearchTreeTester<Patient *> bst;
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

  bst.test_deleteing_root_node();

  // confirm left side of the rotated node are still accessable after deleteing root
  query.setName("George");               // an id is required to delete a specific node from the bst
  assert(bst.search(&query, &patients)); // confirm matches were found
  assert(patients.size() == 1);          // confim the record was deleted
  patients.clear();                      // clear the vector
  query.setName("Hector");               // an id is required to delete a specific node from the bst
  assert(bst.search(&query, &patients)); // confirm matches were found
  assert(patients.size() == 1);          // confim the record was deleted
  patients.clear();                      // clear the vector

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
  tree.insert(new Patient("george-1", "George"));
  tree.insert(new Patient("hector-1", "Hector"));
}