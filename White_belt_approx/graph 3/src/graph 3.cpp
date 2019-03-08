/*
 * 3 1 1 2
 *
 *	5 5
1 3
1 4
1 5
5 3
5 4
 */

#include <vector>
#include <iostream>
#include <set>
#include <map>
using namespace std;

void PrintVector(const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

void PrintGraph(map<int, vector<int>>& v) {
	for (int i = 0; i < v.size(); i++ ) {
		cout << "Node: " << i << " linked with nodes: ";
		PrintVector(v[i]);
		cout << endl;
	}
}

void PrintMap (const map<int, bool>& map) {
	for (const auto& i : map) {
		cout << i.first << "<" << i.second << "> ";
	}
}

void ReadGraph (map<int, vector<int>>& graph, int num_links) {
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}
}

void PrintComps (const vector<map<int, vector<int>>>& c) {
	for (const auto& i: c) {
		for (const auto& j : i) {
			cout << j.first << " -( ";
			for (const auto& k : j.second) {
				cout << k << " ";
			}
			cout << ")  ";
		}
		cout << endl;
	}
}

void EraseByValue (vector<int>& v, int value) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == value) {
			v.erase(v.begin() + i);
			break;
		}
	}
}

void GetComponentNodes (map<int, bool>& component, map<int, vector<int>>& graph) { //По дефолту в сете одна точка,
																			 //первая из оставшихся в графе (в векторе номеров точек графа)
	bool ready = false;
	while (!ready) {
		map<int, bool> new_nodes;
		for (auto& node : component) {
			if (node.second == false) {
				for (const auto& link : graph[node.first]) {
					if (component.count(link) == 0) {
						new_nodes.insert({link, false});
					}
				}
				node.second = true;
			}
		}
		if (new_nodes.size() == 0) {
			ready = true;
		}
		component.insert(new_nodes.begin(), new_nodes.end());
	}

}

void UpdateNodesLeft (map<int, bool>& nodes_left, const map<int, bool>& nodes_used) {
	for (const auto& node : nodes_used) {
		nodes_left[node.first] = true;
	}
}

map<int, vector<int>> NodesToGraph (const map<int, bool>& nodes, map<int, vector<int>>& graph) {
	map<int, vector<int>> new_graph;
	for (const auto& node : nodes) {
		new_graph[node.first] = graph[node.first];
	}
	return new_graph;
}

vector<map<int, vector<int>>> GetConnectedComponents (map<int, vector<int>>& graph) {
	vector<map<int, vector<int>>> connected_components;
	map<int, bool> nodes_left;
	int num_of_comp = 0;
	for (int i = 0; i < graph.size(); i++) {
		nodes_left[i] = false;
	}
	for (auto& node : nodes_left) {
		map<int, bool> component;
		if (node.second == false) {
			component[node.first] = false;
			GetComponentNodes(component, graph);
			UpdateNodesLeft(nodes_left, component);
			connected_components[num_of_comp] = NodesToGraph(component, graph);
		}
	}
	return connected_components;
}

map<int, vector<int>> ReadInvertedGraph (int num_nods, int num_links) {
	map<int, vector<int>> graph;
	for (int i = 0; i < num_nods; i++) {
		for (int j = 0; j < num_nods; j++) {
			if (j != i) {
				graph[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < num_links; i++) {
		int node1;
		int node2;
		cin >> node1 >> node2;
		EraseByValue(graph[node1 - 1], node2 - 1);
		EraseByValue(graph[node2 - 1], node1 - 1);
	}
	return graph;
}

int main() {
	int num_nods;
	int num_links;
	cin >> num_nods >> num_links;
	map<int, vector<int>> graph;
	//graph = ReadInvertedGraph(num_nods, num_links);
	ReadGraph(graph, num_links);
	PrintGraph(graph);
	cout << endl;

	vector<map<int, vector<int>>> connected_comps = GetConnectedComponents(graph);
	PrintComps(connected_comps);


	/*map<int, bool> component;
	component.insert({0,false});
	GetComponentNodes(component, graph);
	PrintMap(component);*/
	return 0;
}
