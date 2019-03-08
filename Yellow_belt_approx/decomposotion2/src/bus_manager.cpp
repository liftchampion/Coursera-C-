#include <iostream>
#include "bus_manager.h"
using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
	  stops_for_buses[bus] = stops;
	  for (auto& stop : stops) {
		  buses_for_stop[stop].push_back(bus);
		 // cout << "PUSHED NEW BUS " << bus <<" TO buses_for_stops" << "(stop: " << stop << ")" << endl;
	  }
  }
BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  // Реализуйте этот метод
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  // Реализуйте этот метод
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

AllBusesResponse BusManager::GetAllBuses() const {
  // Реализуйте этот метод
	  AllBusesResponse resp;
	  if (stops_for_buses.size() == 0) {
		  resp.no_buses = true;
		  return resp;
	  }
	  resp.stops_for_buses = stops_for_buses;
	  return resp;
}
