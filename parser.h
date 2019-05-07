#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <iostream>
using namespace std;

class parser
{
private:
  string processor[3455];
  int cycles[3455];
  int readWrite[3455];
  string hex[3455];
  int size = 3455;

private:
  parser();
  ~parser();
  int getSize();
  string getProcessor(int index);
  int getCycle(int index);
  int getReadWrite(int index);
  string getHex(int index);
}
