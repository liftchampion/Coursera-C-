#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ifstream input("input.txt");
	string line;
	vector<string> file_data;
	if (input) {
		while (getline(input, line)) {
			cout << line << endl;
			file_data.push_back(line);
		}
	}
	ofstream output("output.txt");
	if (output) {
		for (const auto& item : file_data) {
			output << item << endl;
		}
	}

	return 0;
}
