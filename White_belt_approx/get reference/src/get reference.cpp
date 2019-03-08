/*#include <map>
#include <iostream>
#include <exception>
using namespace std;*/

template <typename First, typename Second>
Second& GetRefStrict (map<First, Second>& m, First key) {
	if (m.count(key) == 0) {
		throw runtime_error("");
	}
	return m[key];
}
/*
int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}*/
