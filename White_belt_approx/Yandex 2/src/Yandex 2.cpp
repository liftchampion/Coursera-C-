#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

/*struct IP {
	int p1;
	int p2;
	int p3;
	int p4;
};

istream& operator>> (istream&, IP& new_ip) {

}*/

void CheckNextSymbol_N (stringstream& ss) {
	if (ss.peek() < '0' || ss.peek() > '9' ) {
		//cout << "1";
		throw (exception());
	}
}

void CheckNextSymbol_D (stringstream& ss) {
	if (ss.peek() != '.'){
		//cout << "2";
		throw (exception());
	}
}

void CheckAllSymbols (const string& s) {
	set<char> syms = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.'};
	int n_dots = 0;
	for (const auto& i : s) {
		if (syms.count(i) == 0) {
			//cout << "3";
			throw (exception());
		}
		if (i == '.') {
			++n_dots;
		}
	}
	if (n_dots != 3) {
		//cout << "4";
		throw (exception());
	}
}



bool CheckIP (string& str) {
	int p1;
	int p2;
	int p3;
	int p4;

	if (str.length() > 15 || str.length() < 7) {
		//cout << "5";
		return false;
	}
	stringstream ss(str);
	try {
		CheckAllSymbols(str);
		CheckNextSymbol_N(ss);
		ss >> p1;
		CheckNextSymbol_D(ss);
		ss.ignore(1);
		CheckNextSymbol_N(ss);
		ss >> p2;
		CheckNextSymbol_D(ss);
		ss.ignore(1);
		CheckNextSymbol_N(ss);
		ss >> p3;
		CheckNextSymbol_D(ss);
		ss.ignore(1);
		CheckNextSymbol_N(ss);
		ss >> p4;
	}
	catch (exception& ex) {
		return false;
	}
	if (p1 > 255 || p2 > 255 || p3 > 255 || p4 > 255) {
		//cout << "6";
		return false;
	}
	//cout << p1 << "." << p2 << "." << p3 << "." << p4 << ".";
	return true;

}

int main() {
	string str;
	cin >> str;
	cout << CheckIP(str);


	return 0;
}
