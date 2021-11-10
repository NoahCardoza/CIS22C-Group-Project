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

  Patient *record = new Patient();

  in.ignore(127, '\n'); // read past the CSV header

  while (in.good())
  {
    if (record->fromStream(&in))
    {
      records.push_back(record);
      record = new Patient();
    }
  }

  // delete the left over empty Patient
  delete record;

  opened = true;

  return true;
}

bool Database::save(string filename)
{
  if (!opened)
  {
    // we can't save a database that hasn't been opened
    return false;
  }

  ofstream out(filename);

  // TODO: figure out how to make this more modular
  out << "id,name,checkin date,checkout date,status,age,country code,gender" << endl;

  // TODO: iterate the HashTable to write
  // in the same order
  for (auto const &record : records)
  {
    record->toStream(&out);
  }

  out.close();

  return true;
}

Database::~Database(void)
{
  Patient *patient;

  while (!records.empty())
  {
    patient = records.back();
    records.pop_back();
    delete patient;
  }
}