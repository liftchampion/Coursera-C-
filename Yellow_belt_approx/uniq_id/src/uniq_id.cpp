#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define UNIQ_LINE(arg) var_##arg

#define UNIQ_ID_ARG(arg) UNIQ_LINE(arg)

#define UNIQ_ID UNIQ_ID_ARG(__LINE__)

/*
int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};

  cout << var_14 << endl << var_15 << endl << var_16[0] << endl << var_17[0];

	return 0;
}*/
