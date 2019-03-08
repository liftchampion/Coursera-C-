#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
	ifstream input("input.txt");
	int N_strok;
	int M_stolb;
	int value;
	if (input) {
		input >> N_strok;
		input >> M_stolb;
	}
	for (int i = 0; i < N_strok; ++i) {
		for (int j = 0; j < M_stolb; ++j) {
			input.ignore(1);
			input >> value;
			cout << setw(10) << value;
			if (j != M_stolb - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
