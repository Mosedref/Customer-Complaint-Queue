// File:        dlinkedlist.cpp
// Author:      Fred Mose
// Date:        January 18, 2016
// Description: Definition of a implementation  doubly-linked-list class for CMPT 225 assignment 2

#ifdef _DLINKEDLIST_H_

#include "dlinkedlist.h"
#include <iostream>

using namespace std;



 // helper function for deep copy
    // Used by copy constructor and operator=




   template <class T>
   void DLinkedList<T>::CopyList(const DLinkedList& ll)
   {
		for (int i = 0; i < ll.Size(); i++) // for every element on the right side 
		{
			 T  element = ll.ElementAt(i);  // copy element by element deep copy into a T object
			 InsertAt(element, i); //  place the element into the list at its correct index

		}

	}


    // helper function for deep delete
    // Used by destructor and copy/assignment
    template <class T>
    void DLinkedList<T>::DeleteList()
	{
		Node<T>* cursor = front; // set a cursor to the front

		while(cursor) // while cursor is not  NULL
		{
			cursor = front->next; // move cursor along
			delete front; //delete the front node
			front = cursor; // cursor becomes new front
		}
		front = NULL; // just in case set to NULL
		back = NULL; // to keep from having dangling pointers
		size = 0; // reset size
	}

   // default constructor
    template <class T>
   DLinkedList<T>::DLinkedList()

	{
		size = 0; // set default size
		front = NULL; // inialize to NULL
		back = NULL;// inialize to NULL
	}

     // copy constructor, performs deep copy of list elements
    template <class T>
    DLinkedList<T>::DLinkedList(const DLinkedList& ll)

	{
		size=0; // do everthing of default
		front = NULL;
		back = NULL;
		CopyList(ll); // plus dynamic memory deep copy

	}


   // destructor
	 template <class T>
   DLinkedList<T>::~DLinkedList()
   {
	   DeleteList(); // call help destroy function
   }


     // MUTATORS

    // Inserts an item at the front of the list
    // POST:  List contains item at position 0
    // PARAM: item = item to be inserted
   template<class T>
 void DLinkedList<T>::InsertFront(T item)
 {
	  Node<T>* insert; // pointer to node that will inserted
	  insert = new Node<T>(item); // point it a new node

	 if(front == NULL)
	 {
		insert->next = NULL; // placing in first node so next is NULL
		front = insert; // inserting front of list
		back =insert; // front and back point at the 1 object for now
		front->prev = NULL; // no such thing in the front
		size++; // increment list size
	 }
	 else // base case
	 {
		// insert->data = item;
		 insert->next =front; // keep fornt where is
		 front->prev = insert;
		 insert->prev = NULL;
		 front = insert;
		 size++;// increment list size
	 }

 }

  // Inserts an item at the back of the list
    // POST:  List contains item at back
    // PARAM: item = item to be inserted
 template<class T>
 void DLinkedList<T>::InsertBack(T item)
 {
	  Node<T>* insert;
	  insert = new Node<T>(item);

	  if(front == NULL) // for first element
	 {
		insert->next = NULL; // after back is NULL
		front = insert; // place in insert
		back =insert; // front and back point at the 1 object for now
		front->prev = NULL;
		size++;
	 }

	  else // base case
	  {
		  // insert->data = item;
		   back->next = insert;
		   insert->prev = back;
		   back = insert;
		   back->next = NULL;
		   size++;

	  }

 }

 // Inserts an item in position p (0-indexed)
    // Throws exception for invalid index
    // PRE:   0 <= p <= size
    // POST:  List contains item at position p
    // PARAM: item = item to be inserted, p = position where item will be inserted
  template<class T>
 void DLinkedList<T>::InsertAt(T item, int p)
 {


  try
  {
	  if(front == NULL) // if list is empty
	  {
		  if(p != 0) // if index to be inserted is not 0
		   throw p;

		  InsertFront(item); // if p is 0 then insert the front
		  return;

	  }
	    if(p==0) // first elment
		{
			 InsertFront(item);// if p is 0 then insert the front
			 return;
		}

	  if(p > size+1) // if inserting bigger than the list plus  one you can't do this only to the back
		  throw p;


	  if(p == size) // if all the elements are there and you want to last index so you insert a back
	  {
		  InsertBack(item); 
		  return;
	  }
	

	  Node<T>* insert; // for inserting in between to objects
	  Node<T>* cursor, *before;// need cursor to move up list and before to hold place
	  cursor = front; // start at front
	  int counter = 0; // for indexing purposes

	 while(counter < p && cursor)
	 {
		 counter++; 
		 cursor = cursor ->next; // cursor will point to object at index
	 }
	 
	 if(counter == p) // when equal to index
		{
			insert = new Node<T>(item); // create new node
			before = cursor ->prev; // hold place of before
			before->next = insert;  // REATTACH
			insert ->next = cursor;// REATTACH
			insert ->prev = before;// REATTACH
			cursor ->prev = insert;// REATTACH
			size++; // add one more to size

		}

  }

  catch(...) // default catch block
  {
	  cout << " There is no position: " << p << " Invalid index error " << endl;
  }
 }


  // Removes and returns an item from position p (0-indexed)
  // Throws exception if list is empty or index invalid
  // PRE:   0 <= p <= size
  // POST:  Item is removed from list
  // PARAM: p = position from where item will be removed
 template<class T>
 T DLinkedList<T>::RemoveAt(int p)
 {
	 Node<T>* remove, *cursor, *before;
	 T itemReturned;
	try
	{
		if(IsEmpty()) // if empt nothing to remove so throw error
			 throw p; 

		if(p >= size)
			throw std::out_of_range(" INDEX OUT OF RANGE");  // if trying to remove something not there


		//removing front;
		if(p == 0) // if removing fist element
		{
			if(size == 1) // if only one element there
			{
				itemReturned = front->data; // store
				delete front; 
				front = NULL; // set pointers to NULL list now empty
				back = NULL;
				size--;
				return itemReturned;
			}
			else // eveery other element
			{
				remove = front;  // want to start at front
				front = front->next; // front one after
				front->prev = NULL; // deATTACH
				remove->next = NULL;
				itemReturned = remove->data; // holds data
				delete remove;
				remove = NULL;
				size--; // decrement size
				return itemReturned;
			}


		}


		//removing back
		else if ( p == size -1) // if removing the back 
		{
			remove = back; // back is what is going to be removed
			back = back->prev; // moved to the one before
			remove->prev = NULL; // DEATTACH
			back->next = NULL;// DEATTACH
			itemReturned = remove->data; // save data
			delete remove; // remove node
			remove = NULL; // set poiter to NULL
			size--; // decrement size
			return itemReturned;
		}

		
		else//removing in betweens
		{
			int counter = 0;
			cursor = front;

			while (cursor)
			{
				before = cursor->prev; // holds adress of before so reATTACH
				if(counter == p)
				{
					remove = cursor;
					cursor = cursor->next;
					cursor->prev = before; // back is what is going to be removed
					before->next = remove->next;
					remove->prev = NULL;// DEATTACH
					remove->next = NULL;// DEATTACH
					itemReturned = remove->data;// save data
					delete remove; // remove node
					size--;// decrement size
					return itemReturned;

				}
				
				cursor = cursor->next;
				counter++;

			}
		}

	}

	catch(int p) // catch p
	{
	   cout<< "ERROR INVALID INDEX"<<endl;
	}

 }

 // Removes duplicates from the list, preserving existing order of remaining items.
    // The first occurrence of any duplicate (relative to the front of the list)
    //   is the one which remains.
    // We have not yet learned about efficiency so you may implement this in any way
    //   as long as the resulting list satisfies the requirement above.
    // PRE:
    // POST:  List contains no duplicates, front and back point to the appropriate nodes
    // PARAM:
	template <class T>
	void DLinkedList<T>::RemoveDuplicates()
	{
		T duplicate; // T object to hold the item to be removed
		int found = 0;
		for(int i = 0; i< size; i++) // for every element
		{
			duplicate = ElementAt(i); // set duplicate as that element
			for(int j = i+1; j < size; j++) // chcek through rest of list
			{
				if(duplicate == ElementAt(j)) //if duplicate is the same as that element
				{
					RemoveAt(j); // then remove that element
					j--; // decrement size
				}
			}

		}

	}




  // Returns size of list
    template <class T>
    int  DLinkedList<T>::Size() const
	{
		return size; //  returns size of list
	}

	// Returns whether the list is empty
	template <class T>
    bool DLinkedList<T>::IsEmpty() const
	{
		if(front == NULL) // if front is NULL then list is empty()
		{
			return true; 
		}
		return false;

	}

	// Returns existence of item
	template <class T>
    bool  DLinkedList<T>::Contains(T item) const 
	{
		Node<T>* cursor = front; // cursor to move through list starting from node

		while(cursor) // while cursor not NULL
		{
			if(cursor->data == item) // and item is there
			{
				return true;
			}
			cursor= cursor->next; // move along
		}

		return false;


	}

    // Returns item at index (0-indexed)
    // Throws exception for invalid index
    template <class T>
    T  DLinkedList<T>::ElementAt(int p) const
	{
		Node<T>* cursor;// cursor to move through list starting from node
		cursor = front; // starting at the front
		int count = 0; // for index purposes

	try
	{
		if(p < 0 || p >= size) // if a negative index or is greater than or equal to size of list 
		{
			throw p; // throw this index as a exception
		}

		for (int i = 0  ; i < size ; i++) // for every element 
		{
			if (i == p) // if index is tha of the one being passed in
			{
				return cursor->data; // return its data
			}
			cursor = cursor->next; //  move along
		}

	}

		catch(int p) // catch the exception
		{
			cout<<"Invalid index at "<< p<<endl;
		
		}

	}


 //   // OVERLOADED OPERATORS

 //   // overloaded assignment operator
 //   // must work in the following cases:
 //   // list2 = list1 -> general case
 //   // list2 = list2 -> should do nothing
   template <class T>
    DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& ll)
	{
		if(	this != &ll) // if they are not equal
		{
			DeleteList(); // delete the left side 
			CopyList(ll); // deep copy elements form right side
		}

		return *this;

	}


#endif