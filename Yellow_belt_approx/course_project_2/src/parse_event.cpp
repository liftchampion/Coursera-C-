#include "parse_event.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

string ParseEvent(istream& is) {
	string event;

	bool leading_space = is.peek() == ' ';
	while (leading_space) {
		is.ignore(1);
		leading_space = is.peek() == ' ';
	}

	getline(is, event);
	return event;
}



