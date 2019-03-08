#pragma once

#include "date.h"
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


//bool operator < (const pair<Date, vector<string>>& lhs, const Date& rhs);

ostream& operator << (ostream& stream, const pair<Date, string>& date_event);


class Database {
public:
  void Add(const Date& date, const string& event);

  template <class Predicate>
  vector<pair<Date, string>> FindIf(const Predicate& predicate) const {
	  vector<pair<Date, string>> found_events;
	  for (const auto& date : order) {
		  for (const auto& event : date.second) {
			  if (predicate(date.first, event)) {
				  found_events.push_back(make_pair(date.first, event));
			  }
		  }
	  }
	  return found_events;
  }

  template <class Predicate>
  int RemoveIf(const Predicate& predicate) {
		//vector<Date> empty_dates;

		unsigned deleted_events = 0;
		auto order_it = order.begin();
		for (auto stor_it = storage.begin(); stor_it != storage.end();) {


			//Date current_date = stor_it->first;
			set<string>& set_events = stor_it->second;
			//cerr << "deleting in date= " << current_date << endl;

			unsigned init_size = set_events.size();
			unsigned deleted_events_in_date = 0;
			for (auto it = set_events.begin(); it != set_events.end();) {
				if (predicate(stor_it->first, *it)) {
					it = set_events.erase(it);
					deleted_events_in_date++;
				} else {
					++it;
				}
			}
			deleted_events += deleted_events_in_date;
			//cerr << stor_it->first << ": deleted " << deleted_events_in_date << " size " << init_size << endl;
			if (deleted_events_in_date == init_size) {
				//empty_dates.push_back(stor_it->first);
				order_it = order.erase(order_it);
				//cerr << stor_it->first << " erased" << endl;
				stor_it = storage.erase(stor_it);
			}

			else {
				vector<string>& events = order_it->second;

				auto predicate_in_set =
						[set_events](const string& event) {return
							set_events.find(event) == set_events.end();};

				//auto predicate_in_date =
				//			[predicate, current_date](const string& event) {return
				//				predicate(current_date, event);};

				auto new_end_of_vector = remove_if(events.begin(), events.end(),
						[predicate_in_set]
						(const string& event)
						{	return predicate_in_set(event);});
				events.erase(new_end_of_vector, events.end());
				++stor_it;
				++order_it;
			}

		}

		return deleted_events;
	}

  pair<Date, string> Last(const Date& date) const;

  void Print(ostream& os) const;

private:
  //map<Date, pair<set<string>,vector<string>>> storage;
  map<Date, set<string>> storage;
  map<Date, vector<string>> order;
};

