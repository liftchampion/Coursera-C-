#include "database.h"
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;

/*
bool operator <(const pair<Date, vector<string>>& lhs, const Date& rhs) {
	return lhs.first < rhs;
}*/

ostream& operator << (ostream& stream, const pair<Date, string>& date_event) {
	return stream << date_event.first << " " << date_event.second;
}

void Database::Add(const Date& date, const string& event) {
	//vector<string> tmp_v;
	//set<string> tmp_s;
	/*auto result_of_insert_to_map = storage.insert(make_pair(date,
					make_pair(set<string> (),vector<string> ())));
	auto map_iterator = result_of_insert_to_map.first;

	auto result_of_insert_to_set = map_iterator->second.first.insert(event);
	if (result_of_insert_to_set.second) {
		map_iterator->second.second.push_back(event);
	}*/

	auto result_of_insert = storage[date].insert(event);
	if (result_of_insert.second) {
		order[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (const auto& date : order) {
		for (const string& event : date.second) {
			os << date.first << " " << event << endl;
		}
	}
}

pair<Date, string> Database::Last(const Date& date) const {
	//cerr << "called Last" << endl;
	if (order.empty()) {
		throw invalid_argument("no entries at all");
	}
	//cerr << "empty checked" << endl;
	Date date_begin = order.begin()->first;
	if (date < date_begin) {
		throw invalid_argument("no entries before this date");
	}
	//cerr << "< begin checked" << endl;
	if (date == date_begin) {
		return make_pair(date, order.begin()->second.back());
	}
	//cerr << "== begin checked" << endl;
	Date date_end = prev(order.end())->first;
	//cerr << "date_end written" << endl;

	if (date >= date_end) {
		return make_pair(date_end, prev(order.end())->second.back());
	}
	//cerr << "end checked" << endl;
	//cerr << "finding lb" << endl;
	//auto lower_b = lower_bound(order.begin(), order.end(), date);
	auto lower_b = order.lower_bound(date);
	//cerr << "lb found" << endl;
	if (lower_b->first == date) {
		return make_pair(date, lower_b->second.back());
	}
	else {
		return make_pair(prev(lower_b)->first, prev(lower_b)->second.back());
	}
}

/*
 * Add 1-1-1 fff
Add 1-1-2 ggg
Add 1-1-3 hhh
Add 1-1-2 aaa
Last 1-1-2
 *
 *
 */

