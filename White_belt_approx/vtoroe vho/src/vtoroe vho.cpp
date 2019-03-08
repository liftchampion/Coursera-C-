#include <string>
#include <iostream>
using namespace std;

int main() {
	string str;
	bool first = false;
	bool second = false;
	cin >> str;
	for (int i = 0; i < str.size(); ++i) {
		if ( str [i] == 'f' && first == true && second == false) {
			second = true;
			cout << i;
			break;
		}
		if ( str[i] == 'f' && first == false) {
			first = true;
		}

	}

	if (first == false && second == false) {
		cout << -2;
	}
	if (first == true && second == false) {
		cout << -1;
	}
	return 0;
}
