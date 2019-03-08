#include "profile.h"


//extern TotalDuration updatedocumentbase;
//extern TotalDuration addqueriesstream;
//extern TotalDuration add;

//extern TotalDuration sorting;
//extern TotalDuration hitcount;

//extern TotalDuration createoutput;
//extern TotalDuration refillvector;


#include "search_server.h"
#include "iterator_range.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <queue>
#include <utility>


size_t InvertedIndex::GetDocsCount() {
    lock_guard<mutex> g(guard);
    return docs_count;
}

void InvertedIndex::ReplaceDocuments(istream& document_input){
    unordered_map<string, pair<vector<uint16_t>, unordered_map<uint16_t, uint16_t>>> new_index;
    uint16_t new_docs_count = 0;

    for (string current_document; getline(document_input, current_document);) {
        char sep = ' ';
        size_t b = 0;
        while ((b = current_document.find_first_not_of(sep, b)) != current_document.npos) {
            size_t e = current_document.find_first_of(sep, b);
            new_index[current_document.substr(b, e-b)].first.push_back(new_docs_count);
            b = e;
        }
        new_docs_count++;
    }
    for (auto& [key, value] : new_index) {
        for (const auto n : value.first) {
            value.second[n]++;
        }
    }
    lock_guard<mutex> g(guard);
    index_ = move(new_index);
    docs_count = new_docs_count;
}

void InvertedIndex::AddDocuments(istream& document_input){
    for (string current_document; getline(document_input, current_document);) {
        char sep = ' ';
        size_t b = 0;
        while ((b = current_document.find_first_not_of(sep, b)) != current_document.npos) {
            size_t e = current_document.find_first_of(sep, b);
            index_[current_document.substr(b, e-b)].first.push_back(docs_count);
            b = e;
        }
        docs_count++;
    }
}

void InvertedIndex::MakeMaps(){
    for (auto& [key, value] : index_) {
        for (const auto n : value.first) {
            value.second[n]++;
        }
    }
}

const unordered_map<uint16_t, uint16_t>& InvertedIndex::GetHitcount(const string& word){
    lock_guard<mutex> g(guard);
    if (index_.find(word) == index_.end()){
        return _empty;
    }
    else {
        return index_[word].second;
    }
};

SearchServer::SearchServer(istream& document_input) {
    //ADD_DURATION(searchserver);
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    //ADD_DURATION(updatedocumentbase);
    index.ReplaceDocuments(document_input);
}

void SearchServer::AppendDocumentBase(istream& document_input) {
    //ADD_DURATION(updatedocumentbase);
    index.AddDocuments(document_input);
    index.MakeMaps();
}

void operator += (vector<pair<uint16_t, uint16_t>>& lhs, const unordered_map<uint16_t, uint16_t>& rhs){
    for (const auto& [key, value] : rhs) {
        lhs[key].first += value;
        lhs[key].second = key;
    }
    //cout << lhs << endl;
    //cout << rhs << endl << endl;
}

bool CompFunc(const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs) {
    if (lhs.first != rhs.first) {
        return lhs.first > rhs.first;
    }
    else {
        return lhs.second < rhs.second;
    }
}

void SearchServer::CreateOutput(vector<pair<uint16_t, uint16_t>>& relevancy, ostream& search_results_output){
    //cout << relevancy << endl;
    {
        //ADD_DURATION(sorting);
        uint16_t head_size = relevancy.size() > 5u ? 5u : relevancy.size();
        partial_sort(relevancy.begin(), relevancy.begin() + head_size, relevancy.end(), CompFunc);
    }
    //cout << relevancy << endl << endl;
    {
        //ADD_DURATION(createoutput);
        {
            lock_guard<mutex> g(mut);
            search_results_output << ":";
        }
        bool is_first = true;
        for (uint16_t i = 0; i < (relevancy.size() >= 5u ? 5u : relevancy.size()); i++) {
            if (relevancy[i].first != 0) {
                lock_guard<mutex> g(mut);
                search_results_output << " {docid: " << relevancy[i].second
                                      << ", hitcount: " << relevancy[i].first << "}";

            }
        }
        {
            lock_guard<mutex> g(mut);
            search_results_output << '\n';
        }
    }
    {
        //ADD_DURATION(refillvector);
        fill(relevancy.begin(), relevancy.end(), pair<uint16_t, uint16_t>(0u, 0u));
    }
}

void SearchServer::AddQueriesStreamOT(
        istream& query_input, ostream& search_results_output
) {
    //ADD_DURATION(addqueriesstream);
    vector<pair<uint16_t, uint16_t>> relevancy(index.GetDocsCount());
    for (string current_query; getline(query_input, current_query);) {
        {
            lock_guard<mutex> g(mut);
            search_results_output << current_query;
        }
        char sep = ' ';
        size_t b = 0;
        while ((b = current_query.find_first_not_of(sep, b)) != current_query.npos) {
            size_t e = current_query.find_first_of(sep, b);
            relevancy += index.GetHitcount(current_query.substr(b, e-b));
            b = e;
        }
        CreateOutput(relevancy, search_results_output);
    }
}

void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
) {
    requests.push_back(async(launch::async, &SearchServer::AddQueriesStreamOT,
                             this, ref(query_input), ref(search_results_output)));
    if (requests.size() == 2){
        requests.clear();
    }
}

