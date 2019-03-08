
#include <iostream>
#include <string>
using namespace std;

int main() {
	string string1;
	string string2;
	string string3;
	cin >> string1 >> string2 >> string3;
	if (string1 < string2) {
		if (string1 < string3){
			cout << string1;
		}
		else {
			cout << string3;
		}
	}
	else {
		if (string2 < string3){
					cout << string2;
		}
		else {
			cout << string3;
		}
	}


	return 0;
}
