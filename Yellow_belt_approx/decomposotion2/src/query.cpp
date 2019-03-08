#include <iostream>
#include "query.h"
using namespace std;

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
	string command;
	is >> command;
	q.bus.clear();
	q.stop.clear();
	q.stops.clear();
	if (command == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		for (int i = 0; i < stop_count; i++) {
			string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
		return is;
	}
	else if (command == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
		return is;
	}
	else if (command == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
		return is;
	}
	else if (command == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
		return is;
	}
  return is;
}

