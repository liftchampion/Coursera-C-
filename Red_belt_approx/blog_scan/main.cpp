#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;


template<typename Iterator>
class PageClass {
public:
    PageClass(Iterator begin, Iterator end) :
            _begin(begin), _end(end) {
    }
    Iterator begin() const{
        return _begin;
    }
    Iterator end() const{
        return _end;
    }
    size_t size() const{
        return _end - _begin;
    }

private:
    Iterator _begin;
    Iterator _end;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        while (end - begin > page_size) {
            PageClass<Iterator> new_page(begin, begin + page_size);
            pages.push_back(new_page);
            begin += page_size;
        }
        if (begin != end) {
            PageClass<Iterator> new_page(begin, end);
            pages.push_back(new_page);
        }
    }
    auto begin() const{
        return pages.begin();
    }
    auto end() const {
        return pages.end();
    }
    size_t size() const {
        return pages.size();
    }
private:
    vector<PageClass<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}



struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
      for (const auto& [word, count] : other.word_frequences) {
          word_frequences[word] += count;
      }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats freqs;
    string word;
    for (size_t i = 0; i < line.size(); i++) {

        if (line[i] != ' ') {
            word.push_back(line[i]);
        }
        else {
            if (key_words.find(word) != key_words.end()) {
                freqs.word_frequences[word]++;
                //cout << "ADDED" << endl;
            }
            word.clear();
        }
        //cout << word << endl;
    }
    if (key_words.find(word) != key_words.end()) {
        freqs.word_frequences[word]++;
        //cout << "ADDED" << endl;
    }
    return freqs;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreLines(const vector<string>& lines, const set<string>& key_words) {
    Stats stats;
    for (const auto& line : lines) {
        stats += ExploreLine(key_words, line);
    }
    return stats;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  // Реализуйте эту функцию
    vector<vector<string>> lines(4);
    int count = 0;
    for (string line; getline(input, line); ) {
        lines[count / 5000].push_back(line);
        count++;
    }

    vector<future<Stats>> futures;
    for (auto thread : lines) {
        futures.push_back(async([=] { return ExploreLines(thread, key_words); }));
    }
    Stats word_frequences;
    for (auto& future : futures) {
        word_frequences += future.get();
    }
    return word_frequences;

}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 7},
    {"rocks", 3},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
