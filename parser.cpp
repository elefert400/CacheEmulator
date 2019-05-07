#include "parser.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Parser::parser()
{
  //initializing item count in arrays
  size = 0;

  //populating arrays
  parseP0();
  parseP1();
  parseP2();
  parseP3();
}

void Parser::parseP0()
{
  //creating variables for storing data
  int processor, cycle, rw;
  string address;
  ifstream p0;

  //opening  file
  p0.open("p0.txt");

  //making sure the  file opened properly
  if(!p0.is_open())
  {
    cout << "Could not open file." << endl;
    exit(1);
  }

  //read from file
  while(p0 >> cycle >> rw >> address)
  {
    processor[size] = 0;
    cycles[size] = cycle;
    readWrite[size] = rw;
    hex[size] = address;
    size++;
  }

  //closing  file
  p0.close();
}

void Parser::parseP1()
{
  //creating variables for storing data
  int processor, cycle, rw;
  string address;
  ifstream p1;

  //opening  file
  p1.open("p1.txt");

  //making sure the  file opened properly
  if(!p1.is_open())
  {
    cout << "Could not open file." << endl;
    exit(1);
  }

  //read from file
  while(p1 >> cycle >> rw >> address)
  {
    processor[size] = 1;
    cycles[size] = cycle;
    readWrite[size] = rw;
    hex[size] = address;
    size++;
  }

  //closing  file
  p1.close();
}

void Parser::parseP2()
{
  //creating variables for storing data
  int processor, cycle, rw;
  string address;
  ifstream p2;

  //opening  file
  p2.open("p2.txt");

  //making sure the  file opened properly
  if(!p2.is_open())
  {
    cout << "Could not open file." << endl;
    exit(1);
  }

  //read from file
  while(p2 >> cycle >> rw >> address)
  {
    processor[size] = 2;
    cycles[size] = cycle;
    readWrite[size] = rw;
    hex[size] = address;
    size++;
  }

  //closing  file
  p2.close();
}

void Parser::parseP3()
{
  //creating variables for storing data
  int processor, cycle, rw;
  string address;
  ifstream p3;

  //opening  file
  p3.open("p3.txt");

  //making sure the file opened properly
  if(!p3.is_open())
  {
    cout << "Could not open file." << endl;
    exit(1);
  }

  //read from file
  while(p3 >> cycle >> rw >> address)
  {
    processor[size] = 3;
    cycles[size] = cycle;
    readWrite[size] = rw;
    hex[size] = address;
    size++;
  }

  //closing file
  p3.close();
}
