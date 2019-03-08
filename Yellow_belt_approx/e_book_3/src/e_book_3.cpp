//#include "profiler.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;
/*
void PrintVectorHead(const vector<int>& v){
	for (int i = 0; i < 18; i++) {
		cerr << v[i] << " ";
	}
	cerr << endl;
}*/

class ReadingManager {
public:
	ReadingManager() : pages_to_count(1001, 0){}

	void Read(int user_id, int page_count) {
		auto result_of_insert = users_to_count.insert(make_pair(user_id, page_count));
		if (result_of_insert.second) {
			for (int i = 0; i <= page_count; i++) {
				pages_to_count[i]++;
			}
		}
		else {
			for (int i = result_of_insert.first->second + 1; i <= page_count; i++) {
				pages_to_count[i]++;
			}
			result_of_insert.first->second = page_count;
		}
		//PrintVectorHead(pages_to_count);
	}

	double Cheer(int user_id) const {
		if (users_to_count.find(user_id) == users_to_count.end()) {
			return 0.0;
		}
		if (users_to_count.size() == 1) {
			return 1.0;
		}
		int pages_read = users_to_count.at(user_id);
		int people_read_this_page = pages_to_count[pages_read];
		int people_not_read_this_page = users_to_count.size() - people_read_this_page;
		return people_not_read_this_page * 1.0 / (users_to_count.size() - 1);
	}

private:
	map<int, int> users_to_count;
	vector<int> pages_to_count;
};

int main() {
	// Для ускорения чтения данных отключается синхронизация
	// cin и cout с stdio,
	// а также выполняется отвязка cin от cout
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}
