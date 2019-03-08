#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <algorithm>
//#include "profiler.h"

using namespace std;


void ProcedeNewSportsman(list<size_t>& s_men, size_t new_s, size_t pos, vector<list<size_t>::iterator>& iterators) {
   /* if (s_men.size() == 0) {
        auto new_it = s_men.insert(s_men.begin(), new_s);
        iterators[new_s] = new_it;
        return;
    }*/
    auto pos_iter = iterators[pos];
    auto new_it = s_men.insert(pos_iter, new_s);
    iterators[new_s] = new_it;


}

template <class T>
ostream& operator << (ostream& stream, const list<T>& l) {
    for (const auto& i : l) {
        stream << i << " ";
    }
    return stream;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*LOG_DURATION("Total");
    list<size_t> sports;
    vector<list<size_t>::iterator> iterators(100001, sports.end());


    {
        LOG_DURATION("read 100000");
        for (size_t i = 0; i < 100000; i++) {
            ProcedeNewSportsman(sports, i, i, iterators);
        }
    }
    {
        LOG_DURATION("Print 100000");
        //cout << sports;
    }*/




    size_t q;
    cin >> q;
    list<size_t> sports;
    vector<list<size_t>::iterator> iterators(100001, sports.end());
    for (size_t i = 0; i < q; i++) {
        size_t num;
        size_t pos;
        cin >> num >> pos;
        ProcedeNewSportsman(sports, num, pos, iterators);
    }
    cout << sports;
    return 0;
}