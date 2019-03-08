#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

void TestCopyAssignment() {
    SimpleVector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 1);

    SimpleVector<int> dest;
    ASSERT_EQUAL(dest.Size(), 0u);

    dest = numbers;
    ASSERT_EQUAL(dest.Size(), numbers.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));


    SimpleVector<int> numbers2;
    dest = numbers2;
    ASSERT_EQUAL(dest.Size(), numbers2.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(equal(dest.begin(), dest.end(), numbers2.begin()));

    SimpleVector<int> numbers3(5);
    dest = numbers3;
    ASSERT_EQUAL(dest.Size(), numbers3.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(equal(dest.begin(), dest.end(), numbers3.begin()));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCopyAssignment);
}
