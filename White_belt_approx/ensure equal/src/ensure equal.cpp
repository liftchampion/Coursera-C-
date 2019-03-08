#include <string>
#include <iostream>
using namespace std;

void EnsureEqual (const string& lhs, const string& rhs) {
	if (lhs != rhs) {
		string ss;
		ss = lhs + " != " + rhs;
		throw runtime_error(ss);
	}
}

/*int main() {
  try {
    EnsureEqual("C++ White", "C++ White");
    EnsureEqual("C++ White", "C++ Yellow");
  } catch (runtime_error& e) {
    cout << e.what() << endl;
  }
  return 0;
}*/
