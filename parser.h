#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
using namespace std;

class Parser
{
private:
  //declaring arrays to keep track of data from traces
  int processor[3456];
  int cycles[3456];
  int readWrite[3456];
  string hex[3456];

  //variable to keep track of number of items in each array
  int size;

public:
  //construct and destructor
  Parser();
  ~Parser();

  //functions to swap values in arrays for sorting
  void intSwap(int* x, int* y);
  void stringSwap(string* x, string* y);

  //sorting function
  void arraySort();

  //parsing functions to read in trace values
  void parseP0();
  void parseP1();
  void parseP2();
  void parseP3();

  //functions to return values from each array, or get current number of items
  int getSize();
  int getProcessor(int index);
  int getCycle(int index);
  int getReadWrite(int index);
  string getHex(int index);
};

#endif
