#include "parser.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Parser::Parser()
{
  //initializing item count in arrays
  size = 0;

  //populating arrays
  parseP0();
  parseP1();
  parseP2();
  parseP3();

  //sorting arrays based on cycle, then processor
  arraySort();
}

Parser::~Parser()
{

}

void Parser::intSwap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Parser::stringSwap(string* x, string* y)
{
  string temp = *x;
  *x = *y;
  *y = temp;
}

void Parser::arraySort()
{
    int i, j, minIndex;

    //one by one move boundary of unsorted subarray
    for (i = 0; i < size - 1; i++)
    {
        //find the minimum element in the cycles array
        minIndex = i;
        for (j = i + 1; j < size; j++)
        {
          if (cycles[j] < cycles[minIndex])
          {
            minIndex = j;
          }
          else if(cycles[j] == cycles[minIndex])
          {
            if(processor[j] < processor[minIndex])
            {
              minIndex = j;
            }
          }
        }

        //swap minimum element with the first element of array
        intSwap(&processor[minIndex], &processor[i]);
        intSwap(&cycles[minIndex], &cycles[i]);
        intSwap(&readWrite[minIndex], &readWrite[i]);
        stringSwap(&hex[minIndex], &hex[i]);
    }
}

//reads data from p0.txt and populates arrays
void Parser::parseP0()
{
  //creating variables for storing data
  int cycle, rw;
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

//reads data from p1.txt and populates arrays
void Parser::parseP1()
{
  //creating variables for storing data
  int cycle, rw;
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

//reads data from p2.txt and populates arrays
void Parser::parseP2()
{
  //creating variables for storing data
  int cycle, rw;
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

//reads data from p3.txt and populates arrays
void Parser::parseP3()
{
  //creating variables for storing data
  int cycle, rw;
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

int Parser::getSize()
{
  return size;
}

int Parser::getProcessor(int index)
{
  return processor[index];
}

int Parser::getCycle(int index)
{
  return cycles[index];
}

int Parser::getReadWrite(int index)
{
  return readWrite[index];
}

string Parser::getHex(int index)
{
  return hex[index];
}
