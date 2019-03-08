/*
 * 3 1 1 2
 * 8 5 2 4 4 3 7 6 6 8 8 7
 *
 */

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

struct GraphItem {
	GraphItem () {
		used = false;
		group = 0;
		chet = -1;
	}
	vector<short int> links;
	bool used;
	short int group;
	short int chet;
};

void PrintVector(const vector<short int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

void PrintGraph (const vector<GraphItem>& graph) {
	for (int i = 0; i < graph.size(); i++) {
		cout << "Node: " << i+1 << " [chet=" << graph[i].chet << "]<group="
				<< graph[i].group << ">{used=" << graph[i].used << "} LinkedWith: ";
		for (const auto& l : graph[i].links) {
			cout << l << " ";
		}
		cout << endl;
	}
}

void EraseByValue(vector<short int>& v, short int val) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val) {
			v.erase(v.begin() + i);
			break;
		}
	}
}

void InvertGraph (vector<GraphItem>& graph) {
	for (int j = 0; j < graph.size(); j++) {
		for (int i = 1; i <= graph.size(); i++) {
			if (j != i-1) {
				if (count(graph[j].links.begin(), graph[j].links.end(), i) == 0) {
					graph[j].links.push_back(i);
				}
				else {
					EraseByValue(graph[j].links, i);
				}
			}
		}
	}
}

vector<GraphItem> ReadInvertedGraph () {
	short int num_nods;
	short int num_links;
	cin >> num_nods >> num_links;
	vector<GraphItem> graph(num_nods);
	vector<short int> all_links(num_nods);
	for (int i = 0; i < num_nods; i++) {
		all_links[i] = i + 1;
	}
	for (int i = 0; i < num_nods; i++) {
		graph[i].links = all_links;
	}
	for (int i = 0; i < num_nods; i++) {
		graph[i].links.erase(graph[i].links.begin() + i);
	}
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		/*graph[node1 - 1].links.erase(graph[node1 - 1].links.begin());
		graph[node2 - 1].links.erase(graph[node2 - 1].links.begin());*/
		EraseByValue(graph[node1 - 1].links, node2);
		EraseByValue(graph[node2 - 1].links, node1);
	}
	return graph;
}

vector<GraphItem> ReadGraph() {
	short int num_nods;
	short int num_links;
	cin >> num_nods >> num_links;
	vector<GraphItem> graph(num_nods);
	/*for (int i = 0; i < num_nods; i++) {
		graph[i];
	}*/
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		graph[node1 - 1].links.push_back(node2);
		graph[node2 - 1].links.push_back(node1);
	}
	return graph;
}

short int MarkComps (vector<GraphItem>& graph) {
	bool ready_all = false;
	short int group = 1;
	while (!ready_all) {
		bool ready = false;
		ready_all = true;
		for (auto& item : graph) {
			if (item.group == 0) {
				item.group = group;
				ready_all = false;
				break;
			}
		}
		while (!ready) {
			ready = true;
			for (auto& item : graph) {
				if (item.group == group && item.used == false) {
					for (const auto& link : item.links) {
						graph[link-1].group = group;
					}
					ready = false;
					item.used = true;
				}
			}
		}
		group++;
	}
	return group - 2;
}

void MarkChetForGroup (vector<GraphItem>& graph, short int start, short int previous_chet, short int prev_start) {
	short int this_chet;
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
			if (new_start - 1 != prev_start && graph[new_start - 1].used == true) {
				MarkChetForGroup(graph, new_start - 1, this_chet, start);
			}
		}
		else {
			if (new_start - 1 != prev_start) {
				graph[start].used = false;
				MarkChetForGroup(graph, new_start - 1, this_chet, start);
			}
		}
	}
}

void MarkChet(vector<GraphItem>& graph, short int last_group) { //Можно улучшить, чтобы не проходить вечно заново
	short int start;
	short int current_group = 1;
	while (current_group <= last_group) {
		for (int j = 0; j < graph.size(); j++) {
			if (graph[j].group == current_group) {
				start = j;
				MarkChetForGroup(graph, start, 1, -1);
				current_group++;
			}
		}
	}
}

void MakeParts(const vector<GraphItem>& graph, vector<short int>& part1, vector<short int>& part2) {
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].chet == 0) {
			part1.push_back(i + 1);
		}
		else {
			part2.push_back(i + 1);
		}
	}
	if (part2.size() == 0) {
		part2.push_back(part1[0]);
		part1.erase(part1.begin());
	}
}

int main() {
	/*vector<GraphItem> graph = ReadGraph();
	cout << "reading done" << endl;
	InvertGraph(graph);*/

	short int last_group;

	vector<GraphItem> graph = ReadInvertedGraph();
	//PrintGraph(graph);
	//cout << "inverted" << endl;
	last_group = MarkComps(graph);
	//cout << "comps marked" << endl;
	try {
		MarkChet(graph, last_group);
	}
	catch (exception& ex) {
		cout << -1;
		return 0;
	}
	/*PrintGraph(graph);
	cout << endl;
	cout << last_group;*/

	vector<short int> part1;
	vector<short int> part2;
	MakeParts(graph, part1, part2);
	cout << part1.size();
	cout << endl;
	PrintVector(part1);
	cout << endl;
	PrintVector(part2);



	return 0;
}
