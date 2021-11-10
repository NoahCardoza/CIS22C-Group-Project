#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Patient.h"
#include "Database.h"

using namespace std;

void Database::import(string filename)
{
  int size = 0;
  s_patient p_record;
  string line;
  vector<Patient *> records;
  ifstream in(filename);

  if (!in)
  {
    // TODO: handle errors better
    exit(1);
  }

  getline(in, line); // read past the CSV header

  while (in.good())
  {
    if (!getline(in, p_record.id, ','))
    {
      continue;
    };
    getline(in, p_record.name, ',');
    in >> p_record.checkin;
    in.ignore(1); // consume comma
    in >> p_record.checkout;
    in.ignore(1); // consume comma
    in.get(p_record.status);
    in.ignore(1); // consume comma
    in >> p_record.age;
    in.ignore(1); // consume comma
    getline(in, p_record.country, ',');
    in.get(p_record.gender);
    in.ignore(1); // consume newline

    Patient *patient = new Patient(&p_record);

    records.push_back(patient);
    size++;
  }

  while (!records.empty())
  {
    Patient *patient = records.back();
    patient->print();
    records.pop_back();
    delete patient;
  }

  cout << size << endl;
}

Database::~Database(void) {}