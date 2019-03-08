/*
 * 10 100 45 55 245 35 25 10 10 10 26
 * 2600+
 *
 * 10 10 10 10 10 10 10 10 10 10 10
 * 100+
 *
 * 26 3 3 3 3 3 3 3 10 10 3 3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 2
 * 30+
 *
 * 25 3 3 3 3 3 3 3 10 3 3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 2
 * 20+
 *
 * 25 3 3 3 3 3 3 3 10 3 3 3 3 3 3 3 100 1 1 1 1 1 1 1 1 2
 * 1000+
 *
 * 24 3 3 3 3 3 3 3 10 3 3 3 3 3 3 100 1 1 1 1 1 1 1 1 2
 * 300+
 *
 * 24 3 3 3 3 3 3 3 10 3 3 3 3 3 3 100 1 1 1 1 1 1 1 1 5
 * 500+
 *
 * 24 3 3 3 3 3 3 10 10 3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 2
 * 20+
 *
 * 24 3 3 10 3 3 3 10 3 3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 2
 * 30+
 *
 * 9 1 2 3 4 5 6 7 8 9
 * 9+
 *
 * 9 0 0 0 0 0 0 0 0 0
 * 0+
 *
 * 10 3 7 10 10 10 10 10 10 10 6
 * 42+
 *
 */
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

void ProcedeNewItem (int new_item_value, int new_item_index,
					 vector<int>& max_nums_values, vector<int>& max_nums_indexes) {
	int min_value = 1000; 			//Значение каждого элемента последовательности <= 1000
	int min_index_in_values_array = 0;
	for (int i = 0; i < 8; i++) {			//Можно улучшить, отказавшись от поиска минимума, если он не менялся
		if (max_nums_values[i] < min_value) {
			min_value = max_nums_values[i];
			min_index_in_values_array = i;
		}
	}
	if (new_item_value > min_value) {
		max_nums_values[min_index_in_values_array] = new_item_value;
		max_nums_indexes[min_index_in_values_array] = new_item_index;
	}
}

int CountMaxPairResult (const vector<int>& max_nums_values, const vector<int>& max_nums_indexes,
						int item_value, int item_index) {
	int max_result = 0;
	for (int i = 0; i < 8; i ++) {
		if ( abs(max_nums_indexes[i] - item_index) >= 8) {
			if (max_result < item_value * max_nums_values[i]) {
				max_result = item_value * max_nums_values[i];
			}
		}
	}
	return max_result;
}

void PrintVector(const vector<int>& v) {
	cout << "[ ";
	for (const auto& i : v) {
		cout << i << ", ";
	}
	cout << " ]";
}

int GetRandTime(uint64_t num) {
	int start_time_r =  clock();
	for (uint64_t i = 0; i < num; i++) {
		rand() % 1000 + 1;
	}
	int end_time_r = clock();
	int search_time_r = end_time_r - start_time_r;
	return search_time_r;
}

void MeasureTimes() {

	vector<int> nums;
	vector<int> times;

	for (int num = 9; num <= 1000000009; num += 50000000) {

		int rand_time = GetRandTime(num);

		int start_time =  clock();
		int n = num;
		//cin >> n;
		vector<int> max_nums_values(8, 0);
		vector<int> max_nums_indexes(8,-1);
		int max_result = 0;
		for (int i = 0; i < n; i++) {
			int item = rand() % 1000 + 1;
			//cin >> item;
			int moment_max_result = CountMaxPairResult(max_nums_values, max_nums_indexes, item, i);
			if (max_result < moment_max_result) {
				max_result = moment_max_result;
			}
			ProcedeNewItem(item, i, max_nums_values, max_nums_indexes);
		}
		//cout << endl;
		//PrintVector(max_nums_values);
		//cout << endl;
		//PrintVector(max_nums_indexes);
		//cout << endl << endl;
		//cout << max_result << endl;
		int end_time = clock();
		int search_time = end_time - start_time - rand_time;
		//cout << search_time << endl << endl;
		nums.push_back(num);
		times.push_back(search_time);
	}
	PrintVector(nums);
	cout << endl;
	PrintVector(times);
}

int main() {

	//MeasureTimes();

	int n;
	cin >> n;
	vector<int> max_nums_values(8, 0);
	vector<int> max_nums_indexes(8,-1);
	int max_result = 0;
	for (int i = 0; i < n; i++) {
		int item;
		cin >> item;
		int moment_max_result = CountMaxPairResult(max_nums_values, max_nums_indexes, item, i);
		if (max_result < moment_max_result) {
			max_result = moment_max_result;
		}
		ProcedeNewItem(item, i, max_nums_values, max_nums_indexes);
	}
	cout << endl;
	PrintVector(max_nums_values);
	cout << endl;
	PrintVector(max_nums_indexes);
	cout << endl;
	cout << max_result;

	return 0;
}
