#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

class Meet {
public:
	
private:
	TimeInterval
};

int main() {
	int q;
	cin >> q;
	map<int, Day> shedule;
	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "APPOINT") {
			Appoint(shedule);
		}
		if (command == "PRINT") {
			Print(shedule);
		}
	}
	return 0;