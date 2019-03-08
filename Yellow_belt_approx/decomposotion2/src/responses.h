#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

using BMInside = map<string, vector<string>>;

struct BusesForStopResponse {
  // ��������� ������ ��� ���������
	BusesForStopResponse () {
		no_stop = false;
	}
	vector<string> buses;
	bool no_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

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

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  // ��������� ������ ��� ���������
	AllBusesResponse () {
		no_buses = false;
	}
	bool no_buses;
	BMInside stops_for_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
