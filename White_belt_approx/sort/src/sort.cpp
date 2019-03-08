#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void PrintVector(const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> v;
	for (int i = 0; i < n; ++i) {
		int item;
		cin >> item;
		v.push_back(item);
	}
	sort(v.begin(), v.end(), [](int a1, int a2) {return (abs(a1) < abs(a2) );});
	PrintVector(v);
	return 0;
}
