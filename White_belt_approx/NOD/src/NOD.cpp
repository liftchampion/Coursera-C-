
#include <iostream>
using namespace std;

int main() {
	int a, b, o, m, l;
	cin >> a >> b;
	if (a >= b) {
		m = a;
		l = b;
	}
	else {
		m = b;
		l = a;
	}

	while (l >= 1) {
		o = m % l;
		if ( o == 0) {
			break;
		}
		else {
			m = l;
			l = o;
		}
	}
	cout << l;
	return 0;
}
