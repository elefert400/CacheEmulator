#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
using namespace std;

class Parser
{
private:
  int processor[3455];
  int cycles[3455];
  int readWrite[3455];
  string hex[3455];
  int size;

public:
  Parser();
  ~Parser();
  void parseP0();
  void parseP1();
  void parseP2();
  void parseP3();
  int getSize();
  int getProcessor(int index);
  int getCycle(int index);
  int getReadWrite(int index);
  string getHex(int index);
};

#endif
