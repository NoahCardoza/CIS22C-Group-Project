#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Patient.h"

using namespace std;

/**
 * Accepts a stream and fills the interal
 * properties. Basically initiates it's self
 * via a steam.
 * 
 * Returns success status
 */
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

/**
 * Accept a stream and write it's CSV
 * representation to the stream.
 */
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
void Patient::print(void)
{
  cout << "ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Check In: " << checkin << endl;
  cout << "Check Out: " << checkout << endl;
  cout << "Age: " << age << endl;
  cout << "Country: " << country << endl;
  cout << "Gender: " << gender << endl;
}