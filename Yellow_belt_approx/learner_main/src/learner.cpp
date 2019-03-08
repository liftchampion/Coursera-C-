#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.find(word) == dict.end()) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    //sort(dict.begin(), dict.end());
    //dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return vector<string>(dict.begin(), dict.end());
  }
};
