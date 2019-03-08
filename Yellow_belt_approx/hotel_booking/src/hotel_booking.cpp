//#include "profiler.h"

#include <iostream>
#include <queue>
#include <map>
#include <cstdint>
using namespace std;

struct Entry {
	Entry()
		: time_(0)
		, client_id_(0)
		, room_count_(0) {}

	Entry(const string& hotel, int64_t time, int client_id, int room_count)
		: hotel_(hotel)
		, time_(time)
		, client_id_(client_id)
		, room_count_(room_count) {}

	string hotel_;
	int64_t time_;
	int client_id_;
	int room_count_;
};

struct Hotel {
	Hotel() : rooms_last_day_(0) {}

	map<int, int> clients_to_count;
	int rooms_last_day_;
};

class Booker {
public:
	Booker() : last_time_(0) {}
	void NewBook(const Entry& new_book) {
		last_time_ = new_book.time_;
		//Clean(new_book.time_);
		queries.push(new_book);

		Hotel& current_hotel = hotels_[new_book.hotel_];
		current_hotel.clients_to_count[new_book.client_id_]++;
		current_hotel.rooms_last_day_ += new_book.room_count_;
	}
	int GetClientsCount(const string& hotel_name) {
		Clean(last_time_);
		return hotels_[hotel_name].clients_to_count.size();
	}
	int GetRoomsCount(const string& hotel_name) {
		Clean(last_time_);
		return hotels_[hotel_name].rooms_last_day_;
	}
private:
	int64_t last_time_;
	queue<Entry> queries;
	map<string, Hotel> hotels_;
	void Clean(const int64_t& time) {

		while (queries.front().time_ <= time - 86400 && !queries.empty()) {
			Hotel& current_hotel = hotels_[queries.front().hotel_];
			current_hotel.rooms_last_day_ -= queries.front().room_count_;
			auto it = current_hotel.clients_to_count.find(queries.front().client_id_);
			it->second--;
			if (it->second == 0) {
				current_hotel.clients_to_count.erase(it);
			}
			queries.pop();
		}
	}
};

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Booker hotels;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") {
			int64_t time;
			string hotel_name;
			int client_id;
			int room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			Entry new_book = {hotel_name, time, client_id, room_count};
			hotels.NewBook(new_book);
		}
		else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << hotels.GetClientsCount(hotel_name) <<'\n';
		}
		else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			cout << hotels.GetRoomsCount(hotel_name) << '\n';
		}
	}
	return 0;
}
/*
 *
 * 5
BOOK 10 FourSeasons 1 2
BOOK 86409 FourSeasons 2 1
CLIENTS FourSeasons
ROOMS FourSeasons
ROOMS FourSeasons
 *
 *
 *
 */
