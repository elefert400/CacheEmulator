#include "CPU.h"
#include <iostream>
#include <fstream>
using namspace std;

//variables for
int cycle, readWrite;
string address;
ifstream input;
//opening file
input.open("p0.txt");
//making sure the file opened properly
if(!input.is_open())
{
  cout << "Could not open file." << endl;
  exit(1);
}
//read from file
while(input >> cycle >> readWrite >> address)
{

}
//closing file
input.close();
