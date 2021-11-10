#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Database.h"

using std::string;

class Patient
{
private:
  // columns
  string id;
  string name;
  int checkin;
  int checkout;
  char status;
  int age;
  string country;
  char gender;

public:
  Patient()
  {
    id = "";
    name = "";
    checkin = -1;
    checkout = -1;
    status = 0;
    age = -1;
    country = "";
    gender = 0;
  }

  bool fromStream(std::ifstream *in);
  void toStream(std::ostream *out);
  int hash(int);
  void print(void);

  // getters
  void setId(string id) { this->id = id; }
  void setName(string name) { this->name = name; }
  void setCheckin(int checkin) { this->checkin = checkin; }
  void setCheckout(int checkout) { this->checkout = checkout; }
  void setStatus(char status) { this->status = status; }
  void setAge(int age) { this->age = age; }
  void setCountry(string country) { this->country = country; }
  void setGender(char gender) { this->gender = gender; }
  static string getHeader()
  {
    return "id,name,checkin date,checkout date,status,age,country code,gender";
  };

  // setters
  string getId() { return id; }
  string getName() { return name; }
  int getCheckin() { return checkin; }
  int getCheckout() { return checkout; }
  char getStatus() { return status; }
  int getAge() { return age; }
  string getCountry() { return country; }
  char getGender() { return gender; }

  // overloaded operators
  bool operator==(const Patient &p);
  bool operator<(const Patient &p);
  bool operator>(const Patient &p);
};

#endif
