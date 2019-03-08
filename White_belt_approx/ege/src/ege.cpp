#include <iostream>
using namespace std;

int NotFactorial(int n) {
	int result = 0;
	if (n == 1 || n == 0) {
		return 1;
	}
	else {
		while (n > 0) {
			result += n;
			n--;
		}
	}
	return result;
}

int RecursiveFactorial (int n) {
	if (n == 1 || n == 0) {
		return 1;
	}
	return n * RecursiveFactorial(n-1);
}

int main() {
	/*int d14 = 0;
	int d7 = 0;
	int d2 = 0;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		if (temp % 14 == 0) {
			d14++;
		}
		else if (temp % 7 == 0) {
			d7++;
		}
		else if (temp % 2 == 0) {
			d2++;
		}
	}
	cout << NotFactorial(n-1) - d14 * (n-1) - d7 * d2;*/

	int n;
	cin >> n;
	cout << RecursiveFactorial(n);


	return 0;
}
