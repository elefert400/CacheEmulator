#include "CPU.h"
#include "CPU.cpp"
#include <iostream>
using namespace std;

int main()
{
  int clockCycle = 0;
  //variables for file input
  int p0Cycle, p1Cycle, p2Cycle, p3Cycle;
  int p0ReadWrite, p1ReadWrite, p2ReadWrite, p3ReadWrite;
  string p0Address, p1Address, p2Address, p3Address;
  ifstream p0, p1, p2, p3;
  //opening file
  p0.open("p0.txt");
  p1.open("p1.txt");
  p2.open("p2.txt");
  p3.open("p3.txt");
  //making sure the file opened properly
  if(!p0.is_open() || !p1.is_open() || !p2.is_open() || !p3.is_open())
  {
    cout << "Could not open file." << endl;
    exit(1);
  }
  //read from file
  while(p0 >> p0Cycle >> p0ReadWrite >> p0Address)
  {

    clockCycle++;
  }
  //closing file
  input.close();
}
