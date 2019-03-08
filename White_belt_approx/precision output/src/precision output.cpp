#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	ifstream input("input.txt");
	double num;
	if (input) {
		while (input >> num) {
			cout << fixed << setprecision(3) << num << endl;
		}
	}
	return 0;
}
