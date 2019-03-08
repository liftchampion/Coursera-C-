#include <string>
#include <iostream>
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
