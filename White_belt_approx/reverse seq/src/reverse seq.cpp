#include <vector>
#include <iostream>
using namespace std;

void swap (int& a, int& b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}
void Reverse (vector<int>& s) {
	for (int i = 0; i < s.size() / 2; ++i) {
		swap(s[i], s[s.size() - 1 - i]);
	}
}
