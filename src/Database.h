#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include "Patient.h"

using std::string;

class Database
{
private:
  bool opened = false;
  std::vector<Patient *> records;

public:
  bool open(string filename);
  bool save(string filename);

  ~Database();
};

#endif
