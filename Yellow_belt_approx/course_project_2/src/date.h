#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdint>

using namespace std;

class Date {
public:
  Date(const uint16_t& new_year, const uint16_t& new_month, const uint16_t& new_day);
  uint16_t GetYear() const;
  uint16_t GetMonth() const;
  uint16_t GetDay() const;

  uint16_t year;
  uint16_t month;
  uint16_t day;
};

Date ParseDate(istream& date);

ostream& operator<<(ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);
