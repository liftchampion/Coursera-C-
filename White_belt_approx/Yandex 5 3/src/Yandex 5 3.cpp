/*
 *
 * 5 aaaaa aaaab aaaaa abaaa abaaa
 * 22  - 22
 *
 * 3 hello world hello
 * 11  - 11
 *
 * 5 an apple a big apple
 * 13   - 13
 */

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

void PrintV(const vector<string>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}
void PrintS(const set<string>& s) {
	for (const auto& i : s) {
		cout << i << " ";
	}
}




int main() {
	int n;
	cin >> n;
	int total_amount = 0;
	map<string, string> prefix_to_word;
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		//total_amount += CountKeysForWord(word, prefix_to_words);
	}
	cout << total_amount;

		//cout << "words: ";
		//PrintV(words);
		//cout << endl;

		//cout << "set created: ";
		//PrintS(dict);
		//cout << endl;



	return 0;
}
