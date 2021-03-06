#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "[";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "]";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "<";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << ">";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << "(" << kv.first << " : " << kv.second << ")";
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
  os << "(" << p.first << " : " << p.second << ")";

  return os;
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << endl << "	Assertion failed: " << endl << "		" << t << " != " << u;
    if (!hint.empty()) {
       os << endl << "		hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
    	cerr << endl;
    	cerr << fail_count << " unit tests failed. Terminate" << endl;
    	exit(1);
    }
  }

private:
  int fail_count = 0;
};



bool IsPalindrom(const string& str) {
  // �� ������ ��������� ���� ��������� ���������� �������,
  // ����� ���������, ��� ���� ����� ���������� ���������� ���
  // � ����� ������������
	return true;
}

void TestIsPalindrom() {
	AssertEqual(IsPalindrom(""), true, "empty");
	AssertEqual(IsPalindrom(" "), true, "1 - < >");
	AssertEqual(IsPalindrom("a"), true, "1 - <a>");
	AssertEqual(IsPalindrom("  a"), false, "3 - <  a>");
	AssertEqual(IsPalindrom("a  "), false, "3 - <a  >");
	AssertEqual(IsPalindrom("baaa"), false, "4 - <baaa>");
	AssertEqual(IsPalindrom("aaab"), false, "4 - <aaab>");
	AssertEqual(IsPalindrom("madam"), true, "5 - <madam>");
	AssertEqual(IsPalindrom("mada m"), false, "6 - <mada m>");
	AssertEqual(IsPalindrom("notpalindr0m"), false, "many - <notpalindr0m>");
	AssertEqual(IsPalindrom("maddam0"), false, "7 - <maddam0>");
	AssertEqual(IsPalindrom("0maddam"), false, "7 - <0maddam>");
	AssertEqual(IsPalindrom("0maddam0"), true, "8 - <0maddam0>");
}


void TestAll() {
	// �������� ���� ���� �����
	TestRunner tr;
	tr.RunTest(TestIsPalindrom, "TestIsPalindrom");

}

int main() {
  TestAll();

  return 0;
}
