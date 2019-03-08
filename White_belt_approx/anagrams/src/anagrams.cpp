#include <map>
#include <string>
#include <iostream>
using namespace std;

map<char, int> BuildCharCounters(const string& word) {
	map<char, int> spelling;
	for (auto c : word) {
		spelling[c]++;
	}

	return spelling;
}
int main() {
	int q;
	string word1, word2;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> word1 >> word2;
		if (BuildCharCounters(word1) == BuildCharCounters(word2)) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
