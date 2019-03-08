#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "responses.h"
using namespace std;

using BMInside = map<string, vector<string>>;

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops);
  BusesForStopResponse GetBusesForStop(const string& stop) const;
  StopsForBusResponse GetStopsForBus(const string& bus) const;
  AllBusesResponse GetAllBuses() const;
private:
  BMInside buses_for_stop;
  BMInside stops_for_buses;
};
