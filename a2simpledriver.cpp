// File:        a1simpledriver.cpp
// Author:      Fred Mose / Geoffrey Tien
// Date:        January 19, 2016
// Description: Basic test driver for CMPT 225 assignment #2
//              This file tests some functions of the CCQueue and DLinkedList classes of assignment #2.
//              Note that only functions which are called will be compiled, therefore you must
//                ensure that every function in your classes is called at least once.
//              Not all special cases have been tested; you will be responsible for adding
//                your own test code and function calls to this file in order to thoroughly
//                test all general and boundary cases for your functions.
//              In general, please ensure that you test:
//               1. invalid parameter(s)
//               2. valid parameter(s), boundary case
//               3. valid parameter(s), general case

#include <cstdlib>
#include <iostream>
#include <string>

#include "ccqueue.h"
#include "dlinkedlist.h"
#include "ticket.h"

using namespace std;

// forward function declarations
void LLTest();
void CCQTest();

// program entry point
int main()
{
  cout << "Entering DLinkedList test function... " << endl;
  LLTest();
  cout << "... DLinkedList test function complete!\n" << endl;

  cout << "Entering CCQueue test function... " << endl;
 CCQTest();
  cout << "... CCQueue test function complete!\n" << endl;

  system("pause");
  return 0;
}

void LLTest()
{
  // default constructor, InsertFront, InsertBack, ElementAt
  DLinkedList<int> lla;
  lla.InsertFront(5);
  lla.InsertBack(10);
  cout << "lla contains " << lla.ElementAt(0) << " at index 0." << endl;
   cout << "lla contains " << lla.ElementAt(1) << " at index 1." << endl;
   cout<<"LLa size is "<<lla.Size()<<endl;

  // copy constructor, InsertAt, RemoveAt (with exception)
  DLinkedList<int> llb(lla);
   cout<<"LLb size is "<<llb.Size()<<endl;
  llb.InsertAt(7, 1);
   cout<<"LLb size is "<<llb.Size()<<endl;

  try
  {
    int temp = llb.RemoveAt(12345);
  }
  catch (exception e)
  {
    cout << "Exception in RemoveAt(): " << e.what() << endl;
  }

  // assignment operator, IsEmpty, Size, RemoveDuplicates, Contains
  DLinkedList<int> llc;
  if (llc.IsEmpty())
    cout << "llc is empty." << endl;
  else
    cout << "llc is not empty." << endl;
  llc = lla;
   cout<<"LLc size is "<<llc.Size()<<endl;
  llc.InsertBack(13);
  llc.InsertBack(13);
  llc.InsertBack(13);
  cout << "llc contains " << llc.Size() << " items." << endl;
  llc.RemoveDuplicates();
   cout << "llc contains " << llc.Size() << " items." << endl;
  if (llc.Contains(10))
    cout << "10 found in llc." << endl;
  else
    cout << "10 not found in llc." << endl;
  if (llc.Contains(13))
    cout << "13 found in llc." << endl;
  else
    cout << "13 not found in llc." << endl;
}

void CCQTest()
{
  CCQueue ccq;
 /* ccq.Add("Alrikr", "Video card smoked");
  ccq.Add("Bjornstjerne", "Received wrong colour cable");
  ccq.Add("Cyprianus", "Motherboard DOA");
  ccq.Add("Dietrich", "Order not received");
  ccq.Add("Elisaeus", "Only 931GB on 1TB hard drive");*/

  ccq.Add("A", "B");
  ccq.Add("C", "D");
  ccq.Add("E", "F");
  ccq.Add("G", "H");
  ccq.Add("I", "J");
  cout << "Size of ticket queue: " << ccq.Size() << endl;
  ccq.Service();
   ccq.Add("M", "N");
  ccq.Add("O", "P");
  //ccq.Service();
 ccq.MoveUp(3);
 //ccq.MoveUp(1);
  ccq.MoveDown(3);
  cout << ccq.PrintStatus() << endl;
}
