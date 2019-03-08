#include <vector>
#include <iostream>
using namespace std;

int main() {
	int num10;
	vector<int> digits;
	cin >> num10;
	while (num10 >= 2 ) {
		digits.push_back(num10 % 2);
		num10 = num10 / 2;
	}
	if (num10 != 0) {
		digits.push_back(1);
	}
	else {
		digits.push_back(0);
	}

	for (int i = digits.size() - 1 ; i >= 0; --i) {
		cout << digits[i];
	}
	return 0;
}
