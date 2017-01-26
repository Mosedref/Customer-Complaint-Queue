// File:        dlinkedlist.cpp
// Author:      Fred Mose
// Date:        January 18, 2016
// Description: Definition of a implementation  doubly-linked-list class for CMPT 225 assignment 2


#include "ccqueue.h"

using namespace std;


 // default constructor
    CCQueue::CCQueue()
	{
		maxticketid = 0; // maxticketid begins at 0
	}


    bool CCQueue::Add(string customer, string complaint)
	{
		
		if(customer == "" || complaint == "") //if either parameter is empty string the function returns false
		{
			return false;
		}

		Ticket newTicket(maxticketid+1, customer,complaint);// creates a new ticket object and initializes it to the contents being passed in and increments the current ticket id amount via constructor
		tickets.InsertBack(newTicket); // inserts new ticket into back of the queue
		maxticketid++; // increments the number of tickets in queue at this moment 

		return true;
	}

    // throws a logic_error if the ticket queue is empty
    // POST:  first item of the ticket queue is removed
    Ticket CCQueue::Service()
	{
		if(tickets.IsEmpty())
		{
			//Ticket X;
			throw std::out_of_range(" INDEX OUT OF RANGE"); 
			//return X;
		}
		else
		{
			return tickets.RemoveAt(0);// removes and returns an item from the front of the ticket queue
		}
	}


	// moves an item towards the front of the queue by 1 position and returns true
    // returns false if supplied index is 0 (first item) or outside the list boundaries
    // POST:  DLinkedList items at position and position-1 swap spots in the list
    // PARAM: initial index of item to move up
    bool  CCQueue::MoveUp(int index)
	{
		if(index == 0 || index >= tickets.Size() || tickets.IsEmpty() || tickets.Size() < 2) // if index is 0 if it's greater than the size, if there are no tickets or there aren't two rickets to switch
		{
			return false;
		}

		if(index-1 == 0) // if you want to move up the second one in the list you are just moving it to the front 
		{
			tickets.InsertFront(tickets.RemoveAt(index)); // insert the object to be removed at that index to the front
		}
		else
		{
		tickets.InsertAt(tickets.RemoveAt(index), index-1); // else index is swapped with index -1
		}
		
		return true;


	}

	 // moves an item towards the back of the queue by 1 position and returns true
    // returns false if supplied index is the last item or outside the list boundaries
    // POST:  DLinkedList items at position and position+1 swap spots in the list
    // PARAM: initial index of item to move down
    bool  CCQueue::MoveDown(int index)
	{
		if(index == tickets.Size()-1 || index >= tickets.Size() || tickets.IsEmpty() || tickets.Size() < 2) // if index is 0 if it's greater than the size, if there are no tickets or there aren't two rickets to switch
		{
			return false;
		}

		tickets.InsertAt(tickets.RemoveAt(index), index+1);// else index is swapped with index + 1

		return true;
	}

    int  CCQueue::Size() const
	{
		return tickets.Size(); // returns the number of tickets

	}