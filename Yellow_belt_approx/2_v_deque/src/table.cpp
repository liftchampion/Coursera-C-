#include "test_runner.h"

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

// ���������� ����� ��������� ����� Table

template<class T>
class Deque {
public:
	Deque() {
		vector<T> empty(0);
		v_back = empty;
		v_front = empty;
	}
	bool Empty() const {
		return v_back.empty() && v_front.empty();
	}
	size_t Size() const {
		return v_back.size() + v_front.size();
	}
	void PushFront(T new_item) {
		v_front.push_back(new_item);
	}
	void PushBack(T new_item) {
		v_back.push_back(new_item);
	}
	T& Front() {
		return v_front.back();
	}
	const T& Front() const {
		return v_front.back();
	}
	T& Back() {
		return v_back.back();
	}
	const T& Back() const {
		return v_back.back();
	}
	T& operator[] (size_t index) {
		//cerr << "index = " << index << endl;
		//cerr << "f = " << v_front.size() << endl;
		//cerr << "b = " << v_back.size() << endl;

		if (index < v_front.size()) {
			return v_front[v_front.size() - 1 - index];
			//cerr << "called 1" << endl;
		}
		else if (index == v_front.size()) {
			//cerr << "called 2" << endl;
			return v_back[0];
		}
		else {
			//cerr << "called 3" << endl;
			return v_back[index - v_front.size()];
		}
	}
	const T& operator[](size_t index) const {
		if (index < v_front.size()) {
			//cerr << "called 1" << endl;
			return v_front[v_front.size() - 1 - index];
		}
		else if (index == v_front.size()) {
			//cerr << "called 2" << endl;
			return v_back[0];
		}
		else {
			//cerr << "called 3" << endl;
			return v_back[index - v_front.size()];
		}
	}
	T& At(size_t index) {
		if (index >= Size()) {
			throw out_of_range("last element is " + to_string(Size() - 1));
		}
		return operator[](index);
	}
	const T& At(size_t index) const{
		if (index >= Size()) {
			throw out_of_range("last element is " + to_string(Size() - 1));
		}
		return operator[](index);
	}
	vector<T> GetFront() const{
		return v_front;
	}
	vector<T> GetBack() const{
		return v_back;
	}
private:
	vector<T> v_back;
	vector<T> v_front;
};

template<class T>
ostream& operator<< (ostream& os, const Deque<T>& d) {
	vector<T> f = d.GetFront();
	vector<T> b = d.GetBack();
	for (size_t i = f.size(); i > 0; i--) {
		os << f[i - 1] << " ";
	}
	os << endl;
	for (size_t i = 0; i < b.size(); i++) {
		os << b[i] << " ";
	}
	return os;
}


void TestDeque() {
	Deque<int> d;

	d.PushBack(9);
	d.PushBack(9);
	ASSERT_EQUAL(d.Back(), 9);

	d.PushFront(0);
	//cout << d;
	ASSERT_EQUAL(d.Front(), 0);
	ASSERT_EQUAL(d.Back(), 9);
	ASSERT_EQUAL(d[0], 0);
	ASSERT_EQUAL(d[2], 9);
	//ASSERT_EQUAL(d[9], 9);
	ASSERT_EQUAL(d[1], 9);

	d.PushBack(5);
	d.PushBack(6);
	d.PushBack(7);
	d.PushBack(8);
	d.PushFront(4);
	d.PushFront(3);
	d.PushFront(2);
	d.PushFront(1);

}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestDeque);
  return 0;
}
