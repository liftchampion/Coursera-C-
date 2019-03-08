#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.find(start) == reachable_lists_.end()) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);

    if (!reachable_stations.empty()) {


        auto nearest_it_lower = reachable_stations.lower_bound(finish);
        auto nearest_it_lower_prev = nearest_it_lower;
        if (nearest_it_lower != reachable_stations.begin()) {
        	nearest_it_lower_prev = prev(nearest_it_lower);
        }

        auto nearest_it_upper = reachable_stations.upper_bound(finish);
        auto nearest_it_upper_prev = nearest_it_upper;
        if (nearest_it_upper != reachable_stations.begin()) {
        	nearest_it_upper_prev = prev(nearest_it_upper);
        }
			set<int> distances;
			if (nearest_it_lower != reachable_stations.end()) {
				distances.insert(abs(finish - *nearest_it_lower));
			}
			if (nearest_it_lower_prev != reachable_stations.end()) {
				distances.insert(abs(finish - *nearest_it_lower_prev));
			}
			if (nearest_it_upper != reachable_stations.end()) {
				distances.insert(abs(finish - *nearest_it_upper));
			}
			if (nearest_it_upper_prev != reachable_stations.end()) {
				distances.insert(abs(finish - *nearest_it_upper_prev));
			}

      result = min(
          result,
		  *distances.begin()
          /*abs(finish - *min_element(
              begin(reachable_stations), end(reachable_stations),
              [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
          ))*/
      );
    }
    return result;
  }
private:
  map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
