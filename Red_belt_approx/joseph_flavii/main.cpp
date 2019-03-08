#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>

using namespace std;

template<typename RandIt>
void MakeJosephusPermutation(RandIt first, RandIt last, uint32_t stepSize) {

    vector<typename RandIt::value_type> circle(last - first);
    size_t i = 0;
    for (auto it = first; it != last; it++) {
        circle[i] = move(*it);
        i++;
    }

    size_t curPos = 0;
    while(!circle.empty()) {
        *(first++) = move(circle[curPos]);
        circle.erase(circle.begin() + curPos);
        if (circle.empty()) {
            break;
        }
        curPos = (curPos + stepSize - 1) % circle.size();
    }

    //cout << "** " << circle << endl;

}

/*
vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_ = {11};
        vector<int> numbers_copy = {11};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        cout << numbers_copy << endl;
        ASSERT_EQUAL(numbers_copy, numbers_);
    }
    {
        string numbers_ = "11111111";
        string numbers_copy = "11111111";
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        cout << numbers_copy << endl;
        ASSERT_EQUAL(numbers_copy, numbers_);
    }
    {
        vector<string> numbers_ = {"one", "two", "three"};
        vector<string> numbers_copy = {"one", "two", "three"};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        cout << numbers_copy << endl;
        ASSERT_EQUAL(numbers_copy, numbers_);
    }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    cout << numbers_copy << endl;
    ASSERT_EQUAL(numbers_copy, numbers);
  }

  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
      cout << numbers_copy << endl;
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

int main() {



  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}*/