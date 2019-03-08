#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>
#include <list>
#include <climits>
#include "profile.h"

using namespace std;

template <typename T>
struct Object {
    Object(T& object, size_t number) {
        number_ = number;
        object_ = move(object);
    }
    T object_;
    size_t number_;
};

template <class T>
ostream& operator << (ostream& os, const Object<T>& o) {
    os << "{";
    cout << o.object_ << " " << o.number_;
    return os << "}";
}


template <typename Id>
bool operator<(Id lhs, Id rhs) {
    return lhs->number_ > rhs->number_;
}

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;
  PriorityCollection(){
      data_.reserve(MAX_SIZE);
      priorities = vector<int>(MAX_SIZE, 0);
      is_valid = vector<bool>(MAX_SIZE, false);
  }



  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
      data_.push_back(move(object));
      is_valid[data_.size() - 1] = true;
      priorities[data_.size() - 1] = 0;

      priors[0].insert(data_.size() - 1);


      PrintLog();

      return data_.size() - 1;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {

      for (auto it = range_begin; it != range_end; it++ ) {
          *ids_begin = Add(move(*it));
          ids_begin++;
      }

  };

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
      return is_valid[id];
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
      return data_[id];
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      int curr_prior = priorities[id];
      auto it = priors.find(curr_prior);

      it->second.erase(id);
      if (it->second.size() == 0) {
          priors.erase(it);
      }
      priors[++curr_prior].insert(id);
      priorities[id]++;
      PrintLog();
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {

  };

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {

      auto last_prior_it = prev(priors.end());
      auto last_item_it = prev(last_prior_it->second.end());
      size_t last_item_id = *last_item_it;

      last_prior_it->second.erase(last_item_it);
      if (last_prior_it->second.size() == 0) {
          priors.erase(last_prior_it);
      }

      //Id id = FindLastMaxId();
      is_valid[last_item_id] = false;
      PrintLog();
      return pair<T, int>(move(data_[last_item_id]), priorities[last_item_id]);
  };


private:
    // Приватные поля и методы
    const size_t MAX_SIZE = 2000000;
    vector<T> data_;
    vector<int> priorities;
    vector<bool> is_valid;
    map<int, set<size_t>> priors;

    //unordered_set<size_t> valid_ids;
    int FindMaxPrior() const{
        int max_prior = INT_MIN;
        for (size_t i = 0; i < MAX_SIZE; i++) {
            if (is_valid[i]) {
                if (priorities[i] > max_prior) {
                    max_prior = priorities[i];
                }
            }
        }
        //cout << "max prior " << max_prior << endl;
        return max_prior;
    }
    Id FindLastMaxId() const {
        int max_prior = FindMaxPrior();
        Id index = 0;
        for (size_t i = data_.size() - 1; i >= 0; i--) {
            if (is_valid[i]) {
                if (priorities[i] == max_prior) {
                    index = i;
                    break;
                }
            }
        }
        //cout << "max prior ID " << index << endl;
        return index;
    }
    void PrintLog() {
        /*cout << data_ << endl;
        cout << is_valid << endl;
        cout << priorities << endl;
        cout << priors << endl;
        cout << data_.size() - 1 << endl;
        cout << endl;*/
    }


};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");


  PriorityCollection<string> strings2;
  vector<string> strs = {"hello", "brave", "world"};
  vector<size_t> ids;
  strings2.Add(strs.begin(), strs.end(), back_inserter(ids));
  for (auto id : ids) {
      cout << strings2.Get(id) << endl;
  }

  cout << strings.Get(red_id) << endl;
    cout << strings.IsValid(red_id) << endl;
    cout << strings.IsValid(6u) << endl;

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  //cout << strings.GetMax() << endl;
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  //cout << strings.IsValid(red_id) << endl;
  cout << "~~~1~~~" << endl;
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
    cout << "~~~2~~~" << endl;
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "");
    ASSERT_EQUAL(item.second, 0);
  }
    cout << "~~~3~~~" << endl;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);


    /*{
        LOG_DURATION("to string");
        for (int i = 0; i < 1000000; i++) {
            //string tmp = to_string(i % 10) + to_string(i % 9) + to_string(i % 8) + to_string(i % 7) + to_string(i % 6) + to_string(i % 5) + to_string(i % 4) + to_string(i % 3) + to_string(i % 2) + to_string(i % 1);
                    string tmp = to_string(i);
        }
    }
    set<string> ss;
    {
        LOG_DURATION("set insert");
        for (int i = 0; i < 1000000; i++) {
            ss.insert(to_string(i));
        }
    }
    cout << ss.size() << endl;
  vector<int64_t> ints(1000000, 0);
    {
        LOG_DURATION("scan vector");
        find_if(ints.begin(), ints.end(), [](size_t x){return x == 1;});
    }*/

  PriorityCollection<int> strings;
    {
        LOG_DURATION("add 500000");
        for (int i = 0; i < 500000; i++) {
            strings.Add(i);
        }
    }
    {
        LOG_DURATION("pop 500000");
        for (int i = 0; i < 500000; i++) {
            strings.PopMax();
        }
    }

    {
        LOG_DURATION("pop bottom total");
        PriorityCollection<int> strings;
        auto hello_id = strings.Add(-1);
        strings.Promote(hello_id);
        {
            LOG_DURATION("add in pop bottom");
            for (int i = 0; i < 1000000; i++) {
                strings.Add(i);
            }
        }
        {
            LOG_DURATION("is_valid");
            for (int i = 0; i < 1000000; i++) {
                strings.IsValid(hello_id);
            }
        }
        LOG_DURATION("pop bottom");
        strings.PopMax();
    }
  return 0;
}