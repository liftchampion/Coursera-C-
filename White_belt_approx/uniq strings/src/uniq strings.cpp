/*
 * 6 first second first third second second
 */
#include <set>
#include <string>
#include <iostream>
using namespace std;

int main() {
	int q;
	cin >> q;
	set<string> strings;
	for (int i = 0; i < q; ++i) {
		string str;
		cin >> str;
		strings.insert(str);
	}
	cout << strings.size();
	return 0;
}
