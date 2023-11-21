#include "Airplane.h"
#include <fstream>
using namespace std;

string Airplane::getdestination()
{
	return destination;
}
int Airplane::getnumber()
{
	return number;
}
string Airplane::getName()
{
	return string(Name);
}
string Airplane::getDate()
{
	return Date;
}
string Airplane::getDate() const
{
	return Date;
}
void Airplane::setdestination(string s)
{
	destination = s;
}
void Airplane::setnumber(int a)
{
	number = a;
}
void Airplane::setName(string s)
{
	Name = s;
}
void Airplane::setDate(string s)
{
	Date = s;
}
void Airplane::Print(list<Airplane>& ticket)
{
	for (const Airplane& airplane : ticket) {
		cout << airplane.destination << " " << airplane.number << " " << airplane.Name << " " << airplane.Date << endl;
	}
}
void Airplane::Add(list<Airplane>& ticket)
{
	string Destination;
	int Number;
	string name;
	string date;
	cout << "Enter the destination" << endl;
	cin.ignore();
	getline(cin, Destination);
	cout << "Enter the flight number" << endl;
	cin >> Number;
	cout << "Enter the passenger's name" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Enter the date" << endl;
	cin >> date;
	Airplane tickets(Destination, Number, name, date);
	ticket.push_back(tickets);
}
void Airplane::Delete(list<Airplane>& ticket)
{
	int Number;
	cout << "Enter the flight number" << endl;
	cin >> Number;
	for (list<Airplane>::iterator it = ticket.begin(); it != ticket.end();) {
		Airplane& Element = *it;
		if (Number == Element.number)
			it = ticket.erase(it);
		else
			++it;
	}
}
void Airplane::PrintNumber(list<Airplane>& ticket)
{
	int Number;
	cout << "Enter the flight number" << endl;
	cin >> Number;
	bool flag = false;
	for (list<Airplane>::iterator it = ticket.begin(); it != ticket.end(); it++) {
		Airplane& Element = *it;
		if (Number == Element.number) {
			cout << Element.destination << " " << Element.number << " " << Element.Name << " " << Element.Date << endl;
			flag = true;
			break;
		}
	}
	if (flag == false)
		cout << "Not found" << endl;
}
void Airplane::PrintDestination(list<Airplane>& ticket)
{
	ticket.sort([](const Airplane& a, const Airplane& b) {
		return a.destination < b.destination;
		});

	for (const Airplane& airplane : ticket) {
		cout << airplane.destination << " " << airplane.number << " " << airplane.Name << " " << airplane.Date << endl;
	}
}
bool dateComparator(const Airplane& a, const Airplane& b) {
	return a.getDate() < b.getDate();
}
void Airplane::PrintDate(list<Airplane>& ticket) {
	ticket.sort(dateComparator);
	for (const Airplane& airplane : ticket) {
		cout << airplane.destination << " " << airplane.number << " " << airplane.Name << " " << airplane.Date << endl;
	}
}
void Airplane::ReadList(list<Airplane>& ticket)
{
	istream_iterator<Airplane> input_it(cin);
	istream_iterator<Airplane> input_end;
	copy(input_it, input_end, back_inserter(ticket));
}
istream& operator>>(istream& is, Airplane& ticket)
{
	is >> ticket.destination >> ticket.number >> ticket.Name >> ticket.Date;
	return is;
}
ostream& operator<<(ostream& os, const Airplane& ticket)
{
	for (int i = 0; i < 4; i++) {
		os << ticket.destination << endl;
		os << ticket.number << endl;
		os << ticket.Name << endl;
		os << ticket.Date << endl;
	}
	return os;
}
void Airplane::ReadfromFile(const string& fileName, list<Airplane>& ticket)
{
	ifstream file(fileName);
	if (file.is_open()) {
		ticket.clear();
		Airplane application;

		while (file >> application) {
			ticket.push_back(application);
		}

		file.close();

	}
	else
		cerr << "Error" << endl;

}