#pragma once

#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <ctime>
#include <fstream>
#include "test_runner.h"
#include "iterator_range.h"

using namespace std;


vector<string> GenerateWords();
string GenerateDoc(const vector<string>& words);
string GenerateQuery(const vector<string>& words);
vector<string> GenerateDocs(const vector<string>& words = GenerateWords());
vector<string> GenerateQueries(const vector<string>& words = GenerateWords());
istringstream MakeStream(const vector<string>& items);

template <typename Container>
string Join(char c, const Container& cont) {
    //ADD_DURATION(join);
    ostringstream os;
    for (const auto& item : Head(cont, cont.size() - 1)) {
        os << item << c;
    }
    os << *rbegin(cont);
    return os.str();
}
