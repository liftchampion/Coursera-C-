#include <string>
#include <iostream>
#include <vector>
using namespace std;

bool IsPalindrom (string str) {
	for (int i = 0; i < str.size()/2; ++i) {
		if (str[i] == str[str.size() - 1 - i]) {
		}
		else {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter (vector<string> words, int minLenght) {
	vector<string> result;
	for (auto i : words) {
		if (i.size() >= minLenght && IsPalindrom(i) == true) {
			result.push_back(i);
		}
	}
	return result;
}
