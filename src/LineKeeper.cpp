#include<iostream>
#include<fstream>
#include<string> // can use member functions for the assingment, not variables

#include "LineKeeper.h"

using namespace std;

 /*Extracts lines in filename into this LineKeeper's list.
 It terminates and exits the program if the file does not exists
 otherwise it constructs a LineKeeper object.*/
LineKeeper::LineKeeper(const char * filename) {

	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			Line newLine{ line.c_str() };
			list.push_back(newLine);
		}
		myfile.close();
	}
	else {
		cerr << "Unable to open file" << endl;		
		exit(EXIT_FAILURE);
	}
}


 //swaps m and n if m > n. Adjusts m and n depending on how the intervals [m,n]
 //and [1, size()] overlaps. Finally it prints lines m through n to std output.
void LineKeeper::print(int m, int n) {
	if (!list.empty()) {
		// swap m and n if m > n
		if (m > n)
			swap(m, n);

		// check range
		if (!inRange(m, n)) {
			cout << "Invalid range of line numbers from " << m << " to " << n << endl;
			// adjust start to [1, size()]
			if (m < 1) {
				m = 1;
			}
			else if (m > list.size()) {
				m = list.size();
			}

			// adjust end to [1, size()]
			if (n < m) {
				n = m;
			}
			else if (n > list.size()) {
				n = list.size();
			}

			// show default range
			cout << "Default value from " << m << " to " << n << " is now in effect.\n";
		}

		// print range
		while (m <= n) {
			cout << "(" << m << ") ";
			list.print(m);
			++m;
		}
	}
	else
		cerr << "Error. Empty list. Nothing to print." << endl;
}	

/*Checks wether two numbers are within the list's number of items range*/
bool LineKeeper::inRange(int j, int k) {
	return !(j < 1 || k < 1 || j > list.size() || k > list.size());
}