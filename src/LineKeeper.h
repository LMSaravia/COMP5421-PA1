#ifndef LINEKEEPER_H
#define LINEKEEPER_H

#include "LinkedList.h"

class LineKeeper {
private:
	LinkedList list;

	//Returns true if two line indexes are within [1, size()].
	bool LineKeeper::inRange(int j, int k);

public:
	LineKeeper() = delete;

	/* Extracts lines in filename into this LineKeeper's list.
	   It terminates and exits the program if the file does not exists
	   otherwise it constructs a LineKeeper object.*/
	LineKeeper(const char * filename); 

	/* Swaps m and n if m > n. Adjusts m and n depending on how the intervals [m,n]
	 and [1, size()] overlaps. Finally it prints lines m through n to std output.*/
	void print(int m, int n = 1); 

};

#endif // !LINEKEEPER_H