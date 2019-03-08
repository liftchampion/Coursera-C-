#include <vector>
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
using namespace std;

void PrintVector(const vector<string>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

string TolowerString(const string& str) {
	string str_l;
	for (const auto& i : str) {
		str_l.push_back(tolower(i));
	}
	return str_l;
}

int main() {
	int n;
	cin >> n;
	vector<string> v(n);
	for (auto& i : v) {
		cin >> i;
	}
	sort(v.begin(), v.end(), [](string a1, string a2) {return TolowerString(a1) < TolowerString(a2) ;});
	PrintVector(v);
	return 0;
}
