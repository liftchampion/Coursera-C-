#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
	}
	else {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		auto part1_end = begin(elements) + elements.size() / 2;
		auto part2_begin = part1_end;
		MergeSort(begin(elements), part1_end);
		MergeSort(part2_begin, end(elements));
		merge(begin(elements), part1_end,
			  part2_begin, end(elements),
			  range_begin);
	}
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
