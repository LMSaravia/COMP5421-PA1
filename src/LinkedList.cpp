#include "LinkedList.h"

using namespace std;

struct LinkedList::ListNode {
private:
	Line data; // node data
	ListNode * prev; // pointer to previous node
	ListNode * next; // pointer to next node

public:
	ListNode() = delete;


	ListNode(const ListNode &) = default; // shallow copy ctor


	ListNode(const Line & line, ListNode * prev = nullptr, ListNode * next = nullptr)
		: data{ line }, prev{ prev }, next{ next } {
	};


	~ListNode() = default;


	// setters and getters for all 3 data members

	void setData(const Line & l) {
		data = l;
	}


	const Line & getData() const {
		return data;
	}


	void setPrev(ListNode * p) {	
		prev = p;
	}


	ListNode * getPrev() const {
		return prev;
	}


	void setNext(ListNode * n) {
		next = n;
	}


	ListNode * getNext() const {
		return next;
	}

}; // end of struct ListNode


LinkedList::LinkedList() { 	// default ctor
	// create dummy head node
	ListNode * dummyHead = new ListNode { Line { "" } } ;
	head = dummyHead;

	// create dummy tail node
	ListNode * dummyTail = new ListNode { Line { "" } } ;
	tail = dummyTail;

	// connect head to tail and tail to head
	// size remains zero. Do not count dummy nodes.
	dummyHead->setNext(dummyTail); 
	dummyTail->setPrev(dummyHead);
}
	
LinkedList::~LinkedList() {  // dtor
	removeAll();
}

LinkedList::LinkedList(const LinkedList & rhs) { // copy ctor
	deepCopy(rhs);
}

const LinkedList & LinkedList::operator=(const LinkedList & rhs) { // copy assignment
	if (this != &rhs) { // nothing to do on self-assignment
		removeAll(); // release storage space currently used by *this (LHS)
		deepCopy(rhs); // copy rhs to *this
	}
	return *this;
}

void LinkedList::push_front(const Line & line) { // inserts line at the front of this list
	// point new node prev to dummyhead and new node next to first node 
	ListNode * newNode = new ListNode{ line, head, head->getNext() };

	// point 1st node prev to new node
	head->getNext()->setPrev(newNode);

	// point dummyhead node next to new node
	head->setNext(newNode);

	// increase list size by 1
	++theSize;
}


void LinkedList::push_back(const Line & line) { // inserts line at the back of this list
	// point new node prev to last node and new node next to dummytail
	ListNode* newNode = new ListNode{ line, tail->getPrev(), tail };

	// point last node next to new node
	tail->getPrev()->setNext(newNode);

	// point dummytail prev to new node
	tail->setPrev(newNode);

	// increase list size by 1
	++theSize;
}


void LinkedList::pop_front() { // removes the first line in this list
	// create temp pointer to popping node to deallocate space later
	ListNode * temp = head->getNext();

	if (temp != tail) { // Avoids popping dummy tail node
		// point the following to popping node's prev to head
		temp->getNext()->setPrev(head);

		// point head next to 2nd node
		head->setNext(temp->getNext());

		// decrease size
		--theSize;

		// deallocate space
		delete temp;
		temp = nullptr;
	}
}


void LinkedList::pop_back() { // removes the last line in this list
	// create temp pointer to popping node to deallocate space later
	ListNode * temp = tail->getPrev();

	if (temp != head) {
		// point the previous to popping node's next to tail
		temp->getPrev()->setNext(tail);

		// point tail prev to node before popping node
		tail->setPrev(temp->getPrev());

		// decrease size
		--theSize;

		// deallocate space
		delete temp;
		temp = nullptr;
	}
}


int LinkedList::size() const { // returns the size of this list
	return theSize;
}


bool LinkedList::empty() const { // returns wether this list is empty
	return (head->getNext() == tail) && (tail->getPrev() == head) && (theSize == 0);
}

void LinkedList::insert(const Line & line, int k) { // inserts a new node with line at 
												// position k in this list
	if (validIndex(k)) { // index ok. 
		// Special case
		if (k == 1) {
			push_front(line);
			return;
		}

		//get pointer to the k-1 node
		ListNode * pre = find(k - 1);

		// get pointer to the current k node
		ListNode * pos = find(k);

		// create new node pointing to the prev and next to be nodes
		ListNode * newNode = new ListNode{ line, pre, pos };

		// update post node's prev
		pos->setPrev(newNode);

		// update prev node's next
		pre->setNext(newNode);
		++theSize;
	}
	else { // invalid index
		cerr << "Error. Invalid index. Unable to insert" << endl;
	}
}													

void LinkedList::remove(int k) { // removes node at position k in this list
	if (validIndex(k)) { // index ok
		// get pointer to the k node
		ListNode * kNode = find(k);

		// update pointers to skip k node
		kNode->getPrev()->setNext(kNode->getNext());
		kNode->getNext()->setPrev(kNode->getPrev());

		--theSize;
		delete kNode;
		kNode = nullptr;
	}
	else { // invalid index
		cerr << "Invalid index. Unable to remove." << endl;
	}
}


void LinkedList::print(int position) const { //prints the line stored in the node at given position
	if (validIndex(position)) { // position ok
		ListNode * tempNode = find(position);
		cout << tempNode->getData() << endl;
		tempNode = nullptr;
	}
	else { // invalid position
		cerr << "Invalid position. Unable to print" << endl;
	}
}


void LinkedList::deepCopy(const LinkedList & original) { // deep copies the supplied LinkedList
	head = new ListNode{ Line { "" } };
	tail = new ListNode{ Line { "" }, head }; // tail points to head
	head->setNext(tail); // head points to tail
	theSize = original.size();

	if (original.empty())
		return; // *this object is good to go
	ListNode * current = original.head->getNext(); // point to first node in original list
	while (current != original.tail) { // stop at tail
		push_back(current->getData()); // copy original line at the end of the new list
		current = current->getNext(); // point to the following node in original list
	}
}


void LinkedList::removeAll() { // releases all nodes / Don't KEEP DUMMY HEAD AND TAIL / USED BY DESTRUCTOR
	while (!empty()) {
		pop_front();
	}
	delete head;
	head = nullptr;
	delete tail;
	tail = nullptr;
}


/** Check whether an element exists at a given index before attempting to access that element.
* @ param i the index to be checked.
* @ return true if index i is valid, false otherwise.
*/
bool LinkedList::validIndex(int i) const {
	return !(i < 1 || i > size());
}

/** Returns a pointer to the node at a given position in the list.
* @ param index The position of the node.
* @return A pointer to the node at position k, if exists; otherwise, nullptr.
*/
LinkedList::ListNode * LinkedList::find(int i) const
{
	if (i < 1 || i > size()) {
		return nullptr; // signal bad index
	}
	else {
		ListNode * current = head;
		for (int n = 0; n < i; ++n) {
			current = current->getNext();
		}
		return current;
	}
}