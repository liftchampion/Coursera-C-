#include "test_runner.h"

#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cstdint>
#include <utility>
#include <locale>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;


template <typename String>
vector<int8_t> StringToSeq(const String& str, const vector<typename String::value_type>& chars){

}


template <typename String>
vector<typename String::value_type> SplitStringToChars(const String& str) {
    set<typename String::value_type> chars;
    for (size_t i = 0; i < str.size(); i++) {
        chars.insert(str[i]);
    }

    vector<typename String::value_type> chars_v;
    for (auto& char_ : chars) {
        chars_v.push_back(move(char_));
    }

    return chars_v;
}

template <typename String>
vector<Group<String>> MapToVector(map<vector<typename String::value_type>, vector<String>>& m) {
    vector<Group<String>> v;
    for (auto& item : m) {
        v.push_back(move(item.second));
    }
    return v;
}

template <typename String>
struct LightChar {
    size_t num;
    String& str;
    LightChar()
        : num(0)
        , str(nullptr) {}

    LightChar(size_t num_, String& str_)
        : num(num_)
        , str(str_) {}

    typename String::value_type GetChar() {
        return str[num];
    }

};

template <typename String>
bool operator < (const LightChar<String>& lhs, const LightChar<String>& rhs){
    return lhs.str[lhs.num] < rhs.str[rhs.num];
}
template <typename String>
bool operator == (const LightChar<String>& lhs, const LightChar<String>& rhs){
    return *lhs.str[lhs.num] == *rhs.str[rhs.num];
}

template <typename String>
class LightString {
public:
    LightString(vector<LightChar<String>>& unique_chars, vector<size_t>& chars_seq)
        : unique_chars_(unique_chars)
        , chars_seq_(chars_seq) {}

    String GetStr() {
        String str;
        for (auto i : chars_seq_) {
            str.push_back(move(unique_chars_[i].str[unique_chars_[i].num]));
        }
        //cout << str << endl;
        return str;
    }
    vector<LightChar<String>> GetUniqueChars() {
        return unique_chars_;
    }

private:
    size_t pos_;
    vector<LightChar<String>> unique_chars_;
    vector<size_t> chars_seq_;
};

template <typename String>          // L*logL
LightString<String> LightenStr (String& str) {
    set<LightChar<String>> chars;
    for (size_t i = 0; i < str.size(); i++) {
        chars.insert(LightChar<String>(i, str));
    }

    vector<LightChar<String>> chars_v;
    for (const auto& i : chars) {
        chars_v.push_back(i);
    }

    /*vector<size_t> chars_ints;
    for (const auto& i : chars_v) {
        chars_ints.push_back(i.num);
    }
    cout << chars_ints << endl;*/

   vector<size_t> str_seq;
    for (size_t i = 0; i < str.size(); i++) {
    auto it = lower_bound(chars_v.begin(), chars_v.end(), LightChar<String>(i, str));
    str_seq.push_back(it - chars_v.begin());
    }

    //cout << str_seq << endl;

    LightString<String> ls(chars_v, str_seq);
    ls.GetStr();

    return ls;

}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  // использовав не более 1 копирования каждого символа
    map<vector<LightChar<String>>, vector<String>> groups;
    for (auto& str : strings) {
        LightString<String> ls = LightenStr(str);
        groups[ls.GetUniqueChars()].push_back(ls.GetStr());
    }
    //cout << "simplified" << endl;

    vector<Group<String>> groups_v;

    for (auto& item : groups) {
        groups_v.push_back(move(item.second));

    }
    return groups_v;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);


   /* vector<string> strs = {"111"};
    string str1 = "paloalto";
    LightenStr(str1);
    cout << str1 << endl;

    string str2 = "ccccc";
    LightenStr(str2);
    cout << str2 << endl;

    string str3 = "";
    LightenStr(str3);
    cout << str3 << endl;*/





  return 0;
}