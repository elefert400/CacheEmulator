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
  string str;
  int total = 0;
  int exponent = 6;
  int calcExponent;
  for(int i = 6; i < 15; i++)
  {
    calcExponent = i - exponent;
    str = binary[32 - i];
    if(str[0] == '1')
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
  string hex, bin, state;
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

    bin = hexToBinary(hex);
    index = getIndex(bin);
    //tag = getTag(bin);
		char tag[18];
		std::size_t length = bin.copy(tag,18,0);
		tag[length]='\0';
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
				if(p0->find(tag, index) == true && p0->stateIn(index) != "Invalid")
				{
					//we have the data we are trying to read and it is valid, do nothing
				}
				//p1 has a valid form of the data
				else if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p1->stateIn(index);

					if(state == "Exclusive")
					{
						p1->exclusiveToShared(index);
						//increment p1 shared
						p1->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p1->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared
						p1->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p1->incrementP0();
						p0->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusiveToShared(index);
						//increment p2 shared
						p2->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p2->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p2->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
						p2->incrementP0();
						p0->invalidToShared(index);
					}
				}//end p2 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusiveToShared(index);
						//increment p3 shared
						p3->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p3->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p3->incrementP0();
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
						p3->incrementP0();
						p0->invalidToShared(index);
					}
				}//end p3 look up
				else
				{
					//update the tag array with the new tag and set it to the exclusive state
					p0->invalidToExclusive(tag, index);
				}//end base case to pull from memory
      }//checking processor 0
      if(processor == 1)
      {
				if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//we have the data we are trying to read and it is valid, do nothing
				}
				//p0 has a valid form of the data
				else if(p0->find(tag, index) == true && p0->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p0->stateIn(index);

					if(state == "Exclusive")
					{
						p0->exclusiveToShared(index);
						//increment p1 shared
						p0->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p0->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p1 shared
						p0->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p0->incrementP1();
						p1->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusiveToShared(index);
						//increment p2 shared
						p2->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p2->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p2->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
						p2->incrementP1();
						p1->invalidToShared(index);
					}
				}//end p2 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusiveToShared(index);
						//increment p3 shared
						p3->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p3->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p3->incrementP1();
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
						p3->incrementP1();
						p1->invalidToShared(index);
					}
				}//end p3 look up
				else
				{
					//update the tag array with the new tag and set it to the exclusive state
					p1->invalidToExclusive(tag, index);
				}//end base case to pull from memory
      }//checking processor 1
      if(processor == 2)
      {
				if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//we have the data we are trying to read and it is valid, do nothing
				}
				//p0 has a valid form of the data
				else if(p0->find(tag, index) == true && p0->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p0->stateIn(index);

					if(state == "Exclusive")
					{
						p0->exclusiveToShared(index);
						//increment p0 shared
						p0->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p0 shared
						p0->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p0 shared
						p0->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p0 shared
						p0->incrementP2();
						p2->invalidToShared(index);
					}
				}//end p0 look up
				else if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p1->stateIn(index);

					if(state == "Exclusive")
					{
						p1->exclusiveToShared(index);
						//increment p1 shared
						p1->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p1->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared
						p1->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p1->incrementP2();
						p2->invalidToShared(index);
					}
				}//end p1 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusiveToShared(index);
						//increment p3 shared
						p3->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p3->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p3->incrementP2();
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
						p3->incrementP2();
						p2->invalidToShared(index);
					}
				}//end p3 look up
				else
				{
					//update the tag array with the new tag and set it to the exclusive state
					p2->invalidToExclusive(tag, index);
				}//end base case to pull from memory
      }//checking processor 2
      if(processor == 3)
      {
				if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//we have the data we are trying to read and it is valid, do nothing
				}
				//p0 has a valid form of the data
				else if(p0->find(tag, index) == true && p0->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p0->stateIn(index);

					if(state == "Exclusive")
					{
						p0->exclusiveToShared(index);
						//increment p0 shared
						p0->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p0 shared
						p0->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p0 shared
						p0->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p0 shared
						p0->incrementP3();
						p3->invalidToShared(index);
					}
				}//end p0 look up
				else if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p1->stateIn(index);

					if(state == "Exclusive")
					{
						p1->exclusiveToShared(index);
						//increment p1 shared
						p1->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p1->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared.
						p1->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p1->incrementP3();
						p3->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusiveToShared(index);
						//increment p2 shared
						p2->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p2->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p2->incrementP3();
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
						p2->incrementP3();
						p3->invalidToShared(index);
					}
				}//end p3 look up
				else
				{
					//update the tag array with the new tag and set it to the exclusive state
					p3->invalidToExclusive(tag, index);
				}//end base case to pull from memory
      }//checking processor 3
    }//end read
    //write
    if(rw == 1)
    {
      if(processor == 0)
      {
				state = p0->stateIn(index);
				if(state == "Invalid")
				{
					p0->invalidToModified(index);

					//checking to see if anyone does a dirty write back
					if(p1->stateIn(index) == "Owner" || p1->stateIn(index) == "Modified")
					{
						p1->incrementDirtyWriteBack();
					}
					if(p2->stateIn(index) == "Owner" || p2->stateIn(index) == "Modified")
					{
						p2->incrementDirtyWriteBack();
					}
					if(p3->stateIn(index) == "Owner" || p3->stateIn(index) == "Modified")
					{
						p3->incrementDirtyWriteBack();
					}

					//everyone goes to invalid now
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Shared")
				{
					p0->sharedToModified(index);

					//invalidate everyone without sending back to DRAM
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Owner")
				{
					p0->ownerToModifed(index);

					//just invalidating everyone
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Modified")
				{
					//don't need to do anything because we are modifing data we already have to latest data of
				}
				else if(state == "Exclusive")
				{
					//don't need to do anything because we are the only ones with the data
					p0->exclusiveToModified(index);
				}
      }//checking processor 0
      if(processor == 1)
      {
				state = p1->stateIn(index);
				if(state == "Invalid")
				{
					p1->invalidToModified(index);

					//checking to see if anyone does a dirty write back
					if(p0->stateIn(index) == "Owner" || p0->stateIn(index) == "Modified")
					{
						p0->incrementDirtyWriteBack();
					}
					if(p2->stateIn(index) == "Owner" || p2->stateIn(index) == "Modified")
					{
						p2->incrementDirtyWriteBack();
					}
					if(p3->stateIn(index) == "Owner" || p3->stateIn(index) == "Modified")
					{
						p3->incrementDirtyWriteBack();
					}

					//everyone goes to invalid now
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Shared")
				{
					p1->sharedToModified(index);

					//invalidate everyone without sending back to DRAM
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Owner")
				{
					p1->ownerToModifed(index);

					//just invalidating everyone
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Modified")
				{
					//don't need to do anything because we are modifing data we already have to latest data of
				}
				else if(state == "Exclusive")
				{
					//don't need to do anything because we are the only ones with the data
					p1->exclusiveToModified(index);
				}
      }//checking processor 1
      if(processor == 2)
      {
				state = p2->stateIn(index);
				if(state == "Invalid")
				{
					p2->invalidToModified(index);

					//checking to see if anyone does a dirty write back
					if(p1->stateIn(index) == "Owner" || p1->stateIn(index) == "Modified")
					{
						p1->incrementDirtyWriteBack();
					}
					if(p0->stateIn(index) == "Owner" || p2->stateIn(index) == "Modified")
					{
						p0->incrementDirtyWriteBack();
					}
					if(p3->stateIn(index) == "Owner" || p3->stateIn(index) == "Modified")
					{
						p3->incrementDirtyWriteBack();
					}

					//everyone goes to invalid now
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Shared")
				{
					p2->sharedToModified(index);

					//invalidate everyone without sending back to DRAM
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Owner")
				{
					p2->ownerToModifed(index);

					//just invalidating everyone
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
					if(p3->stateIn(index) == "Exclusive")
					{
						p3->exclusiveToInvalid(index);
					}
					if(p3->stateIn(index) == "Modified")
					{
						p3->modifiedToInvalid(index);
					}
					if(p3->stateIn(index) == "Owner")
					{
						p3->ownerToModifed(index);
					}
					if(p3->stateIn(index) == "Shared")
					{
						p3->sharedToInvalid(index);
					}
				}
				else if(state == "Modified")
				{
					//don't need to do anything because we are modifing data we already have to latest data of
				}
				else if(state == "Exclusive")
				{
					//don't need to do anything because we are the only ones with the data
					p2->exclusiveToModified(index);
				}
      }//checking processor 2
      if(processor == 3)
      {
				state = p3->stateIn(index);
				if(state == "Invalid")
				{
					p3->invalidToModified(index);

					//checking to see if anyone does a dirty write back
					if(p1->stateIn(index) == "Owner" || p1->stateIn(index) == "Modified")
					{
						p1->incrementDirtyWriteBack();
					}
					if(p2->stateIn(index) == "Owner" || p2->stateIn(index) == "Modified")
					{
						p2->incrementDirtyWriteBack();
					}
					if(p0->stateIn(index) == "Owner" || p3->stateIn(index) == "Modified")
					{
						p0->incrementDirtyWriteBack();
					}

					//everyone goes to invalid now
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
				}
				else if(state == "Shared")
				{
					p3->sharedToModified(index);

					//invalidate everyone without sending back to DRAM
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
				}
				else if(state == "Owner")
				{
					p3->ownerToModifed(index);

					//just invalidating everyone
					if(p1->stateIn(index) == "Exclusive")
					{
						p1->exclusiveToInvalid(index);
					}
					if(p1->stateIn(index) == "Modified")
					{
						p1->modifiedToInvalid(index);
					}
					if(p1->stateIn(index) == "Owner")
					{
						p1->ownerToModifed(index);
					}
					if(p1->stateIn(index) == "Shared")
					{
						p1->sharedToInvalid(index);
					}
					if(p2->stateIn(index) == "Exclusive")
					{
						p2->exclusiveToInvalid(index);
					}
					if(p2->stateIn(index) == "Modified")
					{
						p2->modifiedToInvalid(index);
					}
					if(p2->stateIn(index) == "Owner")
					{
						p2->ownerToModifed(index);
					}
					if(p2->stateIn(index) == "Shared")
					{
						p2->sharedToInvalid(index);
					}
					if(p0->stateIn(index) == "Exclusive")
					{
						p0->exclusiveToInvalid(index);
					}
					if(p0->stateIn(index) == "Modified")
					{
						p0->modifiedToInvalid(index);
					}
					if(p0->stateIn(index) == "Owner")
					{
						p0->ownerToModifed(index);
					}
					if(p0->stateIn(index) == "Shared")
					{
						p0->sharedToInvalid(index);
					}
				}
				else if(state == "Modified")
				{
					//don't need to do anything because we are modifing data we already have to latest data of
				}
				else if(state == "Exclusive")
				{
					//don't need to do anything because we are the only ones with the data
					p3->exclusiveToModified(index);
				}
      }//checking processor 3
    }//end write
  }//end main loop


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



  //garabage collection
  delete mypars;
  delete p0;
  delete p1;
  delete p2;
  delete p3;
}
