#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Database.h"
#include "Patient.h"

using namespace std;

bool Patient::fromStream(ifstream *in)
{
  // if nothing is read in for the id
  // then something isn't working
  if (!getline(*in, id, ','))
  {
    return false;
  };

  getline(*in, name, ',');
  *in >> checkin;
  in->ignore(1); // consume comma
  *in >> checkout;
  in->ignore(1); // consume comma
  in->get(status);
  in->ignore(1); // consume comma
  *in >> age;
  in->ignore(1); // consume comma
  getline(*in, country, ',');
  in->get(gender);
  in->ignore(1); // consume newline

  return true;
}

void Patient::toStream(ostream *out)
{
  *out << id << ',' << name << ',' << checkin << ',' << checkout << ',' << status << ',' << age << ',' << country << ',' << gender << endl;
}

/**
 * Overloaded Operators
 */

bool Patient::operator==(const Patient &p) const
{
  return name == p.name || id == p.id;
}

bool Patient::operator!=(const Patient &p) const
{
  return name != p.name && id != p.id;
}

bool Patient::operator<(const Patient &p) const
{
  return name < p.name;
}

bool Patient::operator>(const Patient &p) const
{
  return name > p.name;
}
