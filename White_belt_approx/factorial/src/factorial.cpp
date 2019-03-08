
#include <iostream>
using namespace std;

int Factorial (int n) {
	int f = 1;
	if (n <= 0) {
		return 1;
	}
	while (n >= 1) {
		f *= n;
		n--;
	}
	return f;
}

