#include "test_runner.h"

#include <sstream>
#include <iostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

/*
int main() {
  TestRunner tr;
  tr.RunTest([] {
    {ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");}

    {ostringstream output;
    int x = 4;
    int y = 5;
    PRINT_VALUES(output, x, y);
    ASSERT_EQUAL(output.str(), "4\n5\n");}

    {ostringstream output;
    int x = 4;
    int y = 5;
    PRINT_VALUES(output, ++x, y++);
    ASSERT_EQUAL(output.str(), "5\n5\n");}

    {ostringstream output;
    auto x = [](){if (true) {
    	cout << "called x" << endl;
    				int z = 1;
    				string q = "q";
    				return z;
    			  }
    };
    auto y = [](){if (true) {
    	cout << "called y" << endl;
        				int z = 3;
        				string q = "q";
        				return z;
        			  }
    };

    PRINT_VALUES(output, x(), y());
    ASSERT_EQUAL(output.str(), "1\n3\n");}

  }, "PRINT_VALUES usage example");

  if (true)
	  PRINT_VALUES(cout, 1, 1);
  PRINT_VALUES(cout, 1, 1);
  if (false) {
	  PRINT_VALUES(cout, 1, 1); }
  else
	  PRINT_VALUES(cout, 1, 1);


  if (false)
	  PRINT_VALUES(cout, 5, 5);
  else
	  PRINT_VALUES(cout, 6, 6);

  if (false)
	  {cout << "444";}
  else
	  {cout << "555";}

	return 0;
}*/
