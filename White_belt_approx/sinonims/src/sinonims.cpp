/*
 * 7 ADD 1 2 ADD 2 3 ADD 1 4 COUNT six ADD one two ADD two five COUNT 1
 *
 */

#include <set>
#include <string>
#include <iostream>
#include <map>
using namespace std;

void PrintSins(const map<string, set<string>>& sins) {
	for (const auto& i : sins) {
		cout << i.first << " : ";
		for (const auto& j : i.second) {
			cout << j << " ";
		}
		cout << endl;
	}
}

void Check (map<string, set<string>>& sins) {
	string word1;
	string word2;
	cin >> word1 >> word2;
	if (sins.count(word1) == 0 || sins.count(word2) == 0) {
		cout << "NO" << endl;
	}
	else if (sins[word1].count(word2) == 1 || sins[word2].count(word1) == 1) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

}

void Count(map<string, set<string>>& sins) {
	string word;
	int n = 0;
	cin >> word;
	n = sins.count(word);
	if (n == 0) {
		cout << n << endl;
	}
	else {
		n = sins[word].size();
		cout << n << endl;
	}
}

void Add(map<string, set<string>>& sinonim_groups) {
	string word1;
	string word2;
	cin >> word1 >> word2;
	//sinonim_groups[word1];
	sinonim_groups[word1].insert(word2);
	//sinonim_groups[word2];
	sinonim_groups[word2].insert(word1);
}

int main() {
	map<string, set<string>> sinonim_groups;
	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "ADD") {
			Add(sinonim_groups);
		}
		if (command == "COUNT") {
			Count(sinonim_groups);
		}
		if (command == "CHECK") {
			Check(sinonim_groups);
		}
		/*if (command == "STOPS_FOR_BUS") {
			StopsForBus(routes, sequence);
		}*/
	}
		//PrintSins(sinonim_groups);
	return 0;
}
