#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
	}
	else {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		auto part1_end = begin(elements) + elements.size() / 3;
		auto part2_begin = part1_end;
		auto part2_end = begin(elements) + 2 * (elements.size() / 3);
		auto part3_begin = part2_end;

		MergeSort(begin(elements), part1_end);
		MergeSort(part2_begin, part2_end);
		MergeSort(part3_begin, end(elements));

		vector<typename RandomIt::value_type> temp;
		merge(begin(elements), part1_end,
			  part2_begin, part2_end,
			  back_inserter(temp));
		merge(begin(temp), end(temp),
			  part3_begin, end(elements),
			  range_begin);
	}
}

int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
