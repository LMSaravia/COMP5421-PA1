#include <iostream>
#include <fstream>
#include "LineKeeper.h"

using namespace std;

int main() {
	// build a LineKeeper object from the lines in the input.txt text file
	LineKeeper lk("input.txt");
	cout << "\n" << "lk.print(2)" << "\n";	 lk.print(2);
	cout << "\n" << "lk.print(13, 7)" << "\n";	 lk.print(13, 7);
	cout << "\n" << "lk.print(25, 5)" << "\n";	 lk.print(25, 5);
	cout << "\n" << "lk.print(-25, 5)" << "\n";	 lk.print(-25, 5);
	cout << "\n" << "lk.print(-25 , -85)" << "\n";	 lk.print(-25, -85);
	cout << "\n" << "lk.print(25, 50)" << "\n";	 lk.print(25, 50);
	cout << "Done!" << endl;
	return 0; // report success
}