#include <string>
#include <vector>
#include <iostream>
using namespace std;

void PrintVector (vector<string> v) {
	int j = 0;
	for (auto i : v) {
		cout << j << ": " << i << endl;
		j++;
	}
}

string VectorToString (const vector<string>& v) {
	string str;
	for (auto i : v) {
		if (i >= "!") {
			str += i;
			//str += " ";
		}
	}
	return str;
}

int DealsCount (const vector<string>& month, int day) {
	int n = 0;
	for (auto i : month[day - 1]) {
		if (i == ' ') {
			n++;
		}
	}
	return n;
}

void Add (vector<string>& month, const int& date, const string& bussines) {
	month[date - 1] += bussines + " ";
}

void Next (vector<string>& month, const vector<int>& days_in_months, int& current_month) {
	int days_next;
	int days_this = days_in_months[current_month - 1];
	if (current_month != 12) {
		days_next = days_in_months[current_month];
		current_month++;
	}
	else {
		days_next = 31;
		current_month = 1;
	}
	if (days_next >= days_this) {
		month.resize(days_next);
	}
	else {
		vector<string> tmp;
		for ( int i = days_next - 1; i < days_this; ++i) {
			tmp.push_back(month[i]);
		}
		month.resize(days_next);
		month[days_next - 1] = VectorToString(tmp);
	}
}

void Dump (const vector<string>& month, int day) {
	cout << DealsCount(month, day) << " " << month[day - 1] << endl;
}

int main() {
	vector<string> month(31);
	vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int current_month = 1;

	int q;
	cin >> q;

	for(int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "ADD") {
			int date;
			string deal;
			cin >> date >> deal;
			Add(month, date, deal);
		}
		if (command == "NEXT") {
			Next(month, days_in_months, current_month);
		}
		if (command == "DUMP") {
			int d;
			cin >> d;
				Dump(month, d);
		}
	}
	//PrintVector(month);

	return 0;
}
