#include "CPU.h"

using namespace std;

CPU::CPU()
{
  p0transfers = 0;
  p1transfers = 0;
  p2transfers = 0;
  p3transfers = 0;

  dirtyWrite = 0;

  m = 0;
  o = 0;
  s = 0;
  i = 0;

  for(int i = 0; i < arraySize; i++)
  {
    states[i] = "";
    tag[i] = "";
  }
}

CPU::~CPU()
{

}

void CPU::exclusiveToModified()
{

}

void CPU::exclusiveToInvalid()
{

}

void CPU::exclusiveToShared()
{

}

void CPU::exclusiveToExclusve()
{

}

void CPU::modifiedToOwner()
{

}

void CPU::modifiedToInvalid()
{

}

void CPU::modifiedToModified()
{

}

void CPU::ownerToOwner()
{

}

void CPU::ownerToModifed()
{

}

void CPU::ownerToInvalid()
{

}

void CPU::sharedToShared()
{

}

void CPU::sharedToModified()
{

}

void CPU::sharedToInvalid()
{

}

void CPU::invalidToModified()
{

}

void CPU::invalidToExclusive()
{

}

void CPU::invalidToShared()
{

}

bool CPU::find(string findMe)
{

}

string CPU::stateIn(int index)
{

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
