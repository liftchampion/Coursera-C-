/*
 * 3 1 1 2
 * 8 5 2 4 4 3 7 6 6 8 8 7
 *
 */

#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

struct GraphItem {
	GraphItem () {
		used = false;
		group = 0;
		chet = -1;
	}
	set<int> links;
	bool used;
	int group;
	int chet;
};

void PrintVector(const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

void PrintGraph (const map<int, GraphItem>& graph) {
	for (const auto& item : graph) {
		cout << "Node: " << item.first << " [chet=" << item.second.chet << "]<group="
				<< item.second.group << "> LinkedWith: ";
		for (const auto& l : item.second.links) {
			cout << l << " ";
		}
		cout << endl;
	}
}

void InvertGraph (map<int, GraphItem>& graph) {
	for (auto& item : graph) {
		for (int i = 1; i <=graph.size(); i++) {
			if (i != item.first) {
				if (item.second.links.count(i) == 0) {
					item.second.links.insert(i);
				}
				else {
					item.second.links.erase(i);
				}
			}
		}
	}
}

map<int, GraphItem> ReadGraph() {
	int num_nods;
	int num_links;
	cin >> num_nods >> num_links;
	map<int, GraphItem> graph;
	for (int i = 1; i <= num_nods; i++) {
		graph[i];
	}
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		graph[node1].links.insert(node2);
		graph[node2].links.insert(node1);
	}
	return graph;
}

int MarkComps (map<int, GraphItem>& graph) {
	bool ready_all = false;
	int group = 1;
	while (!ready_all) {
		bool ready = false;
		ready_all = true;
		for (auto& item : graph) {
			if (item.second.group == 0) {
				item.second.group = group;
				ready_all = false;
				break;
			}
		}
		while (!ready) {
			ready = true;
			for (auto& item : graph) {
				if (item.second.group == group && item.second.used == false) {
					for (const auto& link : item.second.links) {
						graph[link].group = group;
					}
					ready = false;
					item.second.used = true;
				}
			}
		}
		group++;
	}
	return group - 2;
}

void MarkChetForGroup (map<int, GraphItem>& graph, int start, int previous_chet, int prev_start) {
	int this_chet;
	if (previous_chet == 1) {
		if (graph[start].chet == 1) {
			throw exception();
		}
		graph[start].chet = 0;
		this_chet = 0;
	}
	else {
		if (graph[start].chet == 0) {
			throw exception();
		}
		graph[start].chet = 1;
		this_chet = 1;
	}
	for (const auto& new_start : graph[start].links) {
		if (graph[start].used == false) {
			if (new_start != prev_start && graph[new_start].used == true) {
				MarkChetForGroup(graph, new_start, this_chet, start);
			}
		}
		else {
			graph[start].used = false;
			if (new_start != prev_start) {
				MarkChetForGroup(graph, new_start, this_chet, start);
			}
		}
	}
}

void MarkChet(map<int, GraphItem>& graph, int last_group) { //Можно улучшить, чтобы не проходить вечно заново
	int start;
	for (int i = 1; i <= last_group; i++) {
		for (const auto& item : graph) {
			if (item.second.group == i) {
				start = item.first;
				break;
			}
		}
		MarkChetForGroup(graph, start, 1, 0);
	}
}

void MakeParts(const map<int, GraphItem>& graph, vector<int>& part1, vector<int>& part2) {
	for (const auto& item : graph) {
		if (item.second.chet == 0) {
			part1.push_back(item.first);
		}
		else {
			part2.push_back(item.first);
		}
	}
}

int main() {
	map<int, GraphItem> graph = ReadGraph();
	int last_group;
	InvertGraph(graph);
	last_group = MarkComps(graph);
	try {
		MarkChet(graph, last_group);
	}
	catch (exception& ex) {
		cout << -1;
		return 0;
	}
	//PrintGraph(graph);
	//cout << endl;
	//cout << last_group;

	vector<int> part1;
	vector<int> part2;
	MakeParts(graph, part1, part2);
	cout << part1.size();
	cout << endl;
	PrintVector(part1);
	cout << endl;
	PrintVector(part2);

	return 0;
}
