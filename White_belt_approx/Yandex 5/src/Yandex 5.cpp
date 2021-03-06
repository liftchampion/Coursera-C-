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

/*
 * ������������ �� �����
 */

bool CheckAccordance(const string& prefix, const string& word, const set<string>& bad_words) {
	//cout << "				" << " Checking accordance between: " << prefix << " & " << word << endl;
	if (bad_words.count(word) == 1) {
		//cout << "				" << "No accordance - BAD_WORD" << endl;
		return false;
	}
	/*for (int i = 0; i < prefix.size(); ++i) {
		if (prefix[i] != word[i]) {
			//cout << "				" << "No accordance" << endl;
			return false;
		}
	}*/

	string temp_word = word;
	temp_word.erase(temp_word.begin() + prefix.size(), temp_word.end());
	if (prefix != temp_word) {
		return false;
	}

	//cout << "				" << "Yes accordance" << endl;
	return true;
}

int CountAccords(const string& prefix, const set<string>& dict, set<string>& bad_words) {
	//cout << "			" << "Counting Accords for prefix: " << prefix << endl;

	int accords = 0;
	for (const auto& word : dict) {
		//cout << "			" << "Checking word: " << word << endl;
		if (word.size() > prefix.size()) {
			if (CheckAccordance(prefix, word, bad_words)) {
				accords++;
				//cout << "			 " << "Accordance checked, now accords = " << accords << endl;
			}
			else {
				bad_words.insert(word);
			}
		}
		if (word.size() == prefix.size()) {
			if (word == prefix) {
				accords++;
			}
		}
	}

	//cout << "			 " << "Accords counted = " << accords << endl;
	return accords;
}

int CountKeysForWord(const string& word, const set<string>& dict) {
	/*
	 * ������������ ����� �� ��������+
	 * ������ ������ ���������+
	 * ���������� �� ����+
	 * 		����� ������ �� ����� ������� ��� ������������ ����������� ����� �� dict ��������������+
	 * ��������� ����� ���������� ��������������� ��������+
	 */
	//cout << "		" << "Counting keys for word: " << word << endl;
	if (dict.count(word) == 0) {
		//cout << "		" << "First meet this word: " << word << endl;
		//cout << "		" << "Keys for this word: " << word.size() << endl;
		return word.size();
	}

	vector<string> prefixes = WordToPrefixes(word);

	//cout << "		" << "Prefixes are: ";
	//PrintV(prefixes);
	//cout << endl;

	string good_prefix;
	set<string> bad_words;
	for (const auto& prefix : prefixes) {
		//cout << "		" << "Looking for a good prefix. Try: " << prefix << endl;
		good_prefix = prefix;
		if (CountAccords(prefix, dict, bad_words) == 1) {
			//cout << "		" << "Good prefix found: " << good_prefix << endl;
			break;
		}
	}

	//cout << "		" << "Keys for this word: " << good_prefix.size() << endl;
	return good_prefix.size();
}

int CountAllKeys(const vector<string>& words, set<string>& dict) {
	//cout << "Counting All Keys: " << endl;
	int num_keys = 0;
	for (const auto& word : words) {
		num_keys += CountKeysForWord(word, dict);
		dict.insert(word);

		//cout << "	" << "num_keys = " << num_keys << "  checked word is: " << word << endl;
		//cout << "	" << "new dict is: ";
		//PrintS(dict);
		//cout << endl;
	}
	return num_keys;
}


int main() {

	/*string test;
	cin >> test;
	//PrintV(WordToPrefixes(test));
	test.erase(test.begin() + 2, test.end());
	cout << test;*/


	int n;
	cin >> n;

	vector<string> words(n);
	for (auto& i : words) {
		cin >> i;
	}


	//cout << "words: ";
	//PrintV(words);
	//cout << endl;

	set<string> dict;
	//cout << "set created: ";
	//PrintS(dict);
	//cout << endl;

	cout << CountAllKeys(words, dict);

	/*
	 * ����������� �� ������
	 * 		����� �����
	 * 		num_keys += ������� ���������� ������� �������� CountKeysForWord
	 * 		��������� ����� � dict
	 */

	/*string word;
	cin >> word;
	WordToPrefixes(word);*/

	/*for (int i = 0; i < 10; i++) {
		cout << "i=" << i << "   ";
		for (int j = 0; j < 10; j++) {
			cout << "j=" << j << " ";
			if (j == 5) {
				;
			}
		}
		cout << endl;
	}*/

	return 0;
}
