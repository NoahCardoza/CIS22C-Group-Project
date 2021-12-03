/**
 * @author Noah Cardoza
 * @file PatientDatabase.h
 * Section: 5
 * 
 * I tried to make this project as modular as possible.
 * The Database is an ADT for this reason. If the header
 * of the CSV file should change, you must subclass it 
 * differently and update the getHeader method which I did
 * here.
 */

#ifndef PATIENT_DATABASE_H
#define PATIENT_DATABASE_H

#include <string>

#include "Database.h"
#include "Patient.h"

using std::string;

class PatientDatabase : public Database<Patient>
{
private:
  std::string getHeader()
  {
    return "id,name,checkin date,checkout date,status,age,country code,gender";
  }
};

#endif
