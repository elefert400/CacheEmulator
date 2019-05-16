//Authors: Kyle Curry and Ethan Lefert

#include "CPU.h"

using namespace std;

//initializing variables and arrays
CPU::CPU()
{
  //variables to keep track of the number of transfers from other processors
  p0transfers = 0;
  p1transfers = 0;
  p2transfers = 0;
  p3transfers = 0;

  //variable to keep track of the number of dirty writes
  dirtyWrite = 0;

  //variable to keep track of final state count in the states array
  m = 0;
  o = 0;
  e = 0;
  s = 0;
  i = 0;

  //variable used to keep track of how many times a state goes to invalid
  invalidM = 0;
  invalidO = 0;
  invalidE = 0;
  invalidS = 0;

  //loop to initialize the states and tag array
  for(int i = 0; i < arraySize; i++)
  {
    states[i] = "Invalid";
    tag[i] = "";
  }
}

CPU::~CPU()
{

}

//changes state from exclusive to modified
void CPU::exclusiveToModified(int index)
{
  states[index] = "Modified";
}

//changes state from exclusive to invalid, increments the invalid counter
void CPU::exclusiveToInvalid(int index)
{
  states[index] = "Invalid";
  invalidE++;
}

//changes state from exclusive to shared
void CPU::exclusiveToShared(int index)
{
  states[index] = "Shared";
}

//handles case where exclusive state stays exclusive
void CPU::exclusiveToExclusve(int index)
{
  states[index] = "Exclusive";
}

//changes state from modified to owner
void CPU::modifiedToOwner(int index)
{
  states[index] = "Owner";
}

//changes state from modified to invalid, increments invalid counter
void CPU::modifiedToInvalid(int index)
{
  states[index] = "Invalid";
  invalidM++;
}

//handles case where modified state stays modified
void CPU::modifiedToModified(int index)
{
  states[index] = "Modified";
}

//handles case where owner state stays owner
void CPU::ownerToOwner(int index)
{
  states[index] = "Owner";
}

//changes owner to modified
void CPU::ownerToModifed(int index)
{
  states[index] = "Modified";
}

//changes owner to invalid, increments invalid counter
void CPU::ownerToInvalid(int index)
{
  states[index] = "Invalid";
  invalidO++;
}

//handles case where shared state stays shared
void CPU::sharedToShared(int index)
{
  states[index] = "Shared";
}

//changes shared to modified
void CPU::sharedToModified(int index)
{
  states[index] = "Modified";
}

//changes shared to invalid
void CPU::sharedToInvalid(int index)
{
  states[index] = "Invalid";
  invalidS++;
}

//changed invalid to modified
void CPU::invalidToModified(int index)
{
  states[index] = "Modified";
}

//changes invalid to exclusive, increments dirty write, and adds new tag to array
void CPU::invalidToExclusive(string newTag, int index)
{
  if(states[index] != "Invalid")
  {
    dirtyWrite++;
  }
  states[index] = "Exclusive";
  tag[index] = newTag;
}

//changes invalid to shared
void CPU::invalidToShared(int index)
{
  states[index] = "Shared";
}

//checks to see if a tag is in the tag array
bool CPU::find(string passedTag, int index)
{
  if(tag[index] == passedTag)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//returns the current state
string CPU::stateIn(int index)
{
  return states[index];
}

//returns the number of transfers from p0
int CPU::getp0transfers()
{
  return p0transfers;
}

//returns the number of transfers from p1
int CPU::getp1transfers()
{
  return p1transfers;
}

//returns the number of transfers from p2
int CPU::getp2transfers()
{
  return p2transfers;
}

//returns the number of transfers from p3
int CPU::getp3transfers()
{
  return p3transfers;
}

//returns the number of dirty writes
int CPU::getDirtyWrite()
{
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Modified" || states[i] == "Owner")
    {
      dirtyWrite++;
    }
  }
  return dirtyWrite;
}

//loops through states array for final modified count
int CPU::getm()
{
  int m = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Modified")
    {
      //dirtyWrite++;
      m++;
    }
  }
  return m;
}

//loops through states array for final invalid count
int CPU::geti()
{
  int i = 0;
  for(int j = 0; j < 512; j++)
  {
    if(states[j] == "Invalid")
    {
      i++;
    }
  }
  return i;
}

//loops through states array for final owner count
int CPU::geto()
{
  int o = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Owner")
    {
      //dirtyWrite++;
      o++;
    }
  }
  return o;
}

//loops through states array for final shared count
int CPU::gets()
{
  int s = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Shared")
    {
      s++;
    }
  }
  return s;
}

//loops through states array for final exclusive count
int CPU::gete()
{
  int e = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Exclusive")
    {
      e++;
    }
  }
  return e;
}

//returns the number of modified to invalid state changes
int CPU::getInvalidM()
{
  return invalidM;
}

//returns the number of owner to invalid states changes
int CPU::getInvalidO()
{
  return invalidO;
}

//returns the number of exclusive to invalid state changes
int CPU::getInvalidE()
{
  return invalidE;
}

//returns the number of shared to invalid state changes
int CPU::getInvalidS()
{
  return invalidS;
}

//increments p0 variable
void CPU::incrementP0()
{
  p0transfers++;
}

//increments p1 variable
void CPU::incrementP1()
{
  p1transfers++;
}

//increments p2 variable
void CPU::incrementP2()
{
  p2transfers++;
}

//increments p3 variable
void CPU::incrementP3()
{
  p3transfers++;
}

//increments dirty writes
void CPU::incrementDirtyWriteBack()
{
  dirtyWrite++;
}
