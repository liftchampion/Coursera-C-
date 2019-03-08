#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#include "phone_number.h"

// Write includes

using namespace std;

// Define your functions and classes here

PhoneNumber::PhoneNumber(const string& international_number) {
	stringstream str(international_number);
	if (str.peek() != '+') {
		throw invalid_argument("no plus");
	}
	str.ignore(1);
	getline(str, country_code_, '-');
	getline(str, city_code_, '-');
	getline(str, local_number_);
	if (city_code_.size() == 0 || country_code_.size() == 0 || local_number_.size() == 0) {
		throw invalid_argument("no part");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	string int_number;
	int_number += "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
	return int_number;
}




