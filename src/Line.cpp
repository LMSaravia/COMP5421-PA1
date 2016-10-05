//#include <iostream>
//#include <cstring>
#include "Line.h"

using namespace std;

Line::Line(const char * cstr) {
	lineLength = strlen(cstr);
	lineCapacity = lineLength;
	linePtr = new char[lineLength + 1];
	strcpy(linePtr, cstr);
}


Line::Line(char c) {
	const short int INITIAL_CAPACITY = 10;
	lineLength = 1;
	lineCapacity = INITIAL_CAPACITY;
	linePtr = new char[INITIAL_CAPACITY + 1]{ c, '\0' };
}


Line::Line(const Line & l) {
	lineLength = l.lineLength;
	lineCapacity = lineLength;
	linePtr = new char[lineLength + 1];
	strcpy(linePtr, l.linePtr);
}


const Line & Line::operator=(const Line & rhs) {
	if (this == &rhs)
		return *this; // do nothing on self-assignment
	else {
		delete[] linePtr; // release dynamic storage currently used by calling object (LHS)
		lineLength = rhs.lineLength;
		lineCapacity = lineLength;
		linePtr = new char[lineLength + 1]; // allocate new storage
		strcpy(linePtr, rhs.linePtr); // copy									
	}
	return *this; // as const reference
}


Line::~Line() {
	lineLength = 0;
	lineCapacity = lineLength;
	delete[] linePtr;
	linePtr = nullptr;   // defensive programming
}


const char * Line::cstr() const {
	return linePtr;
}


int Line::length() const {
	return lineLength;
}


bool Line::empty() const {
	return !(lineLength > 0);
}


bool Line::full() const {
	return (lineLength >= lineCapacity);
}


int Line::capacity() const {
	return lineCapacity; 
}


void Line::resize() {	
	int newCapacity = capacity() * 2; // define doubled size
	char * tempArr = new char[newCapacity + 1]; // allocate new storage 
	strcpy(tempArr, linePtr); // copy
	lineCapacity = newCapacity; // set new lineCapacity
	delete[] linePtr; // release dynamic storage currently used by linePtr
	linePtr = tempArr; // update linePtr to new array in dynamic storage
}


void Line::pushBack(const char & ch) {
	if (full())
		resize();
	linePtr[lineLength] = ch; // append char to the line
	linePtr[lineLength + 1] = '\0';// append end char
	lineLength++;
}


void Line::popBack() {
	if (!empty()) {
		linePtr[lineLength - 1] = '\0'; // replace last char in the line w/ end char
		lineLength--;
	}
}


// Friend members, privileged to see the private members of its parameter line

std::ostream & operator<<(ostream & out, const Line & line) {
	if (line.lineLength > 0)
		out << line.linePtr;
	return out;
}


std::istream & operator>>(istream & in, Line & line) {
	char c;
	while (in.get(c)) {
		if (line.full())
			line.resize();
		line.pushBack(c);
	}
	return in;
}