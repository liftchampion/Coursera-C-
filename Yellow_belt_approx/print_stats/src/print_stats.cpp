#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
/*
enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}*/


void PrintStats(const vector<Person>& pers) {

	{
		cout << "Median age = " <<
				ComputeMedianAge(begin(pers), end(pers)) <<
				endl;
	}

	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::FEMALE;
						});
		cout << "Median age for females = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::MALE;
						});
		cout << "Median age for males = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::FEMALE &&
							   person.is_employed == true;
						});
		cout << "Median age for employed females = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::FEMALE &&
							   person.is_employed == false;
						});
		cout << "Median age for unemployed females = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::MALE &&
							   person.is_employed == true;
						});
		cout << "Median age for employed males = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
	{
		vector<Person> good_data;
		vector<Person> thrash;
		partition_copy(begin(pers), end(pers),
						back_inserter(good_data),
						back_inserter(thrash),
						[](Person person) {
						return person.gender == Gender::MALE &&
							   person.is_employed == false;
						});
		cout << "Median age for unemployed males = " <<
				ComputeMedianAge(begin(good_data), end(good_data)) <<
				endl;
	}
}

/*
int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}*/
