#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
						RandomIt range_begin, RandomIt range_end,
						char prefix) {





	RandomIt interval_begin = lower_bound(range_begin, range_end, prefix,
											[](string word, char prefix){
											return word[0] < prefix;
											});
	RandomIt interval_end = upper_bound(range_begin, range_end, prefix,
											[](char prefix, string word){
											return prefix < word[0];
											});

	return make_pair(interval_begin, interval_end);
}





template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
						RandomIt range_begin, RandomIt range_end,
						string prefix) {





	RandomIt interval_begin = lower_bound(range_begin, range_end, prefix,
											[](string word, string prefix){
											string word_pref(begin(word), begin(word) + prefix.size());
											return word_pref < prefix;
											});
	RandomIt interval_end = upper_bound(range_begin, range_end, prefix,
											[](string prefix, string word){
											string word_pref(begin(word), begin(word) + prefix.size());
											return prefix < word_pref;
											});

	return make_pair(interval_begin, interval_end);
}





/*
int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;

  const auto v_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'v');
  cout << (v_result.first - begin(sorted_strings)) << " " <<
      (v_result.second - begin(sorted_strings)) << endl;

  return 0;
}*/



int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}
