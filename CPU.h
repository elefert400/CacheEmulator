#idndef CPU_H
#define CPU_H

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
  int o;
  int s;
  int i;

  int arraySize = 512;
  string states[arraySize];
  string tag[arraySize];
public:
  //constructor destructor
  CPU();
  ~CPU();
  //state change functions
  void exclusiveToModified();
  void exclusiveToInvalid();
  void exclusiveToShared();
  void exclusiveToExclusve();

  void modifiedToOwner();
  void modifiedToInvalid();
  void modifiedToModified();

  void ownerToOwner();
  void ownerToModifed();
  void ownerToInvalid();

  void sharedToShared();
  void sharedToModified();
  void sharedToInvalid();

  void invalidToModified();
  void invalidToExclusive();
  void invalidToShared();

  //functions to help get info from the CPU
  bool find(string findMe);
  string stateIn(int index);
  void addToArray(string newString);
  int findIndex(string findMe);

  //gets the final variables for output
  int getp0transfers();
  int getp1transfers();
  int getp2transfers();
  int getp3transfers();
  int getDirtyWrite();
  int getm();
  int geti();
  int geto();
  int gets();
};
#endif
