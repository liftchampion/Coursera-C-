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

/*
class Rational {
public:
  // �� ������ ��������� ���� ��������� ����������,
  // ����� ���������, ��� ���� ����� ���������� ���������� ���
  // � ����� ������������

  Rational() {

  }
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
};*/


void TestRational() {
	{
		Rational r;
		AssertEqual(r.Numerator(), 0, "Check default N");
		AssertEqual(r.Denominator(), 1, "Check default D");
	}
	{
		Rational r(3, 6);
		AssertEqual(r.Numerator(), 1, "Check reduction N");
		AssertEqual(r.Denominator(), 2, "Check reduction D");
	}
	{
		Rational r(-2, -3);
		AssertEqual(r.Numerator(), 2, "Check reduction and -- N");
		AssertEqual(r.Denominator(), 3, "Check reduction and -- D");
	}
	{
		Rational r(77, 28);
		AssertEqual(r.Numerator(), 11, "Check reduction N");
		AssertEqual(r.Denominator(), 4, "Check reduction D");
	}
	{
		Rational r(25, -5);
		AssertEqual(r.Numerator(), -5, "Check reduction and - N");
		AssertEqual(r.Denominator(), 1, "Check reduction and - D");
	}
	{
		Rational r(0, -5);
		AssertEqual(r.Numerator(), 0, "Check zero num N");
		AssertEqual(r.Denominator(), 1, "Check zero num D");
	}
}




void TestAll() {
	// �������� ���� ���� �����
	TestRunner tr;
	tr.RunTest(TestRational, "TestRational");

}

int main() {
  TestAll();

  return 0;
}
