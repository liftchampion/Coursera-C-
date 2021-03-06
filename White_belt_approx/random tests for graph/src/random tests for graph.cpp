#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include <map>
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

vector<GraphItem> ReadInvertedGraph (stringstream& stream) {
	short int num_nods;
	short int num_links;
	stream >> num_nods >> num_links;
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
		stream >> node1 >> node2;
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

int TaskGraph(stringstream& stream) {
	short int last_group;

	vector<GraphItem> graph = ReadInvertedGraph(stream);
	//PrintGraph(graph);
	//cout << "inverted" << endl;
	last_group = MarkComps(graph);
	//cout << "comps marked" << endl;
	try {
		MarkChet(graph, last_group);
	}
	catch (exception& ex) {
		cout << "     + ( " << -1 << " )" << endl;
		return 0;
		//cout << -1;
	}
	/*PrintGraph(graph);
	cout << endl;
	cout << last_group;*/

	vector<int> part1;
	vector<int> part2;
	MakeParts(graph, part1, part2);
	cout << "     + ( " << part1.size() << " )" << " ( " << part2.size() << " )" << endl;
	return 0;
	//cout << endl;
	//PrintVector(part1);
	//cout << endl;
	//PrintVector(part2);
}

void PrintLinks(const vector<string>& links) {
	for (const auto& item : links) {
		cout << item << endl;
	}
}

void AddLinks(vector<string> links, vector<string>& links_strings, int num_links, int deep, string str) {
	deep++;
	//cout << "in AddLinks, deep= " << deep << endl;
	if (deep > num_links) {
		links_strings.push_back(str);
	}
	else {
		for (int i = 0; i < links.size(); i++) {
			string str_copy = str;
			//cout << "updating string: " << str_copy << endl;
			str_copy.append(" " + links[i]);
			//cout << "added: " << links[i] + " " << endl;
			vector<string> links_copy = links;
			links_copy.erase(links_copy.begin() + i);
			//cout << "links for further operations looks like: <" << endl;
			//PrintLinks(links_copy);
			//cout << ">" << endl;
			//cout << "going to new iteration with deep=" << deep + 1 << " and string=" << str_copy << endl;
			AddLinks(links_copy, links_strings, num_links, deep, str_copy);
		}
	}
}

int main() {

	vector<string> links;
	int NUM_NODS = 10;
	int NUM_NODS_START = 6;
	int NUM_LINKS_START = 7;

	/*for (int i = 1; i <= NUM_NODS; i++) {
		for (int j = i; j <= NUM_NODS; j++) {
			if (i != j) {
				links.push_back(to_string(i) + " " + to_string(j));
			}
		}
	}
	PrintLinks(links);
	int NUM_LINKS = links.size();
	cout << endl;
	vector<string> links_strings;
	int deep = 0;
	string str;
	AddLinks(links, links_strings, NUM_LINKS, deep, str);
	cout << endl;
	PrintLinks(links_strings);*/


	for (int num_nods = NUM_NODS_START; num_nods <= NUM_NODS; num_nods++) {
		vector<string> links;
		for (int i = 1; i <= num_nods; i++) {
			for (int j = i; j <= num_nods; j++) {
				if (i != j) {
					links.push_back(to_string(i) + " " + to_string(j));
				}
			}
		}
		int NUM_LINKS = links.size();
		for (int num_links = NUM_LINKS_START; num_links <= NUM_LINKS; num_links++) {
			string input_str;
			input_str.append(to_string(num_nods) + " " + to_string(num_links));
			//cout << input_str << endl;

			vector<string> links_strings;
			int deep = 0;
			string str;
			AddLinks(links, links_strings, num_links, deep, str);
			for (const auto& item : links_strings) {
				string input_str_copy = input_str;
				input_str_copy.append(item);
				stringstream ss(input_str_copy);
				cout << input_str_copy;
				TaskGraph(ss);
			}

		}
	}
	return 0;
}
