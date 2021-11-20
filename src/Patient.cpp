#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Database.h"
#include "Patient.h"

using namespace std;

int Patient::hash(int size)
{
  // TODO: implement this function
  return size;
}

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
 * Print out all the properties of the
 * class.
 *
 * TODO: remove in final version.
 */
void Patient::print(void) const
{
  cout << "ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Check In: " << checkin << endl;
  cout << "Check Out: " << checkout << endl;
  cout << "Age: " << age << endl;
  cout << "Country: " << country << endl;
  cout << "Gender: " << gender << endl;
}

/**
 * Overloaded Operators
 */

bool Patient::operator==(const Patient &p)
{
  return name == p.name;
}

bool Patient::operator<(const Patient &p)
{
  return name < p.name;
}

bool Patient::operator>(const Patient &p)
{
  return name > p.name;
}
