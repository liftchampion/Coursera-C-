#include "profiler.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

chrono::duration<long long int, std::ratio<1, 1000000000>> GET_COUNT;
chrono::duration<long long int, std::ratio<1, 1000000000>> ADD;
chrono::duration<long long int, std::ratio<1, 1000000000>> SWAP;
int GET_COUNT_CALLED = 0;
int ADD_CALLED = 0;
int SWAP_CALLED = 0;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    // �� ��������� ������� �������������, �������
    // ����� �������� ��������� � ���� double.
    // ������� ������ ������� ��� � �������� ��� �� 1.0.
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // ����������� ���� �� ����������� ������-�� �����������
  // ������� ������. �� ���� ��� ���������� ����������,
  // � ������ ������ �����������.
  // ���� ��� ���������, � ��� ����� ���� �� ���������� �������
  // ��������� �������: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // ������������� �� �������� ���������� �������
  vector<int> user_positions_; // ������� � ������� sorted_users_

  int GetUserCount() const {
	  GET_COUNT_CALLED++;
	  auto start = steady_clock::now();
	  //LOG_DURATION("GET USER COUNT");
	  int result = sorted_users_.size();
	  auto finish = steady_clock::now();
	  GET_COUNT += finish - start;
    return result;
  }
  void AddUser(int user_id) {
	  //LOG_DURATION("ADD USER");
	  ADD_CALLED++;
	  auto start = steady_clock::now();

    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
	  auto finish = steady_clock::now();
	  ADD += finish - start;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
	  //LOG_DURATION("SWAP USER");
	  SWAP_CALLED++;
	  auto start = steady_clock::now();

    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);

	  auto finish = steady_clock::now();
	  SWAP += finish - start;
  }
};


int main() {
  // ��� ��������� ������ ������ ����������� �������������
  // cin � cout � stdio,
  // � ����� ����������� ������� cin �� cout

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
	cerr << endl << duration_cast<milliseconds>(GET_COUNT).count() << " G_C" << endl;
	cerr << duration_cast<milliseconds>(ADD).count() << " ADD" << endl;
	cerr << duration_cast<milliseconds>(SWAP).count() << " SWAP" << endl;
	cerr << GET_COUNT_CALLED << endl;
	cerr << ADD_CALLED << endl;
	cerr << SWAP_CALLED << endl;



 /* ios::sync_with_stdio(false);
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
