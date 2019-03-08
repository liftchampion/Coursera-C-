#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <thread>
#include <mutex>
#include <cmath>
using namespace std;

template <typename T>
struct Access {

    T& ref_to_value;
    lock_guard<mutex> guard;
};

template <typename T>
class Synchronized {
public:

    explicit Synchronized(T initial = T())
            : value(move(initial))
    {
    }

    Access<T> GetAccess() {
        //cout << "getting access" << endl;
        return {value, lock_guard(m)};
    }

    mutex m;
private:
    T value;

};


template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    explicit ConcurrentMap(size_t bucket_count)
                    : data(bucket_count)    {
        bucket_count_ = bucket_count;
    }


    Access<V> operator[](const K& key) {
        K key_abs;
        if (key >= 0) {
            key_abs = key;
        }
        else {
            key_abs = - key;
        }
        //cout << key % bucket_count_ << endl;
        //lock_guard<mutex> lock_g(data[key_abs % bucket_count_].m);
        //cout << "locked" << endl;
        //cout << key % bucket_count_;

        Access<map<K, Synchronized<V>>> access_to_submap = data[key_abs % bucket_count_].GetAccess();
        //Access<V> access_to_item = access_to_submap.ref_to_value[key].GetAccess();

        //return data[key_abs % bucket_count_].GetAccess().ref_to_value[key].GetAccess();
        return access_to_submap.ref_to_value[key].GetAccess();
    }

    map<K, V> BuildOrdinaryMap(){
        lock_guard<mutex> lock_build(mut);
        map<K, V> result;


        for (size_t j = 0; j < bucket_count_; j++) {

           /* for (size_t i = 0; i < bucket_count_; i++) {
                if (i != j) {
                    data[i].m.lock();
                }
            }*/

            for (auto& [key, value] : data[j].GetAccess().ref_to_value) {



                result[key] = value.GetAccess().ref_to_value;
            }

            /*for (size_t i = 0; i < bucket_count_; i++) {
                if (i != j) {
                    data[i].m.unlock();
                }
            }*/
        }
        /*for (size_t i = 0; i < bucket_count_; i++) {
            data[i].m.unlock();
        }*/

        return result;
    };

private:
    mutex mut;
    vector<Synchronized<map<K, Synchronized<V>>>> data;
    size_t bucket_count_;
};

void RunConcurrentUpdates(
        ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
    auto kernel = [&cm, key_count](int seed) {
        vector<int> updates(key_count);
        iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key : updates) {
                cm[key].ref_to_value++;
            }
        }
    };

    vector<future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(async(kernel, i));
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result) {
        AssertEqual(v, 6, "Key = " + to_string(k));
    }
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = async(updater);
    auto r1 = async(reader);
    auto u2 = async(updater);
    auto r2 = async(reader);

    u1.get();
    u2.get();

    for (auto f : {&r1, &r2}) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }

    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 30);
        //cout << single_lock.BuildOrdinaryMap() << endl;
    }
    {
        ConcurrentMap<int, int> many_locks(4);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 30);
        //cout << many_locks.BuildOrdinaryMap() << endl;
    }
}

void FillConcMap(ConcurrentMap<int, int>& c_map, int begin, int step, int value) {
    //cout << '\n' << "Filling " << value << endl;
    for (int i = begin; i < 50000; i += step) {
        c_map[i].ref_to_value = value;
    }
    //cout << '\n' << "Filled " << value << endl;
}

void PrintMapSize(ConcurrentMap<int, int>& c_map, map<int, int>& result) {
    //cout << '\n' << "Printing" << endl;
    result = c_map.BuildOrdinaryMap();
    //cout << '\n' << "Printed" << endl;
}

void TestAsync() {
    LOG_DURATION("TestAsync");
    ConcurrentMap<int, int> c_map(4);
    map<int, int> ord_map;
    //FillConcMap(c_map, 0, 1, 1);
    {
        auto fill_0 = async(FillConcMap, ref(c_map), 0, 4, 1);
        auto fill_1 = async(FillConcMap, ref(c_map), 1, 4, 2);
        auto fill_2 = async(FillConcMap, ref(c_map), 2, 4, 3);
        auto fill_3 = async(FillConcMap, ref(c_map), 3, 4, 4);
        //auto fill_05 = async(FillConcMap, ref(c_map), 0, 5);
        //auto fill_15 = async(FillConcMap, ref(c_map), 1, 5);
        //auto fill_25 = async(FillConcMap, ref(c_map), 2, 5);
        //auto fill_35 = async(FillConcMap, ref(c_map), 3, 5);
        //auto build = async(PrintMapSize, ref(c_map), ref(ord_map));
    }
    cout << ord_map.size() << endl;
    cout << c_map.BuildOrdinaryMap().size() << endl;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
    //TestAsync();
}
