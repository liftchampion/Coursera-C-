#include "test_framework.h"


///////////////////////////////////////////////////////
void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}


///////////////////////////////////////////////////////
TestRunner::~TestRunner() {
    if (fail_count > 0) {
    	cerr << endl;
    	cerr << fail_count << " unit tests failed. Terminate" << endl;
    	exit(1);
    }
  }




