#pragma once

#include <future>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstdint>
#include <algorithm>
using namespace std;

auto Lock(mutex& m);

using Hitcounts = pair<vector<uint16_t>, unordered_map<uint16_t, uint16_t>>;

struct Access {
    lock_guard<mutex> guard;
    Hitcounts& ref_to_value;

    Access(const string& key, pair<mutex, unordered_map<string, Hitcounts>>& bucket_content);
};

class SyncIndex {
public:

    explicit SyncIndex();

    Access operator[](const string& key);

    unordered_map<string, Hitcounts> BuildOrdinaryMap();

    bool Find(const string& word) const;

    void FillHitcount();

private:
    vector<pair<mutex, unordered_map<string, Hitcounts>>> data;
};


template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T())
            : value(move(initial))
    {
    }

    struct Access {
        T& ref_to_value;
        lock_guard<mutex> guard;
    };

    Access GetAccess() {
        return {lock_guard(m), value};
    }

private:
    T value;
    mutex m;
};