#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Line.h"

class LinkedList {
private:
	struct ListNode;

	int theSize{ 0 }; // number of elements in this list
	ListNode * head = { nullptr }; // pointer to the first node in this list
	ListNode * tail = { nullptr }; // pointer to the last node in this list
	

public:
	LinkedList(); // default ctor
	
	virtual ~LinkedList(); // dtor

	LinkedList(const LinkedList & rhs); // copy ctor

	const LinkedList & operator=(const LinkedList & rhs); // copy assignment

	void push_front(const Line & line); // inserts line at the front of this list

	void push_back(const Line & line); // inserts line at the back of this list

	void pop_front(); // removes the first line in this list

	void pop_back(); // removes the last line in this list

	int size() const; // returns the size of this list

	bool empty() const; // returns wether this list is empty

	void insert(const Line & line, int k); // inserts a new node with line at 
										   // position k in this list

	void remove(int k); // removes node at position k in this list

	void print(int position) const;// prints the line stored in the node at given position

private:
	bool validIndex(int i) const; // returns whether a given index i is valid

	void deepCopy(const LinkedList & original);

	ListNode * find(int i) const; // returns a pointer to the node at position i

	void removeAll();

};
#endif // !LINKED_LIST_H
