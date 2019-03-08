#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> set;
	for (auto i : m) {
		set.insert(i.second);
	}
	return set;
}

