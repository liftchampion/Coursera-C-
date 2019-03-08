/*
 * 3 1 1 2
 *
 *
 */

#include <vector>
#include <iostream>
#include <set>
using namespace std;

void PrintVector(const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

void PrintGraph(const vector<vector<int>>& v) {
	for (int i = 1; i <= v.size(); i++ ) {
		cout << "Node: " << i << " linked with nodes: ";
		PrintVector(v[i - 1]);
		cout << endl;
	}
}

void ReadGraph (vector<vector<int>>& graph, int num_links) {
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		graph[node1 - 1].push_back(node2);
		graph[node2 - 1].push_back(node1);
	}
}

int main() {
	int num_nods;
	int num_links;
	cin >> num_nods >> num_links;
	vector<vector<int>> graph(num_nods);
	ReadGraph(graph, num_links);
	PrintGraph(graph);
	return 0;
}
