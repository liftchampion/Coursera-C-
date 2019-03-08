#pragma once

#include "profile.h"


#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <future>
#include <mutex>
using namespace std;

void operator += (vector<pair<uint16_t, uint16_t>>& lhs, const unordered_map<uint16_t, uint16_t>& rhs);

bool CompFunc(const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs);

class InvertedIndex {
public:

    size_t GetDocsCount();

    const unordered_map<uint16_t, uint16_t>& GetHitcount(const string& word);

    void ReplaceDocuments(istream& document_input);

    void AddDocuments(istream& document_input);

    void MakeMaps();

private:
    mutex guard;
    unordered_map<string, pair<vector<uint16_t>, unordered_map<uint16_t, uint16_t>>> index_;
    uint16_t docs_count = 0u;
    const unordered_map<uint16_t, uint16_t> _empty = {};
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AppendDocumentBase(istream& document_input);
    void AddQueriesStreamOT(istream& query_input, ostream& search_results_output);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
    mutex mut;
    void CreateOutput(vector<pair<uint16_t, uint16_t>>& relevancy, ostream& search_results_output);
    vector<future<void>> requests;
};
