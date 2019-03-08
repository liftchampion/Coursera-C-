#include <vector>
#include <iostream>
using namespace std;

void PrintVector (vector<int> v) {
	for (auto i : v) {
		cout << i << endl;
	}
}

double FindAverage (const vector<int>& v) {
	double average = 0;
	for (auto i : v) {
		average += i;
	}
	average /= v.size();
	return average;
}

void PrintNumDays (const vector<int>& v) {
	int n = 0;
	int av = FindAverage(v);
	for (auto i : v) {
		if (i > av) {
			n++;
		}
	}
	cout << n << endl;
}

void PrintDays (const vector<int>& v) {
	int av = FindAverage(v);
	for (int i = 0; i <= v.size(); ++i) {
		if (v[i] > av) {
			cout << i << ' ';
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> temps(n);
	for (int& t : temps) {
		cin >> t;
	}
	PrintNumDays(temps);
	PrintDays(temps);
	return 0;
}
