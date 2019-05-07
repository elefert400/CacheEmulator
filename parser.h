#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
using namespace std;

class Parser
{
private:
  int processor[3456];
  int cycles[3456];
  int readWrite[3456];
  string hex[3456];
  int size;

public:
  Parser();
  ~Parser();
  void intSwap(int* x, int* y);
  void stringSwap(string* x, string* y);
  void arraySort();
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
