#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void PrintMatrix(const vector<vector<int>>& mat, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

vector<int> GetNeighbor(const vector<vector<int>>& mat, int i, int j, int n, int m) {
	vector<int> result;
	//cout << "getting neighbor" << endl;

	if (i > 0) {
		result.push_back(mat[i-1][j]);
	}
	if (j < m - 1) {
		result.push_back(mat[i][j+1]);
	}
	if (i < n - 1) {
		result.push_back(mat[i+1][j]);
	}
	if (j > 0) {
		result.push_back(mat[i][j-1]);
	}
	//cout << "neighbor got" << endl;
	return result;
}


int GetItem (const vector<vector<int>>& mat, int i, int j, int n, int m) {
	int item = 1;
	//cout << "getting item" << endl;
	vector<int> neighbors = GetNeighbor(mat, i, j, n, m);
	if (count(neighbors.begin(), neighbors.end(), 2) > 1) {
		item = 2;
	}
	else if (count(neighbors.begin(), neighbors.end(), 2) +
			count(neighbors.begin(), neighbors.end(), 3) > 0) {
		item = 3;
	}
	else {
		item = 1;
	}
	//cout << "item got" << endl;
	return item;
}

vector<vector<int>> NewIteration(const vector<vector<int>>& mat, int n, int m,
												vector<vector<int>>& result) {
	vector<vector<int>> new_mat;

	for (int i = 0; i < n; ++i) {
		vector<int> new_str;
		for (int j = 0; j < m; ++j) {
			new_str.push_back(0);
		}
		new_mat.push_back(new_str);
	}
	//cout << "created new zeroes in iter" << endl;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int new_item = GetItem(mat, i, j, n, m);
			if (new_item != mat[i][j]) {
				++result[i][j];
			}
			new_mat[i][j] = new_item;;
		}
	}
	//cout << "filled new zeroes in iter" << endl;
	return new_mat;
}

void Task(vector<vector<int>>& mat, int n, int m, int k) {
	vector<vector<int>> result;
	for (int i = 0; i < n; ++i) {
		vector<int> new_str;
		for (int j = 0; j < m; ++j) {
			new_str.push_back(0);
		}
		result.push_back(new_str);
	}
	//cout << "created zeroes" << endl;
	for (int i = 0; i < k; ++i) {
		mat = NewIteration(mat, n, m, result);
		//cout << "iteration complete" << endl;
	}
	PrintMatrix(result, n, m);

}

int main() {
	int n;
	int m;
	int k;
	cin >> n >> m >> k;
	//cout << n << m << k;
	vector<vector<int>> matrix;
	for (int i = 0; i < n; ++i) {
		vector<int> new_str;
		for (int j = 0; j < m; ++j) {
			int new_element;
			cin >> new_element;
			new_str.push_back(new_element);
		}
		matrix.push_back(new_str);
	}
	//cout << "0" << endl;
	//PrintMatrix(matrix, n, m);
	//cout << "printed" << endl;

	Task(matrix, n, m, k);


	return 0;
}
