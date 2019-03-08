#include <iostream>
#include "responses.h"
using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
	if (r.no_stop) {
		os << "No stop";
	}
	bool first = true;
	for (const auto& bus : r.buses) {
		if (!first) {
			os << " ";
		}
		if (first) {
			first = false;
		}
		os << bus;
	}
	//os << endl;
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
	if (r.no_bus) {
		os << "No bus";
	}
	bool first = true;
	for (const auto& stop : r.order) {
		if (!first) {
			os << endl;
		}
		if (first) {
			first = false;
		}
		os << "Stop " << stop <<":";
		if (r.stops.at(stop).size() == 1) {
			os << " no interchange";
		}
		else {
			for (const auto& bus : r.stops.at(stop)) {
				if (bus != r.bus) {
					os << " " << bus;
				}
			}
		}
	}
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
	if (r.no_buses) {
		os << "No buses";
		return os;
	}
	bool first = true;
	for (const auto& bus_stops : r.stops_for_buses) {
		if (!first) {
			os << endl;
		}
		if (first) {
			first = false;
		}
		os << "Bus " << bus_stops.first << ":";
		for (const auto& stop : bus_stops.second) {
			os << " " << stop;
		}
	}
  return os;
}
