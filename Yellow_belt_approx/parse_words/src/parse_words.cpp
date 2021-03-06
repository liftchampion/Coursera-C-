#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
using namespace std;

template <typename T>
string ConstuctWord(T begin, const T end) {
	string word;
	for (auto it = begin; it != end; it++) {
		word.push_back(*it);

	}
	//cout << "word <" << word << ">" << endl;
	return word;
}

vector<string> SplitIntoWords(const string& s) {
	vector<string> words;
	auto word_begin = s.begin();
	auto word_end = s.begin();
	auto space_it = s.begin();
	while (space_it != s.end()) {
		space_it = find(word_begin, s.end(), ' ');
		word_end = space_it;

		//cout << "begin <" << *word_begin << ">" << endl;
		//cout << "end <" << *word_end << ">" << endl;

		string new_word = ConstuctWord(word_begin, word_end);
		words.push_back(new_word);
		word_begin = ++word_end;
	}


	return words;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
