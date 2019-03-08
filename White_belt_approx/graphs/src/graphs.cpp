/*
 * 3 1 1 2
 *
 *
 */

#include <vector>
#include <iostream>
#include <set>
using namespace std;

void PrintS(const set<int>& s) {
	for (const auto& i : s) {
		cout << i << " ";
	}
}

void PrintG(const vector<set<int>>& v) {
	for (int i = 1; i <= v.size(); i++ ) {
		cout << "Node: " << i << " linked with nodes: ";
		PrintS(v[i - 1]);
		cout << endl;
	}
}

int main() {
	int num_nods;
	int num_links;
	cin >> num_nods >> num_links;
	vector<vector<int>> graph(num_nods);

	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		graph[node1 - 1].push_back(node2);
		graph[node2 - 1].push_back(node1);
	}



	/*for (int i = 0; i < graph.size(); i++) {
		if (graph[i].size() == 0) {
			lonely.push_back(i + 1);
		}
	}
	if (lonely.size() > 2) {
		cout << -1;
	}
	else {
		part1.push_back(lonely[0]);
		part2.push_back(lonely[1]);
		graph.erase(graph.begin() + lonely[0] - 1);
		graph.erase(graph.begin() + lonely[0] - 1);
	}*/

	vector<int> part1;
	vector<int> part2;
	int num_lonely = 0;
	bool last_added_to_1 = false;
	bool left_1linked_node = true;
	while (graph.size() > 0) {
		vector<int> lonely;							//В первую очередь распределяем одиноких
		for (int i = 0; i < graph.size(); i++) {
			if (graph[i].size() == 0) {
				lonely.push_back(i + 1);
				num_lonely++;
			}
		}
		if (num_lonely > 2) {
			cout << -1;
			break;
		}
		else {
			bool added_to_1 = false;
			for (const auto& lonely_node : lonely) {
				if (added_to_1) {
					part2.push_back(lonely_node);
					graph.erase(graph.begin() + lonely_node - 1);
				}
				else {
					part1.push_back(lonely_node);
					graph.erase(graph.begin() + lonely_node - 1);
					added_to_1 = true;
				}
			}											//Распределили одиноких
		}

		if (left_1linked_node) {
			for (int i = 0; i < graph.size(); i++) {		//Распределим людей с 1 связью
				if (graph[i].size() == 1) {

					if (last_added_to_1) {
						part2.push_back(i+1);
						part2.push_back(graph[i][0]);
						last_added_to_1 = false;
						graph.erase(graph.begin() + i);
						graph.erase(graph.begin() + graph[i][0]);
						break;
					}
					else {
						part1.push_back(i+1);
						part1.push_back(graph[i][0]);
						last_added_to_1 = true;
						graph.erase(graph.begin() + i);
						graph.erase(graph.begin() + graph[i][0]);
						break;
					}
				}
			}
		}

	}

	cout << endl;
	//PrintG(graph);
	return 0;
}
