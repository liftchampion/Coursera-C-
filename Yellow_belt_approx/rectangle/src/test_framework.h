#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "STL_output.h"

using namespace std;

///////////////////////////////////////////////////////
class TestRunner {
public:

	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
	    func();
	    cerr << test_name << " OK" << endl;
	    }
		catch (exception& e) {
	      ++fail_count;
	      cerr << test_name << " fail: " << e.what() << endl;
	    }
		catch (...) {
	      ++fail_count;
	      cerr << "Unknown exception caught" << endl;
	    }
	 }

  ~TestRunner();

private:
  int fail_count;
};

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {});

void Assert(bool b, const string& hint);


///////////////////////////////////////////////////////
template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << endl << "	Assertion failed: " << endl << "		" << t << " != " << u;
    if (!hint.empty()) {
       os  << "   hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}



