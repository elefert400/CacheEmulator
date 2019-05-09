#include "CPU.h"

using namespace std;

//initializing variables and arrays
CPU::CPU()
{
  p0transfers = 0;
  p1transfers = 0;
  p2transfers = 0;
  p3transfers = 0;

  dirtyWrite = 0;

  m = 0;
  o = 0;
  e = 0;
  s = 0;
  i = 0;
  //need to make function to go through state array at end and keep track of how many are present of each state



  invalidM = 0;
  invalidO = 0;
  invalidE = 0;
  invalidS = 0;

  for(int i = 0; i < arraySize; i++)
  {
    states[i] = "Invalid";
    tag[i] = "";
  }
}

CPU::~CPU()
{

}

void CPU::exclusiveToModified(int index)
{
  states[index] = "Modified";
}

void CPU::exclusiveToInvalid(int index)
{
  states[index] = "Invalid";
  invalidE++;
}

void CPU::exclusiveToShared(int index)
{
  states[index] = "Shared";
}

void CPU::exclusiveToExclusve(int index)
{
  states[index] = "Exclusive";
}

void CPU::modifiedToOwner(int index)
{
  states[index] = "Owner";
}

void CPU::modifiedToInvalid(int index)
{
  states[index] = "Invalid";
  invalidM++;
}
//
void CPU::modifiedToModified(int index)
{
  states[index] = "Modified";
}

void CPU::ownerToOwner(int index)
{
  states[index] = "Owner";
}

void CPU::ownerToModifed(int index)
{
  states[index] = "Modified";
}

void CPU::ownerToInvalid(int index)
{
  states[index] = "Invalid";
  invalidO++;
}

void CPU::sharedToShared(int index)
{
  states[index] = "Shared";
}

void CPU::sharedToModified(int index)
{
  states[index] = "Modified";
}

void CPU::sharedToInvalid(int index)
{
  states[index] = "Invalid";
  invalidS++;
}

void CPU::invalidToModified(int index)
{
  states[index] = "Modified";
}

void CPU::invalidToExclusive(string newTag, int index)
{
  states[index] = "Exclusive";
  tag[index] = newTag;
}

void CPU::invalidToShared(int index)
{
  states[index] = "Shared";
}

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

string CPU::stateIn(int index)
{
  return states[index];
}

int CPU::getp0transfers()
{
  return p0transfers;
}

int CPU::getp1transfers()
{
  return p1transfers;
}

int CPU::getp2transfers()
{
  return p2transfers;
}

int CPU::getp3transfers()
{
  return p3transfers;
}

int CPU::getDirtyWrite()
{
  return dirtyWrite;
}

int CPU::getm()
{
  int m = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Modified")
    {
      m++;
    }
  }
  return m;
}

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

int CPU::geto()
{
  int o = 0;
  for(int i = 0; i < 512; i++)
  {
    if(states[i] == "Owner")
    {
      o++;
    }
  }
  return o;
}

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

int CPU::getInvalidM()
{
  return invalidM;
}

int CPU::getInvalidO()
{
  return invalidO;
}

int CPU::getInvalidE()
{
  return invalidE;
}

int CPU::getInvalidS()
{
  return invalidS;
}

void CPU::incrementP0()
{
  p0transfers++;
}

void CPU::incrementP1()
{
  p1transfers++;
}

void CPU::incrementP2()
{
  p2transfers++;
}

void CPU::incrementP3()
{
  p3transfers++;
}

void CPU::incrementDirtyWriteBack()
{
  dirtyWrite++;
}


/*
//expected output for project
//total number of cache to cache transfers for each processor pair
cout << endl << endl;
cout << "The total number of cache-to-cache transfers for each processor pair in the following format." << endl;
cout << "P0 cache transfers: <p0-p1> = " << p0->getp1transfers() << ", <p0-p2> = " << p0->getp2transfers() << ", <p0-p3> = " << p0->getp3transfers() << endl;
cout << "P1 cache transfers: <p1-p0> = " << p1->getp0transfers() << ", <p1-p2> = " << p1->getp2transfers() << ", <p1-p3> = " << p1->getp3transfers() << endl;
cout << "P2 cache transfers: <p2-p0> = " << p2->getp0transfers() << ", <p2-p1> = " << p2->getp1transfers() << ", <p2-p3> = " << p2->getp3transfers() << endl;
cout << "P3 cache transfers: <p3-p0> = " << p3->getp0transfers() << ", <p3-p1> = " << p3->getp1transfers() << ", <p3-p2> = " << p3->getp2transfers() << endl << endl;

//total number of invalidations due to coherence in each processor
cout << "The total number of invalidations due to coherence (i.e. not including line replacement) in each processor in the following format." << endl;
cout << "P0 Invalidation from: m = " << p0->getInvalidM() << ", o = " << p0->getInvalidO() << ", e = " << p0->getInvalidE() << ", s = " << p0->getInvalidS() << endl;
cout << "P1 Invalidation from: m = " << p1->getInvalidM() << ", o = " << p1->getInvalidO() << ", e = " << p1->getInvalidE() << ", s = " << p1->getInvalidS() << endl;
cout << "P2 Invalidation from: m = " << p2->getInvalidM() << ", o = " << p2->getInvalidO() << ", e = " << p2->getInvalidE() << ", s = " << p2->getInvalidS() << endl;
cout << "P3 Invalidation from: m = " << p3->getInvalidM() << ", o = " << p3->getInvalidO() << ", e = " << p3->getInvalidE() << ", s = " << p3->getInvalidS() << endl << endl;

//total number of dirty writebacks for each processor
cout << "The number of dirty writebacks from each processor." << endl;
cout << "P0 = " << p0->getDirtyWrite() << ", P1 = " << p1->getDirtyWrite() << ", P2 = " << p2->getDirtyWrite() << ", P3 = " << p3->getDirtyWrite() << endl << endl;

//number of lines in each state at the end  of the simulation for each processor
cout << "The number of lines in each state at the end the simulation for each processor." << endl;
cout << "P0: m = " << p0->getm() << ", o = " << p0->geto() << ", e = " << p0->gete() << ", s = " << p0->gets() << ", i = " << p0->geti() << endl;
cout << "P1: m = " << p1->getm() << ", o = " << p1->geto() << ", e = " << p1->gete() << ", s = " << p1->gets() << ", i = " << p1->geti() << endl;
cout << "P2: m = " << p2->getm() << ", o = " << p2->geto() << ", e = " << p2->gete() << ", s = " << p2->gets() << ", i = " << p2->geti() << endl;
cout << "P3: m = " << p3->getm() << ", o = " << p3->geto() << ", e = " << p3->gete() << ", s = " << p3->gets() << ", i = " << p3->geti() << endl << endl;

*/
