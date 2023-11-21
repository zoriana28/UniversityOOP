#include <iostream>
#include <string>
#include <list>
using namespace std;
class Airplane {
private:
	string destination;
	int number;
	string Name;
	string Date;
public:
	Airplane() {
		destination = "Paris";
		number = 567;
		Name = "Shevchenko";
		Date = "23.11.22";
	}
	Airplane(string a, int b, string c, string d) {
		destination = a;
		number = b;
		Name = c;
		Date = d;
	}
	~Airplane() {}
	string getdestination();
	int getnumber();
	string getName();
	string getDate();
	string getDate() const;
	void setdestination(string s);
	void setnumber(int a);
	void setName(string s);
	void setDate(string s);
	void ReadfromFile(const string& fileName, list<Airplane>& ticket);
	void Print(list<Airplane>& ticket);
	void Add(list<Airplane>& ticket);
	void Delete(list<Airplane>& ticket);
	void PrintNumber(list<Airplane>& ticket);
	void PrintDestination(list<Airplane>& ticket);
	void PrintDate(list<Airplane>& ticket);
	friend istream& operator>> (istream& is, Airplane& ticket);
	friend ostream& operator<< (ostream& os, const Airplane& ticket);
	void ReadList(list<Airplane>& ticket);
};