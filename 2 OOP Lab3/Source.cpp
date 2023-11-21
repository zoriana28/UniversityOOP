#include "Airplane.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
	Airplane obj1;
	list<Airplane>ticket;
	int c;
	obj1.ReadfromFile("File.txt", ticket);
	do {
		cout << "1 - Add the apply" << endl <<
			"2 - Delete the apply" << endl <<
			"3 - Print the statement by flight number" << endl <<
			"4 - Print applications for sorted destinations" << endl <<
			"5 - Print applications for sorted date" << endl <<
			"0 - exit" << endl;
		cin >> c;
		switch (c) {
		case 1:
			obj1.Add(ticket);
			break;
		case 2:
			obj1.Delete(ticket);
			break;
		case 3:
			obj1.PrintNumber(ticket);
			break;
		case 4:
			obj1.PrintDestination(ticket);
			break;
		case 5:
			obj1.PrintDate(ticket);
		}
	} while (c != 0);
	return 0;
}