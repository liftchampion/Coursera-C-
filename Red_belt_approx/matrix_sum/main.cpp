#include "test_runner.h"
#include <vector>
#include <future>
using namespace std;


template<typename Iterator>
class PageClass {
public:
    PageClass(Iterator begin, Iterator end) :
            _begin(begin), _end(end) {
    }
    Iterator begin() const{
        return _begin;
    }
    Iterator end() const{
        return _end;
    }
    size_t size() const{
        return _end - _begin;
    }

private:
    Iterator _begin;
    Iterator _end;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        while (end - begin > page_size) {
            PageClass<Iterator> new_page(begin, begin + page_size);
            pages.push_back(new_page);
            begin += page_size;
        }
        if (begin != end) {
            PageClass<Iterator> new_page(begin, end);
            pages.push_back(new_page);
        }
    }
    auto begin() const{
        return pages.begin();
    }
    auto end() const {
        return pages.end();
    }
    size_t size() const {
        return pages.size();
    }
private:
    vector<PageClass<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}

template <typename Iterator>
int64_t CalculateMatrixSumSingleThread(Iterator begin, Iterator end) {
    int64_t sum = 0;
    for (auto it = begin; it != end; it++) {
        for (const auto& item : *it) {
            sum += item;
        }
    }
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    // Реализуйте эту функцию
    int CORE_COUNT = 4;
    float page_size_f = matrix.size() / CORE_COUNT;
    int page_size = int(page_size_f + 1);
    //cout << page_size << endl;
    //cout << matrix.size() / page_size << endl;
    Paginator pages = Paginate(matrix, page_size);
    int64_t sum = 0;
    vector<future<int64_t>> futures;

    for (const auto& page : pages) {
        futures.push_back(async([page](){return CalculateMatrixSumSingleThread(page.begin(), page.end());}));
        //sum += CalculateMatrixSumSingleThread(page.begin(), page.end());
    }
    for (auto& future : futures) {
        sum += future.get();
    }
    return sum;

}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
