#include <vector>
#include <iostream>
using namespace std;



template<class InputIt1, class InputIt2, class OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first, int& counter)
{
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (*first2 < *first1) {
            *d_first = *first2;
            ++first2;
            counter += (last1 - first1);
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end, int& counter) {
	if (range_end - range_begin < 2) {
	}
	else {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		auto part1_end = begin(elements) + elements.size() / 2;
		auto part2_begin = part1_end;
		MergeSort(begin(elements), part1_end, counter);
		MergeSort(part2_begin, end(elements), counter);
		merge(begin(elements), part1_end,
			  part2_begin, end(elements),
			  range_begin, counter);
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto& i : v) {
		cin >> i;
	}

	int counter = 0;
	MergeSort(begin(v), end(v), counter);
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	cout << counter;
	return 0;
}
