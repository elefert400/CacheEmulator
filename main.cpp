#include "CPU.h"
#include "CPU.cpp"
#include "parser.h"
#include "parser.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
//tag 18 bits index 9 bits and the offset has 5
string hexToBinary(string hex)
	{
		string binary = "";
		for (int i = 2; i < hex.length (); ++i)
		{
			switch (hex [i])
			{
				case '0': binary.append ("0000"); break;
				case '1': binary.append ("0001"); break;
				case '2': binary.append ("0010"); break;
				case '3': binary.append ("0011"); break;
				case '4': binary.append ("0100"); break;
				case '5': binary.append ("0101"); break;
			  case '6': binary.append ("0110"); break;
				case '7': binary.append ("0111"); break;
				case '8': binary.append ("1000"); break;
				case '9': binary.append ("1001"); break;
				case 'a': binary.append ("1010"); break;
				case 'b': binary.append ("1011"); break;
				case 'c': binary.append ("1100"); break;
				case 'd': binary.append ("1101"); break;
				case 'e': binary.append ("1110"); break;
				case 'f': binary.append ("1111"); break;
			}
		}
		return binary;
	}

int getIndex(string binary)
{
  int total = 0;
  int exponent = 5;
  int calcExponent;
  for(int i = 5; i < 14; i++)
  {
    calcExponent = i - exponent;
    if(&binary[i] == "1")
    {
      total = total + pow(2, calcExponent);
    }
  }
  return total;
}

string getTag(string binary)
{
  string tag;
  int tracker = 0;
  for(int i = 14; i < 32; i++)
  {
    tag[tracker] = binary[i];
    tracker++;
  }
  return tag;
}

int main()
{
  // all the declarations
  int processor, rw, index;
  string hex, tag;
  Parser* mypars = new Parser();
  CPU* p0 = new CPU();
  CPU* p1 = new CPU();
  CPU* p2 = new CPU();
  CPU* p3 = new CPU();
  int parseSize = mypars->getSize();

  //main loop for running everything
  for(int i = 0; i < parseSize; i++)
  {
    processor = mypars->getProcessor(i);
    rw = mypars->getReadWrite(i);
    hex = mypars->getHex(i);

    hex = hexToBinary(hex);
    index = getIndex(hex);
    tag = getTag(hex);
    /*
    READS
    check if the processor has the data if it does do nothing
    otherwise check if other processors have it
    if they do modify states as needed and transfer data
    else read from memory
    */
    /*
    WRITES
    update all other processors to invalidate their copies if it exists
    ?? write back to memory
    */
    //read
    if(rw == 0)
    {
      if(processor == 0)
      {

      }//checking processor 0
      if(processor == 1)
      {

      }//checking processor 1
      if(processor == 2)
      {

      }//checking processor 2
      if(processor == 3)
      {

      }//checking processor 3
    }//end read
    //write
    if(rw == 1)
    {
      if(processor == 0)
      {

      }//checking processor 0
      if(processor == 1)
      {

      }//checking processor 1
      if(processor == 2)
      {

      }//checking processor 2
      if(processor == 3)
      {

      }//checking processor 3
    }//end write
  }//end main loop

  //garabage collection
  delete mypars;
  delete p0;
  delete p1;
  delete p2;
  delete p3;
}
