//============================================================================
// Name        : avg.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <iostream>
#include <cstdint>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> temps(n);
	for (auto& item : temps) {
		cin >> item;
	}
	int64_t avg = 0;
	for (auto& item : temps) {
		avg += item;
	}
	avg /= static_cast<int>(temps.size());
	int count_more_avg = 0;
	for (auto& item : temps) {
		if (item > avg) {
			count_more_avg++;
		}
	}
	cout << count_more_avg << endl;
	for (int i = 0; i < static_cast<int>(temps.size()); i++) {
		if (temps[i] > avg) {
			cout << i << " ";
		}
	}
	return 0;
}
