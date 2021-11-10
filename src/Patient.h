#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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

  bool fromStream(std::ifstream *in)
  {
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

  void print(void)
  {
    // TODO: remove this function, only for debugging
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Check In: " << checkin << std::endl;
    std::cout << "Check Out: " << checkout << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Gender: " << gender << std::endl;
  }

  // getters
  void setId(string id) { this->id = id; }
  void setName(string name) { this->name = name; }
  void setCheckin(int checkin) { this->checkin = checkin; }
  void setCheckout(int checkout) { this->checkout = checkout; }
  void setStatus(char status) { this->status = status; }
  void setAge(int age) { this->age = age; }
  void setCountry(string country) { this->country = country; }
  void setGender(char gender) { this->gender = gender; }

  // setters
  string getId() { return id; }
  string getName() { return name; }
  int getCheckin() { return checkin; }
  int getCheckout() { return checkout; }
  char getStatus() { return status; }
  int getAge() { return age; }
  string getCountry() { return country; }
  char getGender() { return gender; }
};

#endif
