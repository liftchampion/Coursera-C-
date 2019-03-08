/*
 * 7 APPOINT 1 12:30 30 2 andrey alex APPOINT 1 12:00 30 2 alex sergey APPOINT 1 12:59 60 2 alex andrey PRINT 1 alex PRINT 1 andrey PRINT 1 sergey PRINT 2 alex
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

struct Time {
	Time () {
		hours = 0;
		minutes = 0;
	}
	Time (int new_hours, int new_minutes) {
		hours = (new_hours * 60 + new_minutes) / 60;
		minutes = (new_hours * 60 + new_minutes) % 60;
	}
	int hours;
	int minutes;
};


bool operator >= (const Time& lhs, const Time& rhs) {
	if (lhs.hours != rhs.hours) {
		return (lhs.hours >= rhs.hours);
	}
	return (lhs.minutes >= rhs.minutes);
}
bool operator <= (const Time& lhs, const Time& rhs) {
	if (lhs.hours != rhs.hours) {
		return (lhs.hours <= rhs.hours);
	}
	return (lhs.minutes <= rhs.minutes);
}
bool operator < (const Time& lhs, const Time& rhs) {
	if (lhs.hours != rhs.hours) {
		return (lhs.hours < rhs.hours);
	}
	return (lhs.minutes < rhs.minutes);
}
bool operator > (const Time& lhs, const Time& rhs) {
	if (lhs.hours != rhs.hours) {
		return (lhs.hours > rhs.hours);
	}
	return (lhs.minutes > rhs.minutes);
}
bool operator == (const Time& lhs, const Time& rhs) {
	return (lhs.hours == rhs.hours && lhs.minutes == rhs.minutes);
}
istream& operator >> (istream& stream, Time& new_time) {
	int new_hours;
	int new_minutes;
	stream >> new_hours;
	stream.ignore(1);
	stream >> new_minutes;
	new_time = {new_hours, new_minutes};
	return stream;
}
ostream& operator << (ostream& stream, const Time& time) {
	stream << setw(2);
	stream << setfill('0');
	stream << time.hours;
	stream << ":";
	stream << setw(2);
	stream << setfill('0');
	stream << time.minutes;

	return stream;
}
bool operator - (const Time& lhs, const Time& rhs) {
	return (lhs.hours * 60 + lhs.minutes) - (rhs.hours * 60 + rhs.minutes);
}

class TimeInterval {
public:
	TimeInterval (const Time& new_begin, int duration) {
		begin = new_begin;
		end = Time(new_begin.hours, new_begin.minutes + duration);
	}
	bool CheckIn (const Time& time) const {
		if (time > begin && time < end) {
			return true;
		}
		else {
			return false;
		}
	}

	Time Begin() const {
		return begin;
	}
	Time End() const {
		return end;
	}
private:
	Time begin;
	Time end;
};

bool operator < (const TimeInterval& lhs, const TimeInterval& rhs) {
	return (lhs.Begin() < rhs.Begin());
}
bool operator == (const TimeInterval& lhs, const TimeInterval& rhs) {
	return (lhs.Begin() == rhs.Begin() && lhs.End() == rhs.End());
}
ostream& operator << (ostream& stream, const TimeInterval& ti) {
	stream << ti.Begin() << " " << ti.End().hours*60 + ti.End().minutes
									- (ti.Begin().hours*60 + ti.Begin().minutes );
	return stream;
}

struct Meet {
	TimeInterval ti;
	vector<string> names;
};

class Day {
public:
	bool Add (const string& name, const Time& new_begin, const int& new_duration) {
		TimeInterval new_ti = {new_begin, new_duration};
		for (const auto& ti : people[name]) {
			if (ti.CheckIn(new_ti.Begin()) || ti.CheckIn(new_ti.End())) {
				return false;
			}
		}
		people[name].insert(new_ti);
		return true;
	}
	set<TimeInterval> GetPersonalShedule (const string& name) {
		return people[name];
	}
	vector<Meet> meetings;
private:
	map<string, set<TimeInterval>> people;

};



void Appoint (map<int, Day>& shedule) {
	int day;
	Time begin;
	int duration;
	int n;
	vector<string> bad_names;
	vector<string> all_names;
	cin >> day >> begin >> duration >> n;
	Day backup = shedule[day];
	for (int i = 0; i < n; ++i) {
		string name;
		cin >> name;
		all_names.push_back(name);
		if ( shedule[day].Add(name, begin, duration) ) {

		}
		else {
			bad_names.push_back(name);
		}
	}
	if (bad_names.size() == 0) {
		cout << "OK" << endl;
		shedule[day].meetings.push_back({{begin, duration}, all_names});
	}
	else {
		shedule[day] = backup;
		cout << "FAIL" << endl;
		for (const auto& i : bad_names) {
			cout << i << " ";
		}
		cout << endl;
	}
}

void PrintMeeters(const Day& day, const string& name, const TimeInterval& ti) {
	vector<string> meeters;
	bool exist = false;
	for (const auto& i : day.meetings) {
		if (i.ti == ti) {
			for (const auto& j : i.names) {
				meeters.push_back(j);
				if (j == name) {
					exist = true;
				}
			}
			if (exist) {
				break;
			}
			else {
				meeters.clear();
			}
		}
	}
	for (const auto& i : meeters) {
		//if (i != name) {
			cout << " " << i;
		//}
	}
	cout << endl;
}


void Print(map<int, Day>& shedule) {
	int day;
	string name;
	cin >> day >> name;
	for (const auto& i : shedule[day].GetPersonalShedule(name)) {
		cout << i;
		PrintMeeters(shedule[day], name, i);
	}


}

int main() {
	int q;
	cin >> q;
	map<int, Day> shedule;
	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "APPOINT") {
			Appoint(shedule);
		}
		if (command == "PRINT") {
			Print(shedule);
		}
	}
	return 0;
}
