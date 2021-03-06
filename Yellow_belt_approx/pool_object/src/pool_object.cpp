#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
	  if (free.size() > 0) {
		  T* new_obj = free.front();
		  free.pop();
		  working.insert(new_obj);
		  return new_obj;
	  }
	  else {
		  T* new_obj = new T;
		  working.insert(new_obj);
		  return new_obj;
	  }
  }
  T* TryAllocate() {
	  if (free.size() > 0) {
		  T* new_obj = free.front();
		  free.pop();
		  working.insert(new_obj);
		  return new_obj;
	  }
	  else {
		  return nullptr;
	  }
  }

  void Deallocate(T* object) {
	  auto it = working.find(object);
	  if (it == working.end()) {
		  throw invalid_argument("not found");
	  }
	  free.push(*it);
	  working.erase(it);
  }

  ~ObjectPool() {
	  while (!free.empty()) {
		  T* tmp = free.front();
		  free.pop();
		  delete tmp;

	  }
	  while (!working.empty()) {
		  T* tmp = *working.begin();
		  working.erase(working.begin());
		  delete tmp;
	  }
  }

private:
  // �������� ���� ����
  queue<T*> free;
  set<T*> working;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
