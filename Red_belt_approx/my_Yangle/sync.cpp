#include "sync.h"

using namespace std;

auto Lock(mutex& m) {
    return lock_guard<mutex>{m};
}

Access::Access(const string& key, pair<mutex, unordered_map<string, Hitcounts>>& bucket_content)
        : guard(bucket_content.first)
        , ref_to_value(bucket_content.second[key]) {}

SyncIndex::SyncIndex() : data(26) {}

Access SyncIndex::operator[](const string& key) {
    auto& bucket = data[key[0] - 'a'];
    return {key, bucket};
}

bool SyncIndex::Find(const string& word) const{
    return data[word[0] - 'a'].second.find(word) != data[word[0] - 'a'].second.end();
}

unordered_map<string, Hitcounts> SyncIndex::BuildOrdinaryMap() {
    unordered_map<string, Hitcounts> result;
    for (auto& [mtx, mapping] : data) {
        auto g = Lock(mtx);
        result.insert(begin(mapping), end(mapping));
    }
    return result;
}

void SyncIndex::FillHitcount() {
    for (auto& [mtx, mapping] : data) {
        auto g = Lock(mtx);
        for (auto& [word, idx] : mapping){
            for (auto& id : idx.first){
                idx.second[id]++;
            }
        }
    }
}