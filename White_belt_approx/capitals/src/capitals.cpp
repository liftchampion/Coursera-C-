/*
 * 4 CHANGE_CAPITAL USSR MSK CHANGE_CAPITAL USSR SPB RENAME USSR RUSSIA ABOUT RUSSIA
 * */


#include <map>
#include <string>
#include <iostream>
using namespace std;

void PrintMap (const map<string, string>& list) {
	for (auto i : list) {
		cout << i.first << ": " << i.second << endl;
	}
}

void ChangeCapital (map<string, string>& list, const string& country, const string& new_capital) {
	int output_case = 1;
	for (auto i : list) {
		if (i.first == country) {
			if (i.second == new_capital) {
				output_case = 2;
				break;
			}
			else {
				output_case = 3;
				break;
			}
		}
	}
	if (output_case == 1) {
		cout << "Introduce new country " << country << " with capital " << new_capital << endl;
	}
	if (output_case == 2) {
		cout << "Country " << country << " hasn't changed its capital" << endl;
	}
	if (output_case == 3) {
		cout << "Country " << country << " has changed its capital from " << list[country] <<
				" to " << new_capital << endl;
	}

	list[country] = new_capital;

}

int Rename (map<string, string>& list, const string& old_country, const string& new_country) {

	if (old_country == new_country) {
		cout << "Incorrect rename, skip" << endl;
		return 0;
	}

	bool exist_old = false;
	bool exist_new = false;
	for (auto i : list) {
		if (i.first == old_country) {
			exist_old = true;
		}
		if (i.first == new_country) {
			exist_new = true;
		}
	}

	if (exist_new == true || exist_old == false) {
		cout << "Incorrect rename, skip" << endl;
		return 0;
	}

	list[new_country] = list[old_country];
	list.erase(old_country);
	cout << "Country " << old_country << " with capital " << list[new_country] <<
			" has been renamed to " << new_country << endl;

	return 0;
}

int About(map<string, string>& list, const string& country) {
	bool exist = false;
	for (auto i : list) {
		if (i.first == country) {
			exist = true;
			break;
		}
	}
	if (exist == false) {
		cout << "Country " << country << " doesn't exist" << endl;
		return 0;
	}

	cout << "Country " << country << " has capital " << list[country] << endl;
	return 0;
}

int Dump(const map<string, string>& list) {
	if (list.size() == 0) {
		cout << "There are no countries in the world" << endl;
		return 0;
	}
	for (auto i : list) {
		cout << i.first << "/" << i.second << " ";
	}
	return 0;
}

int main() {
	map<string, string> list;
	int q;
	cin >> q;

	for(int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			string country;
			string capital;
			cin >> country >> capital;
			ChangeCapital(list, country, capital);
		}
		if (command == "RENAME") {
			string old_country;
			string new_country;
			cin >> old_country >> new_country;
			Rename(list, old_country, new_country);
		}
		if (command == "ABOUT") {
			string country;
			cin >> country;
			About(list, country);
		}
		if (command == "DUMP") {
			Dump(list);
		}
	}

	//PrintMap(list);

	return 0;
}
