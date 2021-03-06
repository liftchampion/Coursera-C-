//#include "test_runner.h"

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

// ���������� ����� ��������� ����� Table

template<class T>
class Table {
public:
	Table (size_t m, size_t n) {
		_m = m;
		_n = n;

		/*vector<T> str(m);
		vector<vector<T>> matrix;
		for (size_t i = 0; i < n; i++) {
			matrix.push_back(str);
		}
		_table = matrix;*/

		_table.resize(m);
		for (auto& item : _table) {
			item.resize(n);
		}
		//cout << _table[m-1][n-1];
	}
	pair<size_t, size_t> Size() const{
		return make_pair(_m, _n);
	}

	const vector<T>& operator [] (size_t index) const {
		return _table[index];
	}

	vector<T>& operator [] (size_t index) {
		return _table[index];
	}

	void Resize(size_t m, size_t n) {
		_table.resize(m);
		_n = n;
		for (auto& column : _table) {
			column.resize(n);
		}
		_m = m;
	}
private:
	vector<vector<T>> _table;
	size_t _m;
	size_t _n;
};

/*
void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);

  Table<int> t2(3,3);
  t2.Resize(5, 5);
  ASSERT_EQUAL(t2[4][4], 0);
  Table<string> t3(3,3);
  t3.Resize(5, 5);
  ASSERT_EQUAL(t3[4][4], "");
  Table<vector<int>> t4(3,3);
  vector<int> empty_v;
  t4.Resize(5, 5);
  ASSERT_EQUAL(t4[4][4], empty_v);
}*/

/*
int main() {
  //TestRunner tr;
  //RUN_TEST(tr, TestTable);
	//Table<int> t(0, 0);
  return 0;
}*/
