#include "profiler.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class ReadingManager {
public:
	ReadingManager() {}

	void Read(int user_id, int page_count) {
		int prev_page_count = -1;

		auto result_of_insert = user_page_counts_.insert(make_pair(user_id, page_count));

		if (!result_of_insert.second) {
			prev_page_count = result_of_insert.first->second;
			result_of_insert.first->second = page_count;
		}

		read_pages_[page_count]++;

		if (prev_page_count != -1) {
			auto prev_pages_it = read_pages_.find(prev_page_count);
			prev_pages_it->second--;
			if (prev_pages_it->second == 0) {
				read_pages_.erase(prev_pages_it);
			}
		}
	}
	double Cheer(int user_id) const {
		if (user_page_counts_.find(user_id) == user_page_counts_.end()) {
			return 0.0;
		}
		if (user_page_counts_.size() == 1) {
			return 1.0;
		}
		int read_by_user = user_page_counts_.at(user_id);
		int count_user_read_less = 0;

		/*auto begin_of_better = read_pages_.lower_bound(read_by_user);
		for (auto it = read_pages_.begin(); it != begin_of_better; it++) {
			count_user_read_less += it->second;
		}*/

		for (const auto& pages_count : read_pages_) {
			if (pages_count.first >= read_by_user) {
				break;
			}
			count_user_read_less += pages_count.second;
		}



		//cerr << user_id << " " << count_user_read_less << " " << user_page_counts_.size() << endl;
		return count_user_read_less * 1.0 / (user_page_counts_.size() - 1);
		// По умолчанию деление целочисленное, поэтому
		// нужно привести числитель к типу double.
		// Простой способ сделать это — умножить его на 1.0.

	}

private:

	map<int, int> user_page_counts_;
	map<int, int> read_pages_;
	//vector<int> user_positions_; // позиции в векторе sorted_users_

	/*int GetUserCount() const {

	}
	void AddUser(int user_id) {

	}
	void SwapUsers(int lhs_position, int rhs_position) {

	}*/
};

int main() {
	// Для ускорения чтения данных отключается синхронизация
	// cin и cout с stdio,
	// а также выполняется отвязка cin от cout




	ReadingManager manager1;
	{
		LOG_DURATION("READ N");
		for(int i = 1; i < 10000; i++) {
			manager1.Read(i, i%10 + 1);
		}
	}
	{
		LOG_DURATION("CHEER N");
		for(int i = 1; i < 10000; i++) {
			manager1.Cheer(i);
		}
	}
	ReadingManager manager2;
	{
		LOG_DURATION("READ 1000");
		for(int i = 1; i < 10000; i++) {
			manager2.Read(i%1000 + 1, i/1000 + i/100 + i/10 + 1);
		}
	}
	{
		LOG_DURATION("CHEER 1000");
		for(int i = 1; i < 10000; i++) {
			manager2.Cheer(i%1000 + 1);
		}
	}
	ReadingManager manager3;
	{
		LOG_DURATION("READ 1");
		for(int i = 1; i < 10000; i++) {
			manager3.Read(1, i/1000 + i/100 + i/10 + 1);
		}
	}
	{
		LOG_DURATION("CHEER 1");
		for(int i = 1; i < 10000; i++) {
			manager3.Cheer(1);
		}
	}
	ReadingManager manager4;
	{
		LOG_DURATION("READ MOST");
		for(int i = 1; i < 10000; i++) {
			manager4.Read(i, i);
		}
	}
	{
		LOG_DURATION("CHEER MOST");
		for(int i = 1; i < 10000; i++) {
			manager4.Cheer(9999);
		}
	}



	/*ios::sync_with_stdio(false);
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
	}*/

	return 0;
}
