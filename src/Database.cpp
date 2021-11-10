#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "Patient.h"
#include "Database.h"

using namespace std;

bool Database::open(string filename)
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

  Patient *patient = new Patient();

  in.ignore(127, '\n'); // read past the CSV header

  while (in.good())
  {
    if (patient->fromStream(&in))
    {
      records.push_back(patient);
      patient = new Patient();
    }
  }

  // delete the left over empty Patient
  delete patient;

  opened = true;

  return true;
}

Database::~Database(void)
{
}