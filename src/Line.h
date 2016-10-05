#ifndef LINE_H
#define LINE_H

#include <iostream>

class Line {
private:
	char * linePtr{ nullptr };		// pointer to first character in this line
	int lineLength{ 0 };			// length of this line
	int lineCapacity{ 0 };			//storage capacity of this line

public:
	Line() = delete; // specific requirement

	explicit Line(const char * cstr); // constructs this line from a given C-string

	explicit Line(char c); // constructs this line from one char

	Line(const Line& l); // copy ctor

	const Line & operator=(const Line & rhs); // copy assignment operator overload.

	virtual ~Line(); // releases dynamic memory owned by this line
	
	const char * cstr() const; // returns C-style version of this Line

	int length() const; // returns length of this line

	bool empty() const; // returns whether this line is empty

	bool full() const; // returns whether this line is full

	int capacity() const; // returns capacity of this line

	void resize(); // doubles capacity of this line

	void pushBack(const char & ch); // appends ch to the end of this line

	void popBack(); // removes the last char in this line

	friend	// prints this line
		std::ostream & operator<<(std::ostream & out, const Line & line); 

	friend	// reads into this line
		std::istream & operator>>(std::istream & in, Line & line); 

}; // class Line

#endif // !LINE_H