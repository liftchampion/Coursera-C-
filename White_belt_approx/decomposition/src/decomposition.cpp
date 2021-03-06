#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

/*
 * 6
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo

6
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo1 Marushkino1 Vnukovo1
NEW_BUS 32K 6 Tolstopaltsevo2 Marushkino2 Vnukovo2 Peredelkino2 Solntsevo2 Skolkovo2
BUSES_FOR_STOP Vnukovo
 *
 *
 */

using namespace std;

using BMInside = map<string, vector<string>>;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // ���������� ��� �������
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

struct BusesForStopResponse {
  // ��������� ������ ��� ���������
	BusesForStopResponse () {
		no_stop = false;
	}
	vector<string> buses;
	bool no_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // ���������� ��� �������
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

struct StopsForBusResponse {
  // ��������� ������ ��� ���������
	StopsForBusResponse () {
		no_bus = false;
	}
	BMInside stops;
	bool no_bus;
	vector<string> order;
	string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // ���������� ��� �������
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

struct AllBusesResponse {
  // ��������� ������ ��� ���������
	AllBusesResponse () {
		no_buses = false;
	}
	bool no_buses;
	BMInside stops_for_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // ���������� ��� �������
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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // ���������� ���� �����
	  stops_for_buses[bus] = stops;
	  for (auto& stop : stops) {
		  buses_for_stop[stop].push_back(bus);
		 // cout << "PUSHED NEW BUS " << bus <<" TO buses_for_stops" << "(stop: " << stop << ")" << endl;
	  }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // ���������� ���� �����
	  BusesForStopResponse resp;
	  if (buses_for_stop.count(stop) == 0) {
		  resp.no_stop = true;
		  return resp;
	  }
	  for (const auto& bus : buses_for_stop.at(stop)) {
		  resp.buses.push_back(bus);
		 // cout << "PUSHED NEW BUS TO RESPONSE" << endl;
	  }
	  return resp;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // ���������� ���� �����
	  StopsForBusResponse resp;
	  if (stops_for_buses.count(bus) == 0) {
		  resp.no_bus = true;
		  return resp;
	  }
	  for (const auto& stop : stops_for_buses.at(bus)) {
		  resp.stops[stop] = buses_for_stop.at(stop);
		  resp.order.push_back(stop);
	  }
	  resp.bus = bus;
	  return resp;
  }

  AllBusesResponse GetAllBuses() const {
    // ���������� ���� �����
	  AllBusesResponse resp;
	  if (stops_for_buses.size() == 0) {
		  resp.no_buses = true;
		  return resp;
	  }
	  resp.stops_for_buses = stops_for_buses;
	  return resp;
  }
private:
  BMInside buses_for_stop;
  BMInside stops_for_buses;
};

// �� ����� ���� ������� main, ���������� ������� � ������ ����

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
