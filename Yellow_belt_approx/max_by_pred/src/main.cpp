#include "STL_output.h" 
#include "max_by_pred_test.h"
#include "max_by_pred.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
  // ���������� ��� �������
}

void TestUniqueMax() {
  auto IsEven = [](int x) {
    return x % 2 == 0;
  };

  const list<int> hill{2, 4, 8, 9, 6, 4, 2};
  auto max_iterator = hill.begin();
  advance(max_iterator, 2);

  vector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  /*
    �� �� ���������� ASSERT_EQUAL, ������ ��� ��� ����������
    ����������� ���������� ��������� ������ � ����� ostream.
    ������������� ����� ����� �����������, ��� ��� ��� ����� �������
    �������������� ���������, ���� ������� max_element_if, � �������,
    ������� ��������, ����������� �� ����� ����������.
  */
  Assert(max_element_if(numbers.begin(), numbers.end(), IsEven) ==
    --numbers.end());
  Assert(max_element_if(hill.begin(), hill.end(), IsEven) ==
    max_iterator);
}

void TestSeveralMax() {
  struct IsCapitalized {
    bool operator()(const string &s) {
      return !s.empty() && isupper(s.front());
    }
  };

  const forward_list<string> text{"One", "two", "Three", "One", "Two",
    "Three", "one", "Two", "three"};
  auto max_iterator = text.begin();
  advance(max_iterator, 4);

  ASSERT(max_element_if(text.begin(), text.end(), IsCapitalized()) ==
    max_iterator);
}

void TestNoMax() {
  const vector<int> empty;
  const string str = "Non-empty string";

  auto AlwaysTrue = [](int) {
    return true;
  };
  ASSERT(max_element_if(empty.begin(), empty.end(), AlwaysTrue) ==
    empty.end());

  auto AlwaysFalse = [](char) {
    return false;
  };
  ASSERT(max_element_if(str.begin(), str.end(), AlwaysFalse) ==
    str.end());
}

int main() {
  TestRunner tr;
  tr.RunTest(TestUniqueMax, "TestUniqueMax");
  tr.RunTest(TestSeveralMax, "TestSeveralMax");
  tr.RunTest(TestNoMax, "TestNoMax");
  return 0;
}
