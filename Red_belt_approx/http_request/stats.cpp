#include "stats.h"
#include <iostream>

using namespace std;

void Stats::AddMethod(string_view method) {

    if (method_stats.find(method) == method_stats.end()) {
        method_stats["UNKNOWN"]++;
        return;
    }
    method_stats[method]++;
}

void Stats::AddUri(string_view uri) {
    if (uri_stats.find(uri) == uri_stats.end()) {
        uri_stats["unknown"]++;
        return;
    }
    uri_stats[uri]++;
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
    string null = "null";
    vector<string_view> key_words(3, null);

    while (true) {
        if (line[0] == ' ') {
            line.remove_prefix(1);
        }
        else {
            break;
        }
    }

    size_t pos = 0;
    while (true) {
        //cout << "*** " << line << endl;
        size_t space = line.find(' ');
        //cout << line.substr(0, space) << endl;
        key_words[pos] = line.substr(0, space);
        pos++;
        if (space == line.npos) {
            //cout << "broken" << endl;
            break;
        }
        else {
            line.remove_prefix(space + 1);
        }

    }
    //cout << key_words << endl;
    return {key_words[0], key_words[1], key_words[2]};
}