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
    cout << binary << endl;
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
	//cout << "total " << total << endl;
  return total;
}

string getTag(string binary)
{
  string tag;
  for(int i = 0; i < 18; i++)
  {
    tag[i] = binary[i];
  }
	for(int k = 0; k < 18; k++)
	{
	cout << tag[k];
	}
	cout  << endl;
  return tag;
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
		cout << tag << endl;
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
						p1->exclusivetoShared(index);
						//increment p1 shared
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p0->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusivetoShared(index);
						//increment p2 shared
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
						p0->invalidToShared(index);
					}
				}//end p2 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusivetoShared(index);
						//increment p3 shared
						p0->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p0->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p0->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
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
						p0->exclusivetoShared(index);
						//increment p1 shared
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p1 shared
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p1->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusivetoShared(index);
						//increment p2 shared
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
						p1->invalidToShared(index);
					}
				}//end p2 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusivetoShared(index);
						//increment p3 shared
						p1->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p1->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p1->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
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
						p0->exclusivetoShared(index);
						//increment p0 shared
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p0 shared
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p0 shared
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p0 shared
						p2->invalidToShared(index);
					}
				}//end p0 look up
				else if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p1->stateIn(index);

					if(state == "Exclusive")
					{
						p1->exclusivetoShared(index);
						//increment p1 shared
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p2->invalidToShared(index);
					}
				}//end p1 look up
				else if(p3->find(tag, index) == true && p3->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p3->stateIn(index);

					if(state == "Exclusive")
					{
						p3->exclusivetoShared(index);
						//increment p3 shared
						p2->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p3 shared
						p2->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p3->modifiedToOwner(index);
						//incrememnt p3 shared
						p2->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p3 shared
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
						p0->exclusivetoShared(index);
						//increment p0 shared
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p0 shared
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p0->modifiedToOwner(index);
						//incrememnt p0 shared
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p0 shared
						p3->invalidToShared(index);
					}
				}//end p0 look up
				else if(p1->find(tag, index) == true && p1->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p1->stateIn(index);

					if(state == "Exclusive")
					{
						p1->exclusivetoShared(index);
						//increment p1 shared
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p1 shared
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p1->modifiedToOwner(index);
						//incrememnt p1 shared
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p1 shared
						p3->invalidToShared(index);
					}
				}//end p1 look up
				else if(p2->find(tag, index) == true && p2->stateIn(index) != "Invalid")
				{
					//get the state of the data
					state = p2->stateIn(index);

					if(state == "Exclusive")
					{
						p2->exclusivetoShared(index);
						//increment p2 shared
						p3->invalidToShared(index);
					}
					if(state == "Shared")
					{
						//increment p2 shared
						p3->invalidToShared(index);
					}
					if(state == "Modified")
					{
						p2->modifiedToOwner(index);
						//incrememnt p2 shared
						p3->invalidToShared(index);
					}
					if(state == "Owner")
					{
						//increment p2 shared
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

/*
  //expected output for project
  //total number of cache to cache transfers for each processor pair
  cout << "The total number of cache-to-cache transfers for each processor pair in the following format."
  cout << "P0 cache transfers: <p0-p1> = " << xxx << ", <p0-p2> = " << xxx << ", <p0-p3> = " << xxx << endl;
  cout << "P1 cache transfers: <p1-p0> = " << xxx << ", <p1-p2> = " << xxx << ", <p1-p3> = " << xxx << endl;
  cout << "P2 cache transfers: <p2-p0> = " << xxx << ", <p2-p1> = " << xxx << ", <p2-p3> = " << xxx << endl;
  cout << "P3 cache transfers: <p3-p0> = " << xxx << ", <p3-p1> = " << xxx << ", <p3-p2> = " << xxx << endl;

  //total number of invalidations due to coherence in each processor
  cout << "The total number of invalidations due to coherence (i.e. not including line replacement) in each processor in the following format." << endl;
  cout << "P0 Invalidation from: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << endl;
  cout << "P1 Invalidation from: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << endl;
  cout << "P2 Invalidation from: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << endl;
  cout << "P3 Invalidation from: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << endl;

  //total number of dirty writebacks for each processor
  cout << "The number of dirty writebacks from each processor." << endl;
  cout << "P0 = " << xxx << ", P1 = " << xxx << ", P2 = " << xxx << ", P3 = " << xxx << endl;

  //number of lines in each state at the end  of the simulation for each processor
  cout << "The number of lines in each state at the end the simulation for each processor." << endl;
  cout << "P0: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << ", i = " << xxx << endl;
  cout << "P1: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << ", i = " << xxx << endl;
  cout << "P2: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << ", i = " << xxx << endl;
  cout << "P3: m = " << xxx << ", o = " << xxx << ", e = " << xxx << ", s = " << xxx << ", i = " << xxx << endl;
*/

  //garabage collection
  delete mypars;
  delete p0;
  delete p1;
  delete p2;
  delete p3;
}
