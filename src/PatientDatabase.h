#ifndef PATIENT_DATABASE_H
#define PATIENT_DATABASE_H

#include <string>

#include "Database.h"
#include "Patient.h"

using std::string;

class PatientDatabase : public Database<Patient>
{
private:
  string getHeader()
  {
    return "id,name,checkin date,checkout date,status,age,country code,gender";
  }
};

#endif
