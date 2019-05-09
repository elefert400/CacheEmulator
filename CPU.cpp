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
  return m;
}

int CPU::geti()
{
  return i;
}

int CPU::geto()
{
  return o;
}

int CPU::gets()
{
  return s;
}

int CPU::gete()
{
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
