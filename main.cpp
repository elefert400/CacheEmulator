#include "CPU.h"
#include "CPU.cpp"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//tag 18 bits index 9 bits and the offset has 5
string hexToBinary(string hex)
	{
		string binary = "";
		for (int i = 0; i < hex.length (); ++i)
		{
			switch (sHex [i])
			{
				case '0': sReturn.append ("0000"); break;
				case '1': sReturn.append ("0001"); break;
				case '2': sReturn.append ("0010"); break;
				case '3': sReturn.append ("0011"); break;
				case '4': sReturn.append ("0100"); break;
				case '5': sReturn.append ("0101"); break;
			  case '6': sReturn.append ("0110"); break;
				case '7': sReturn.append ("0111"); break;
				case '8': sReturn.append ("1000"); break;
				case '9': sReturn.append ("1001"); break;
				case 'a': sReturn.append ("1010"); break;
				case 'b': sReturn.append ("1011"); break;
				case 'c': sReturn.append ("1100"); break;
				case 'd': sReturn.append ("1101"); break;
				case 'e': sReturn.append ("1110"); break;
				case 'f': sReturn.append ("1111"); break;
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
    if(binary[i] == "1")
    {
      total = total + pow(2, calcExponent);
    }
  }
  return total;
}
int main()
{
  // all the declarations
  int processor, rw, index;
  string hex;
  Parser* mypars = new parser();
  CPU* p0 = new CPU();
  CPU* p1 = new CPU();
  CPU* p2 = new CPU();
  CPU* p3 = new CPU();
  int parseSize = parser->getSize();

  //main loop for running everything
  for(int i = 0; i < parseSize; i++)
  {
    processor = mypars->getProcessor(i);
    rw = mypars->getReadWrite(i);
    hex = mypars->getHex(i);

    hex = hexToBinary(hex);
    index = getIndex(hex);
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
