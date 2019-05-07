#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <iostream>
using namespace std;

class Parser
{
private:
  string processor[3455];
  int cycles[3455];
  int readWrite[3455];
  string hex[3455];
  int size;

private:
  parser();
  ~parser();
  void parseP0();
  void parseP1();
  void parseP2();
  void parseP3();
  int getSize();
  string getProcessor(int index);
  int getCycle(int index);
  int getReadWrite(int index);
  string getHex(int index);
}
