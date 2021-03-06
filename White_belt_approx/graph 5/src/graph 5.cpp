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
	int group;
	int chet;
};

void PrintVector(const vector<int>& v) {
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

void EraseByValue(vector<short int>& v, int val) {
	for (short int i = 0; i < v.size(); i++) {
		if (v[i] == val) {
			v.erase(v.begin() + i);
			break;
		}
	}
}

void InvertGraph (vector<GraphItem>& graph) {
	for (short int j = 0; j < graph.size(); j++) {
		for (short int i = 1; i <= graph.size(); i++) {
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
	for (short int i = 0; i < num_nods; i++) {
		all_links[i] = i + 1;
	}
	for (short int i = 0; i < num_nods; i++) {
		graph[i].links = all_links;
	}
	for (short int i = 0; i < num_nods; i++) {
		graph[i].links.erase(graph[i].links.begin() + i);
	}
	for (short int i = 0; i < num_links; i++) {
		short int node1;
		short int node2;
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

int MarkComps (vector<GraphItem>& graph) {
	bool ready_all = false;
	int group = 1;
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

void MarkChetForGroup (vector<GraphItem>& graph, int start, int previous_chet, int prev_start) {
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

void MarkChet(vector<GraphItem>& graph, int last_group) { //����� ��������, ����� �� ��������� ����� ������
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

void MakeParts(const vector<GraphItem>& graph, vector<int>& part1, vector<int>& part2) {
	for (short int i = 0; i < graph.size(); i++) {
		if (graph[i].chet == 0) {
			part1.push_back(i + 1);
		}
		else {
			part2.push_back(i + 1);
		}
	}
}

int main() {
	/*vector<GraphItem> graph = ReadGraph();
	cout << "reading done" << endl;
	InvertGraph(graph);*/
	try {
	short int last_group;

	vector<GraphItem> graph = ReadInvertedGraph();
	PrintGraph(graph);
	cout << "inverted" << endl;
	last_group = MarkComps(graph);
	cout << "comps marked" << endl;
	try {
		MarkChet(graph, last_group);
	}
	catch (exception& ex) {
		cout << -1;
		return 0;
	}
	PrintGraph(graph);
	cout << endl;
	cout << last_group;

	vector<int> part1;
	vector<int> part2;
	MakeParts(graph, part1, part2);
	cout << part1.size();
	cout << endl;
	PrintVector(part1);
	cout << endl;
	PrintVector(part2);
	}
	catch (exception& ex) {
		cout << -1;
		return 0;
	}

	return 0;
}
