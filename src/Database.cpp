#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Database.h"

using namespace std;

struct s_record
{
  string id;
  string name;
  int checkin;
  int checkout;
  char status;
  int age;
  char country[3] = "\0\0";
  char gender;
};

void Database::import(string filename)
{
  int size = 0;
  s_record record;
  string line;
  vector<s_record> lines;
  ifstream in(filename);
  char char_buf;

  if (!in)
  {
    // TODO: handle errors better
    exit(1);
  }

  getline(in, line); // read past the CSV header

  while (in.good())
  {
    if (!getline(in, record.id, ','))
    {
      continue;
    };
    getline(in, record.name, ',');
    in >> record.checkin;
    in.get(char_buf); // consume comma
    in >> record.checkout;
    in.get(char_buf); // consume comma
    in.get(record.status);
    in.get(char_buf); // consume comma
    in >> record.age;
    in.get(char_buf); // consume comma
    in.read(record.country, 2);
    in.get(char_buf); // consume comma
    in.get(record.gender);
    in.get(char_buf); // consume newline

    cout << "ID: " << record.id << endl;
    cout << "Name: " << record.name << endl;
    cout << "Check In: " << record.checkin << endl;
    cout << "Check Out: " << record.checkout << endl;
    cout << "Age: " << record.age << endl;
    cout << "Country: " << record.country << endl;
    cout << "Gender: " << record.gender << endl;

    lines.push_back(record);
    size++;
  }

  cout << size << endl;
}

Database::~Database(void) {}