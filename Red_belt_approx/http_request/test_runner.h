#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <array>


using namespace std;

template <class T>
ostream& operator << (ostream& os1, const vector<T>& s) {
    os1 << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os1 << ", ";
        }
        first = false;
        os1 << x;
    }
    return os1 << "}";
}

template <class T, size_t N>
ostream& operator << (ostream& os1, const array<T, N>& a) {
    os1 << "{";
    bool first = true;
    for (const auto& x : a) {
        if (!first) {
            os1 << ", ";
        }
        first = false;
        os1 << x;
    }
    return os1 << "}";
}

template <class T>
ostream& operator << (ostream& os1, const set<T>& s) {
    os1 << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os1 << ", ";
        }
        first = false;
        os1 << x;
    }
    return os1 << "}";
}

template <class K, class V>
ostream& operator << (ostream& os1, const map<K, V>& m) {
    os1 << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os1 << ", ";
        }
        first = false;
        os1 << kv.first << ": " << kv.second;
    }
    return os1 << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (!(t == u)) {
        ostringstream os1;
        os1 << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os1 << " hint: " << hint;
        }
        throw runtime_error(os1.str());
    }
}

inline void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

#define ASSERT_EQUAL(x, y) {            \
  ostringstream os1;                    \
  os1 << #x << " != " << #y << ", "     \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, os1.str());         \
}

#define ASSERT(x) {                     \
  ostringstream os1;                    \
  os1 << #x << " is false, "            \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, os1.str());                 \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)

