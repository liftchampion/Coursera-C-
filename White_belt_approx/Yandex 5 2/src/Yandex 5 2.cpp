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

vector<string> WordToPrefixes (const string& word) {		// +++
	//cout << "			Getting prefixes" << endl;

	vector<string> prefixes;
	string previus_prefix;
	/*for (const auto& letter : word) {
		prefixes.push_back(previus_prefix + letter);
		previus_prefix += letter;
	}*/
	for (int i = 0; i < word.size(); i++) {
			prefixes.push_back(previus_prefix + word[i]);
			previus_prefix += word[i];
	}
	//PrintV(prefixes);

	//cout << "			Prefixes got" << endl;
	return prefixes;
}

int CountKeysForWord (const string& word, map<string, set<string>>& prefix_to_words) {
	vector<string> word_prefixes = WordToPrefixes(word);
	string good_prefix = word;
	for (const string& prefix : word_prefixes) {
		set<string>& prefix_set = prefix_to_words[prefix];
		if (prefix_set.size() == 1) {
			if (prefix_set.count(word) == 1) {
				good_prefix = prefix;
				break;
			}
		}
		prefix_set.insert(word);
	}

	return good_prefix.size();
}

int CountKeysForAll (const vector<string>& words, map<string, set<string>>& prefix_to_words) {
	int total_amount = 0;
	for (const string& word : words) {
		total_amount += CountKeysForWord(word, prefix_to_words);
	}
	return total_amount;
}

int main() {
	int n;
	cin >> n;
	int total_amount = 0;
	map<string, set<string>> prefix_to_words;
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		total_amount += CountKeysForWord(word, prefix_to_words);
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
