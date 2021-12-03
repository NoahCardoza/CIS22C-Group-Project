#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <fstream>

#include "Database.h"

using std::string;

class Patient
{
private:
  // columns
  std::string id;   // primary key
  std::string name; // secondary key
  int checkin;
  int checkout;
  char status;
  int age;
  std::string country;
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

  Patient(std::string id, std::string name)
  {
    this->id = id;
    this->name = name;
    checkin = -1;
    checkout = -1;
    status = 0;
    age = -1;
    country = "";
    gender = 0;
  }

  Patient(std::string id, std::string name, int checkin, int checkout, int status, int age, std::string country, int gender)
  {
    this->id = id;
    this->name = name;
    this->checkin = checkin;
    this->checkout = checkout;
    this->status = status;
    this->age = age;
    this->country = country;
    this->gender = gender;
  }

  bool fromStream(std::ifstream *in);
  void toStream(std::ostream *out);

  // setters
  void setId(std::string id) { this->id = id; }
  void setName(std::string name) { this->name = name; }
  void setCheckin(int checkin) { this->checkin = checkin; }
  void setCheckout(int checkout) { this->checkout = checkout; }
  void setStatus(char status) { this->status = status; }
  void setAge(int age) { this->age = age; }
  void setCountry(std::string country) { this->country = country; }
  void setGender(char gender) { this->gender = gender; }

  // getters
  std::string getId() const { return id; }
  std::string getName() const { return name; }
  int getCheckin() const { return checkin; }
  int getCheckout() const { return checkout; }
  char getStatus() const { return status; }
  int getAge() const { return age; }
  std::string getCountry() const { return country; }
  char getGender() const { return gender; }

  // overloaded operators
  bool operator==(const Patient &p) const;
  bool operator!=(const Patient &p) const;
  bool operator<(const Patient &p) const;
  bool operator>(const Patient &p) const;
};

#endif
