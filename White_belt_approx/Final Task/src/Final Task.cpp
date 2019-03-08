#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <exception>
#include <iostream>
#include <sstream>
using namespace std;

class Date {
public:
	Date() {
		year = 1;
		month = 1;
		day = 1;
	}
	Date(int new_year, int new_month, int new_day) {
		year = new_year;
		if (new_month < 1 || new_month > 12) {
			throw runtime_error("Month value is invalid: " +
					to_string(new_month));
		}
		else {
			month = new_month;
		}
		if (new_day < 1 || new_day > 31) {
			throw runtime_error("Day value is invalid: " +
					to_string(new_day));
		}
		else {
			day = new_day;
		}
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
private:
	int year;
	int month;
	int day;
};

ostream& operator << (ostream& stream, const Date& date) {
	stream << setw(4);
	stream << setfill('0');
	stream << date.GetYear();
	stream << "-";
	stream << setw(2);
	stream << date.GetMonth();
	stream << "-";
	stream << setw(2);
	stream << date.GetDay();
	return stream;
}

istream& operator >> (istream& stream, Date& new_date) {
	int new_year;
	int new_month;
	int new_day;
	string str;
	stream >> str;
	runtime_error exep("Wrong date format: " + str);
	stringstream ss(str);
	set<char> allowed_symbols = {'0','1','2','3','4','5','6','7','8','9','-'};
	int num_defs_near = 0;
	for (const auto& i : str) {
		if (i == '-') {
			num_defs_near++;			//проверим дефисы подряд
		}
		else {
			num_defs_near = 0;
		}
		if (num_defs_near > 2) {
			throw exep;
		}
		if (count(allowed_symbols.begin(), allowed_symbols.end(), i) == 0) {  //проверим разрешенные символы
			throw exep;
		}
	}
	int num_defs = count(str.begin(), str.end(), '-');
	if ( num_defs < 2 || num_defs > 5) {					//проверим количество дефисов
		throw exep;
	}
	ss >> new_year;
	ss.ignore(1);
	ss >> new_month;
	ss.ignore(1);
	ss >> new_day;
	new_date = {new_year, new_month, new_day};
	return stream;
}

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return (lhs.GetYear() < rhs.GetYear());
	}
	else if (lhs.GetMonth() != rhs.GetMonth()) {
		return (lhs.GetMonth() < rhs.GetMonth());
	}
	else {
		return (lhs.GetDay() < rhs.GetDay());
	}
}

bool operator == (const Date& lhs, const Date& rhs) {
	return (lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() &&
			lhs.GetYear() == rhs.GetYear());
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
	  db[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
	  if (db.count(date) == 0) {
		  cout << "Event not found" << endl;
		  return false;
	  }
	  if (db.at(date).count(event) == 0) {
		  cout << "Event not found" << endl;
		  return false;
	  }
	  db[date].erase(event);
	  cout << "Deleted successfully" << endl;
	  return true;
  }
  int  DeleteDate(const Date& date) {
	  int num = 0;
	  if (db.count(date) == 0) {
		  return num;
	  }
	  num = db[date].size();
	  db[date].clear();
	  return num;
  }

  bool Find(const Date& date) const {
	  if (db.count(date) == 0) {
	  	 return false;
	  }
	  for (const auto& event : db.at(date)) {
		  cout << event << endl;
	  }
	  return true;
  }
  void Print() const {
	  for (const auto& day : db) {
		  for (const auto& event : day.second) {
			  cout << day.first << " " << event << endl;
		  }
	  }
  }
private:
  map<Date, set<string>> db;
};

void Add(Database& db, istream& stream) {
	Date date;
	string event;
	stream >> date >> event;
	db.AddEvent(date, event);
}
void Del(Database& db, istream& stream) {
	Date date;
	string event;
	stream >> date >> event;
	if (event.size() == 0) {
		cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
	}
	else {
		db.DeleteEvent(date, event);
	}
}
void Find(Database& db, istream& stream) {
	Date date;
	stream >> date;
	db.Find(date);
}

int main() {
  Database db;
  string command;
  while (getline(cin, command)) {
	  stringstream ss(command);
	  string key_word;
	  ss >> key_word;

	  try {

		  if (key_word == "Add"){
			  Add(db, ss);

		  }
		  else if (key_word == "Del"){
			  Del(db, ss);
		  }
		  else if (key_word == "Find"){
			  Find(db, ss);
		  }
		  else if (key_word == "Print"){
			  db.Print();
		  }
		  else if (key_word.size() == 0) {

		  }
		  else {
			  cout << "Unknown command: " << key_word << endl;
		  }

	  }
	  catch (runtime_error& err) {
		  cout << err.what() << endl;
		  return 0;
	  }
 }

  return 0;
}
