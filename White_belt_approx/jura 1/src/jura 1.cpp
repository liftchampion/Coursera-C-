//============================================================================
// Name        : jura.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

void PrintResults(const vector<int>& r) {
	for (int i = 1; i <= r.size(); i++) {
		cout << "Pair #" << i << " has " << r[i-1] << " votes" << endl;
	}
}

void ReadResults(vector<int>& pairs_results) {
	int num_sms;
	cin >> num_sms;
	for (int i = 0; i < num_sms; i++) {
		int current_sms;
		cin >> current_sms;
		pairs_results[current_sms - 1]++;
	}
}

void PrintPlaces(const vector<int>& places) {
	for (int i = 0; i < places.size(); i++) {
		cout << "Pair #" << i + 1 << " is in " << places[i] << " place" << endl;
	}
}

void PrintFinalResults(const vector<int>& places) {
	int used_pairs = 0;
	int place = 1;										//начинаем вывод с первого места и увеличиваем на 1 каждую итерацию
	while (used_pairs < places.size()) {				//пока не использовали все пары
		bool is_empty = true;						//!!! переменная, отвечающая за то, что на это место никого не нашлось
		cout << place << " place - pairs #:";			//а т.к. пары ещё не закончились, очевидно, что остались только пары
		for (int j = 0; j < places.size(); j++) {		//без голосов, следовательно выведем их на это место, как на
			if (places[j] == place) {					//следующее после последнего заполненного
				cout << " " << j + 1;
				used_pairs++;							//Идём по всем парам. Если у пары это место, выводим ее на экран
				is_empty = false;						//Если нашлось какую пару вывести, то это не пустое место
			}
		}
		if (is_empty == true) {							//если после цикла место осталось пустым, то см. выше
			for (int j = 0; j < places.size(); j++) {
				if (places[j] == -1) {
					cout << " " << j + 1;
				}
			}
			break;
		}
		place++;
		cout << endl;
	}
}

vector<int> ProcedeResults (vector<int>& pairs_results) {
	vector<int> places(pairs_results.size(), -1);			//По дефолту место каждой пары = -1
	int used_pairs = 0;
	int place = 1;
	while (used_pairs < pairs_results.size()) {				//Пока не присвоили места всем парам
		int max_points = 0;									//Находим максимум очков для данной итерации
		for (int j = 0; j < pairs_results.size(); j++) {
			if (pairs_results[j] > max_points) {
				max_points = pairs_results[j];
			}
		}
		//cout << "new max points = " << max_points << endl;
		if (max_points == 0) {								//Если найденный максимум голосов - 0
			break;												//То голосов больше нет, можно закончить
		}
		for (int j = 0; j < pairs_results.size(); j++) {	//Всем парам, имеющим текущий максимум голосов
			if (pairs_results[j] == max_points) {				//Присваиваем текущее место (сначала = 1,
				places[j] = place;								//Для каждого нового максимума место увеличвается на 1
				pairs_results[j] = -1;						//Изменяем количество голосов данной пары на -1
				//cout << " pair: " << j + 1 << endl;			//Чтобы максимум для следующего места нашёлся корректно
				used_pairs++;								//Увеличиваем на 1 счетчик использованных пар за
			}													//каждую использованную пару
		}
		place++;											//По завершении функции получим массив, где
	}														//парам, за которые голосовали будет присвоено
	return places;											//соответсвющее место, остальным - "-1"
}

/*void MoveToPlace (vector<int>& places, const vector<int>& pairs_results, int pair_number) {
	for (int i = 0; i < places.size(); i++) {
		if (places[i] == -1) {
			places[i] = pair_number;
		}
		else if (pairs_results[pair_number] == pairs_results[places[i] % 10]) {
			places[i] = places[i] * 10 + pair_number;
		}
	}
}*/

void ReadRandomResults(vector<int>& results, uint64_t num_sms, int num_pairs) {
	for (uint64_t i = 0; i < num_sms; i++) {
		int current_sms = rand() % num_pairs + 1;
		results[current_sms - 1]++;
	}
}

int GetRandTime(uint64_t n) {
	int start_time_r =  clock();
	for (uint64_t i = 0; i < n; i++) {
		int a = rand() % 16 + 1;
	}
	int end_time_r = clock();
	int search_time_r = end_time_r - start_time_r;
	return search_time_r;
}

int DoTask(uint64_t num_sms, int num_pairs) {

	vector<int> pairs_results(num_pairs);

	ReadRandomResults(pairs_results, num_sms, num_pairs); //Считываем реузьтаты с помощью цикла for и ++
	int start_time =  clock();								//Запись в ведём в массив, где индекс это номер пары - 1
	//PrintResults(pairs_results);							//А значение - количество голосов
	vector<int> places = ProcedeResults(pairs_results);	  //Обрабатываем результаты, назначая каждой паре -
	//cout << endl;											//(индекс в новом массиве) номер места
	//PrintPlaces(places);									// см. комменты к функции
	//cout << endl;
	PrintFinalResults(places);							  //Выводим соответсвие мест парам в правильном
	cout << endl;											//порядке
	int end_time = clock();									//см. комменты к функции
	return end_time - start_time;

}

void PrintVectorLong(const vector<uint64_t> v) {
	for (const uint64_t i : v) {
		cout << i << " ";
	}
	cout << endl;
}
void PrintVector(const vector<int> v) {
	for (const int i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	uint64_t i = 1;
	uint64_t result = 1000000;
	vector<uint64_t> nums_sms;
	vector<int> times;
	while (i <= 1000000) {
		//result += pow(i,8);
		//cout << i << " " << result << endl;
		//int rand_time = GetRandTime(result);
		int task_time = DoTask(result, i);

		cout << task_time << endl;
		times.push_back(task_time);
		nums_sms.push_back(i);
		i += 62500;
	}
	PrintVectorLong(nums_sms);
	PrintVector(times);
		/*int start_time_r =  clock();
		for (int i = 0; i < 100000; i++) {
			int a = rand() % 16 + 1;
		}
		int end_time_r = clock();
		int search_time_r = end_time_r - start_time_r;
		cout << search_time_r << endl;


		int start_time =  clock();
		vector<int> pairs_results(16);
		//ReadResults(pairs_results);
		//ReadRandomResults(pairs_results);
		PrintResults(pairs_results);
		vector<int> places = ProcedeResults(pairs_results);
		cout << endl;
		PrintPlaces(places);
		cout << endl;
		PrintFinalResults(places);
		cout << endl;
		int end_time = clock();
		int search_time = end_time - start_time;
		cout << search_time << endl;
		cout << "Time is " << (search_time - search_time_r)/1000 << "s " <<
			(search_time - search_time_r) % 1000 << "ms" << endl;*/
	return 0;
}
