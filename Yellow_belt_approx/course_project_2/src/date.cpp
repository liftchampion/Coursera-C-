#include "date.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

// конструктор НЕ выбрасывает исключение, если его аргументы некорректны
Date::Date(const uint16_t& new_year, const uint16_t& new_month, const uint16_t& new_day) {
	year = new_year;

	month = new_month;

	day = new_day;
}

uint16_t Date::GetYear() const {
	return year;
}
uint16_t Date::GetMonth() const {
	return month;
}
uint16_t Date::GetDay() const {
	return day;
}

Date ParseDate(istream& date_stream) {

	uint16_t year;
	date_stream >> year;
	//cerr << year << endl;
	date_stream.ignore(1);

	uint16_t month;
	date_stream >> month;

	//cerr << month << endl;
	date_stream.ignore(1);

	uint16_t day;
	date_stream >> day;
	//cerr << day << endl;

	//cerr << Date(year, month, day) << endl;
	return Date(year, month, day);
}



ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.year << "-" << setw(2)
			<< setfill('0') << date.month << "-" << setw(2) << setfill('0')
			<< date.day;
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	// воспользуемся тем фактом, что векторы уже можно сравнивать на <:
	// создадим вектор из года, месяца и дня для каждой даты и сравним их
	return tie(lhs.year, lhs.month, lhs.day)
			< tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
	// воспользуемся тем фактом, что векторы уже можно сравнивать на ==:
	// создадим вектор из года, месяца и дня для каждой даты и сравним их
	return tie(lhs.year, lhs.month, lhs.day)
				== tie(rhs.year, rhs.month, rhs.day);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	// воспользуемся тем фактом, что векторы уже можно сравнивать на >=:
	// создадим вектор из года, месяца и дня для каждой даты и сравним их
	return tie(lhs.year, lhs.month, lhs.day)
				>= tie(rhs.year, rhs.month, rhs.day);
}


