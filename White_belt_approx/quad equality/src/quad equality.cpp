
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	double a;
	double b;
	double c;
	double d;
	double x1;
	double x2;
	cin >> a >> b >> c;
	d = b*b - 4*a*c;
	if (d >= 0 && a != 0) {
		x1 = (-b + sqrt(d)) / (2*a);
		x2 = (-b - sqrt(d)) / (2*a);
		if (x1 != x2) {
				cout << x1 << " " << x2;
		}
		else {
				cout << x1;
		}
	}
	if (a == 0 && b != 0) {
		x1 = -c / b;
		cout << x1;
	}


	return 0;
}
