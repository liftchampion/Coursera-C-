/*
 * 		7 NEW_BUS 2 3 North Town_hall South NEW_BUS 1 3 Town_hall Butovo Village NEW_BUS 1K 2 Town_hall Butovo ALL_BUSES BUSES_FOR_STOP Town_hall STOPS_FOR_BUS 1 STOPS_FOR_BUS 10
 *
 *
 * */



#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int AllBuses (const map<string, vector<string>>& routes) {
	if (routes.size() == 0) {
		cout << "No buses" << endl;
		return 0;
	}
	for (auto i : routes) {
		cout << "Bus " << i.first << ":";
		for (auto j : i.second) {
			cout << " " << j;
		}
		cout << endl;
	}
	return 0;
}

void NewBus (map<string, vector<string>>& routes, vector<string>& sequence) {
	int n_stops;
	string name;
	cin >> name >> n_stops;
	sequence.push_back(name);
	for (int i = 0; i < n_stops; ++i) {
		string stop;
		cin >> stop;
		routes[name].push_back(stop);
	}
}

vector<string> BusesForStop (map<string, vector<string>>& routes, const vector<string>& sequence, const string& stop, const bool print) {
	vector<string> buses_for_stop;
	bool exist = false;
	for (auto i : routes) {
		for (auto j : i.second) {
			if (j == stop) {
				exist = true;
				break;
			}
		}
	}
	if (exist == false) {
		if (print == true) {
			cout << "No stop" << endl;
		}
		return buses_for_stop;
	}

	for (auto k : sequence) {
		for (auto s : routes[k]) {
			if (s == stop) {
				if (print == true) {
					cout << k << " ";
				}
				buses_for_stop.push_back(k);
			}
		}
	}
	if (print == true) {
		cout << endl;
	}
	return buses_for_stop;
}

int StopsForBus (map<string, vector<string>>& routes, const vector<string>& sequence) {
	string bus;
	cin >> bus;
	bool exist = false;
	for (auto i : routes) {
		if (i.first == bus) {
			exist = true;
			break;
		}
	}
	if (exist == false) {
		cout << "No bus" << endl;
		return 0;
	}

	for (auto i : routes[bus]) {
		cout << "Stop " << i << ":";
		vector<string> buses_for_stop;
		buses_for_stop = BusesForStop(routes, sequence, i, false);
		for (auto j : buses_for_stop) {
			if (j != bus) {
				cout << " " << j;
			}
		}
		if (buses_for_stop.size() == 1) {
			cout << " no interchange";
		}
		cout << endl;
	}
	return 0;
}

int main() {
	map<string, vector<string>> routes;
	vector<string> sequence;
	int q;
	cin >> q;

	for(int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "NEW_BUS") {
			NewBus(routes, sequence);
		}
		if (command == "ALL_BUSES") {
			AllBuses(routes);
		}
		if (command == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;
			BusesForStop(routes, sequence, stop, true);
		}
		if (command == "STOPS_FOR_BUS") {
			StopsForBus(routes, sequence);
		}
	}
	return 0;
}
