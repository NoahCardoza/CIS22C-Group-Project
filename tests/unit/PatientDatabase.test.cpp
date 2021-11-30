#include <string>
#include <vector>
#include <assert.h>

#include "../../src/PatientDatabase.h"
#include "../../src/Patient.h"

int main(void)
{
  PatientDatabase db;

  assert(!db.isOpen());                              // db should default to closed
  assert(!db.open("../../data/does-not-exist.csv")); // should refult false if the file doesn't exist
  assert(!db.isOpen());                              // shouldn't be open if the file didn't exist
  assert(db.open("../../data/medium.csv"));          // should return success when files exists
  assert(db.isOpen());                               // should therefore set the db state to open
  assert(!db.open("../../data/small.csv"));          // shoudn't allow another files to be opened while the db is open
  assert(db.size() == 50);                           // make sure all record were loaded

  Patient *result;
  Patient query;

  db.insert(new Patient("ef4da8d3-e9b9-4955-a533-32359607877c", "Phat Anvari")); // test adding a new record
  assert(db.size() == 51);                                                       // make sure the new record was added
  query.setId("ef4da8d3-e9b9-4955-a533-32359607877c");                           // create new query
  assert(db.primarySearch(&query, &result));                                     // search for the newly inserted id
  assert(result->getName() == "Phat Anvari");                                    // verify the name matches
  db.save("pd.test.csv");                                                        // same output to fs to compare

  return 0;
}
