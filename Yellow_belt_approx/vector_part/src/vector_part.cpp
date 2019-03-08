#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto border = find_if(
					numbers.begin(), numbers.end(),
					[] (int n) {
					return n < 0;
					});
	while (border != numbers.begin()) {
		border--;
		cout << *border << " ";
	}
}

int main() {
	 PrintVectorPart({6, 1, 8, -5, 4});
	 cout << endl;
	 PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	 cout << endl;
	 PrintVectorPart({6, 1, 8, 5, 4});
	return 0;
}
