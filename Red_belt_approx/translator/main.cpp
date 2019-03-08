#include "test_runner.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <string_view>

using namespace std;

class Translator {
public:
    void Add(const string_view source, const string_view target) {
        forward[source] = target;
        backward[target] = source;
    }
    string TranslateForward(const string_view source) const {
        if (forward.find(source) == forward.end()) {
            return "";
        }
        else {
            return string(forward.at(source));
        }
    }
    string TranslateBackward(const string_view target) const {
        if (backward.find(target) == backward.end()) {
            return "";
        }
        else {
            return string(backward.at(target));
        }
    }

private:
    map<string_view, string_view> forward;
    map<string_view, string_view> backward;
};

void TestSimple() {
    const vector<string> russian = {"okno", "stol"};
    const vector<string> english = {"window", "table"};

    Translator translator;
    translator.Add(russian[0], english[0]);
    translator.Add(russian[1], english[1]);

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}