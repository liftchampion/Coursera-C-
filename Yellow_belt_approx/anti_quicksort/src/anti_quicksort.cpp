#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void PrintVector(const vector<int>& v, ostream& stream) {
	for (const auto& i : v) {
		stream << i << " ";
	}
}

int main() {
	ifstream input ("antiqs.in");
	ofstream output("antiqs.out");
	int n;
	input >> n;
	input.close();

	vector<int> nums(n);
	for (int i = 1; i <= n; i++) {
		nums[i - 1] = i;
	}

	for (int i = 0; i < n; i++) {
		int tmp = nums[i];
		nums[i] = nums[i / 2];
		nums[i / 2] = tmp;
	}
	PrintVector(nums, output);
	output.close();

	return 0;
}
