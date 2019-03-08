/*
 * 4 2 Marushkino Kokoshkino 1 Kokoshkino 2 Marushkino Kokoshkino 2 Kokoshkino Marushkino
 *
 */


//#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
using namespace std;

/*void PrintMap(const map<set<string>, int>& m) {
	for (auto i : m) {
		for (auto j : i.first) {
			cout << j << " ";
		}
		cout << i.second << endl;
	}
}*/

int main() {
	map<set<string>, int> stops_to_routes;
	int q;
	cin >> q;
	int n = 1;

	for(int i = 0; i < q; ++i) {
		int m;
		cin >> m;
		set<string> one_route;
		for (int j = 0; j < m; ++j) {
			string stop;
			cin >> stop;
			one_route.insert(stop);
		}
		int exist = 0;
		for (const auto& c : stops_to_routes) {
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
