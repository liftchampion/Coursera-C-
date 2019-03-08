#include <vector>
#include <map>
#include <utility>
#include <iostream>
using namespace std;

template<typename T> T Sqr(T arg);
template <typename T> vector<T> Sqr (const vector<T>& arg);
template <typename First, typename Second> map<First, Second> Sqr (const map<First, Second>& arg);
template <typename First, typename Second> pair<First, Second> Sqr (const pair<First, Second>& arg);

template <typename T>
T Sqr(T arg) {
	return arg * arg;
}
template <typename T>
vector<T> Sqr (const vector<T>& arg) {
	vector<T> result;
	for (const auto& i : arg) {
		result.push_back(Sqr(i));
	}
	return result;
}
template <typename First, typename Second>
map<First, Second> Sqr (const map<First, Second>& arg) {
	map<First, Second> result;
	for (const auto& i : arg) {
		result[i.first] = Sqr(i.second);
	}
	return result;
}
template <typename First, typename Second>
pair<First, Second> Sqr (const pair<First, Second>& arg) {
	pair<First, Second> result;

	result.first = Sqr(arg.first);
	result.second = Sqr(arg.second);

	return result;
}




/*
int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}*/
