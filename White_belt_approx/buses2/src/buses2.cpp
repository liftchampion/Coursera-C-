/*
 * 4 2 Marushkino Kokoshkino 1 Kokoshkino 2 Marushkino Kokoshkino 2 Kokoshkino Marushkino
 *
 */


#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;

void PrintMap(const map<vector<string>, int>& m) {
	for (auto i : m) {
		for (auto j : i.first) {
			cout << j << " ";
		}
		cout << i.second << endl;
	}
}

int main() {
	map<vector<string>, int> stops_to_routes;
	int q;
	cin >> q;
	int n = 1;

	for(int i = 0; i < q; ++i) {
		int m;
		cin >> m;
		vector<string> one_route;
		for (int j = 0; j < m; ++j) {
			string stop;
			cin >> stop;
			one_route.push_back(stop);
		}
		int exist = 0;
		for (auto c : stops_to_routes) {
			if (c.first == one_route) {
				exist = c.second;
			}
		}
		if (exist == 0) {
			stops_to_routes[one_route] = n;
			cout << "New bus " << n << endl;
			n++;
		}
		if (exist != 0) {
			cout << "Already exists for " << exist << endl;
		}
	}
	//PrintMap(stops_to_routes);


	return 0;
}
