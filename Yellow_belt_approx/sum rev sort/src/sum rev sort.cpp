#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	reverse(s.begin(), s.end());
	return s;
}

void Sort(vector<int>& v) {
	sort(v.begin(), v.end());
}
