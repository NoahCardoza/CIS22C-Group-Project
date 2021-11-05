#ifndef DATABASE_H
#define DATABASE_H

#include <string>

using std::string;

class Database
{
private:
  bool opened = false;

public:
  void import(string filename);
  void open(string filename);
  void save(string filename);

  ~Database();
};

#endif
