#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> CreateVector(int n) {
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = n - i;
	}
	return v;
}

void PrintVector(const vector<int> v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

void PrintPermutations(vector<int>& v) {
	PrintVector(v);
	while(prev_permutation(begin(v), end(v))) {
		cout << endl;
		PrintVector(v);
	}

}

int main() {
	int n;
	cin >> n;
	vector<int> v = CreateVector(n);
	PrintPermutations(v);
	return 0;
}
