#include <set>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

set<int>::const_iterator FindNearestElement(
								const set<int>& numbers,
								int border) {
	set<int>::const_iterator result = numbers.begin();
	int min_difference = abs(*numbers.begin() - border);
	for (auto it = numbers.begin(); it != numbers.end(); it++) {
		if (*it == border) {
			return it;
		}
		if (min_difference > abs(*it - border)) {
			min_difference = abs(*it - border);
			result = it;
		}
		if (min_difference == abs(*it - border)) {
			if (*it < *result) {
				result = it;
			}
		}
	}

	/*int bigger = border;
	set<int>::const_iterator result_bigger = numbers.begin();
	while (bigger <= *prev(numbers.end()) ) {
		if (auto it = numbers.find(bigger) == numbers.end()) {
			bigger++;
		}
		else {
			result_bigger = it;
			break;
		}
	}

	int less = border;
	set<int>::const_iterator result_less = prev(numbers.end());
	while (bigger <= *prev(numbers.end()) ) {
		if (auto it = numbers.find(bigger) == numbers.end()) {
			bigger++;
		}
		else {
			result_bigger = it;
			break;
		}
	}*/



	return result;
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
