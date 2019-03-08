#pragma once

#include <string_view>
#include <sstream>
#include <vector>
using namespace std;


string_view Strip(string_view s);
vector<string_view> SplitBy(string_view s, char sep);