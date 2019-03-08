#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <iterator>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

        vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin),
                                                       make_move_iterator(range_end));
        auto part1_end = begin(elements) + elements.size() / 3;
        auto part2_begin = part1_end;
        auto part2_end = begin(elements) + 2 * (elements.size() / 3);
        auto part3_begin = part2_end;

        MergeSort(begin(elements), part1_end);
        MergeSort(part2_begin, part2_end);
        MergeSort(part3_begin, end(elements));

        vector<typename RandomIt::value_type> temp;
        merge(make_move_iterator(begin(elements)),
              make_move_iterator(part1_end),
              make_move_iterator(part2_begin),
              make_move_iterator(part2_end),
              back_inserter(temp));
        merge(make_move_iterator(begin(temp)),
              make_move_iterator(end(temp)),
              make_move_iterator(part3_begin),
              make_move_iterator(end(elements)),
              range_begin);

}

void TestIntVector() {
    vector<int> numbers = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
