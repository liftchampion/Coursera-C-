#include <vector>
#include <iostream>
#include <string>
using namespace std;

void PrintVector (vector<bool> v) {
	for (auto i : v) {
		cout << i << endl;
	}
}

void Worry(vector<bool>& que, int i) {
	que[i] = true;
}

void Quiet(vector<bool>& que, int i) {
	que[i] = false;
}

void Come(vector<bool>& que, int k) {
	que.resize(que.size() + k);
}

int WorryCount(const vector<bool>& que) {
	int n = 0;
	for (auto i : que) {
		if (i == true) {
			n++;
		}
	}
	return n;
}

int main() {
	vector<bool> que(0, false);
	int q;
	cin >> q;

	for(int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "WORRY") {
			int d;
			cin >> d;
			Worry(que, d);
		}
		if (command == "QUIET") {
			int d;
			cin >> d;
			Quiet(que, d);
		}
		if (command == "COME") {
			int d;
			cin >> d;
			Come(que, d);
		}
		if (command == "WORRY_COUNT") {
			cout << WorryCount(que) << endl;
		}
	}

	return 0;
}
