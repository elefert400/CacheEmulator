#ifndef CPU_H
#define CPU_H
#include <string>
#include <iostream>
using namespace std;

class CPU
{
private:
  int p0transfers;
  int p1transfers;
  int p2transfers;
  int p3transfers;

  //need question 2 variables

  int dirtyWrite;

  int m;
  int e;
  int o;
  int s;
  int i;

  int invalidM;
  int invalidO;
  int invalidE;
  int invalidS;

  const static int arraySize = 512;
  string states[arraySize];
  string tag[arraySize];

public:
  //constructor destructor
  CPU();
  ~CPU();

  //state change functions
  void exclusiveToModified(int index);
  void exclusiveToInvalid(int index);
  void exclusiveToShared(int index);
  void exclusiveToExclusve(int index);

  void modifiedToOwner(int index);
  void modifiedToInvalid(int index);
  void modifiedToModified(int index);

  void ownerToOwner(int index);
  void ownerToModifed(int index);
  void ownerToInvalid(int index);

  void sharedToShared(int index);
  void sharedToModified(int index);
  void sharedToInvalid(int index);

  void invalidToModified(int index);
  void invalidToExclusive(string newTag, int index);
  void invalidToShared(int index);

  //functions to help get info from the CPU
  bool find(string passedTag, int index);
  string stateIn(int index);

  //functions for incrementing the variables
  void incrementP0();
  void incrementP1();
  void incrementP2();
  void incrementP3();
  void incrementDirtyWriteBack();

  //gets the final variables for output
  int getp0transfers();
  int getp1transfers();
  int getp2transfers();
  int getp3transfers();
  int getDirtyWrite();
  int getm();
  int geti();
  int gete();
  int geto();
  int gets();
  int getInvalidM();
  int getInvalidO();
  int getInvalidE();
  int getInvalidS();
};
#endif
