/*
 * 10 7 10 3 2 7 4 8 5 9 10
 * 5 1000000000 999999996 999999997 999999998 999999995
 */

#include <vector>
#include <iostream>
#include <set>
using namespace std;

/*void PrintVector(const vector<int>& a) {
	for (const int& i : a) {
		cout << i << " ";
	}
}*/

int HowMuchDelete (const vector<int>& a) {
	set<int> nums;
	int result = 0;
	for (const int& i : a) {
		if (nums.count(i) == 0) {
			nums.insert(i);
		}
		else {
			++result;
		}
	}
	return result;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& i : a) {
		cin >> i;
	}
	//PrintVector(a);
	//cout << endl;
	cout << HowMuchDelete(a);

	return 0;
}
