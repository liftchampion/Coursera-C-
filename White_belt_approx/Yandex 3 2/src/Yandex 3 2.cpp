/*
 * 4 APPOINT 365 9:00 120 3 gleb sergey bob APPOINT 2 11:00 15 3 gleb sergey bob PRINT 365 sergey PRINT 2 sergey
 * 3 APPOINT 1 12:30 30 2 andrey alex APPOINT 1 12:00 30 2 jhonny stephen APPOINT 1 12:00 60 3 jhonny alex stephen
 *
 *
 *
 *
 */


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Time {
	Time () {
		hours = 0;
		minutes =0;
	}
	Time (int new_hours, int new_minutes) {
		hours = (new_hours * 60 + new_minutes) / 60;
		minutes = (new_hours * 60 + new_minutes) % 60;
	}
	int hours;
	int minutes;
};
bool operator < (const Time& lhs, const Time& rhs) {
	return ( (lhs.hours * 60 + lhs.minutes) < (rhs.hours * 60 + rhs.minutes) );
}
bool operator > (const Time& lhs, const Time& rhs) {
	return ( (lhs.hours * 60 + lhs.minutes) > (rhs.hours * 60 + rhs.minutes) );
}
bool operator == (const Time& lhs, const Time& rhs) {
	return ( (lhs.hours * 60 + lhs.minutes) == (rhs.hours * 60 + rhs.minutes) );
}
Time operator + (const Time& lhs, int rhs) {
	return {lhs.hours, lhs.minutes + rhs};
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
	stream << time.minutes;
	return stream;
}


struct Meeting {
	Time begin;
	int duration;
	vector<string> partipicians;
};
bool operator < (const Meeting& lhs, const Meeting& rhs) {
	return lhs.begin < rhs.begin;
}
bool operator == (const Meeting& lhs, const Meeting& rhs) {
	return (lhs.begin == rhs.begin) && (lhs.duration == rhs.duration)
			&& (lhs.partipicians == rhs.partipicians);
}

void PrintVector(const vector<string>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
}

bool CheckMeet (const Meeting& meet, const Time& checking_time, int new_duration) {
	//cout << "begin at " << meet.begin << " end at " << meet.begin + meet.duration
	//		<< " checking time is from " << checking_time << " to " << checking_time + new_duration << endl;
	if (checking_time > meet.begin && checking_time < meet.begin + meet.duration) {
		//cout << "bad checking begin" << endl;
		return false;
	}
	else if (checking_time + new_duration > meet.begin && checking_time + new_duration < meet.begin + meet.duration) {
		//cout << "bad checking end" << endl;
		return false;
	}
	else if ( meet.begin > checking_time && meet.begin < checking_time + new_duration) {
			return false;
		}
	else if ( meet.begin + meet.duration > checking_time && meet.begin + meet.duration < checking_time + new_duration) {
			return false;
		}
	else if (meet.begin == checking_time && meet.begin + meet.duration == checking_time + new_duration) {
		return false;
	}
	else {
		//cout << "is alright" << endl;
		return true;
	}
}

bool CheckPerson (const set<Meeting>& his_meets, const Time& checking_time, int duration) {
	bool can = true;
	for (const auto& meet : his_meets) {
		//cout << "Checking meet at " << meet.begin << endl;
		can = CheckMeet(meet, checking_time, duration);
		if (can == false) {
			return false;
		}
	}
	return true;
}

vector<string> CheckAll (const map<string, set<Meeting>>& meets_for_day, const Time& checking_time, int duration,
							const vector<string>& who_want) {
	vector<string> who_cant;
	//cout << "<ww ";
	//PrintVector(who_want);
	//cout << " >" << endl;
	for (const auto& man : who_want) {
		if (meets_for_day.count(man) == 1) {
			//cout << "Checking " << man << endl;
			if (CheckPerson(meets_for_day.at(man), checking_time, duration) == false) {
				who_cant.push_back(man);
				//cout << "added wc" << endl;
			}
		}
	}
	return who_cant;
}

bool Appoint (map<int, map<string, set<Meeting>>>& db) {
	int day;
	Time time;
	int duration;
	int k;
	cin >> day >> time >> duration >> k;
	vector<string> who_want(k);
	for (auto& i : who_want) {
		cin >> i;
	}
	vector<string> who_cant;
	who_cant = CheckAll(db[day], time, duration, who_want);
	//cout << "<wc ";
	//PrintVector(who_cant);
	//cout << " >" << endl;
	if (who_cant.size() > 0) {
		cout << "FAIL" << endl;
		PrintVector(who_cant);
		cout << endl;
		return false;
	}
	for (const auto& new_person : who_want) {
		//cout << "inserting" << endl;
		db[day][new_person].insert({time, duration, who_want});
	}
	cout << "OK" << endl;
	return true;
}

bool Print(const map<int, map<string, set<Meeting>>>& db) {
	int day;
	string person;
	cin >> day >> person;
	if (db.count(day) == 0) {
		return false;
	}
	if (db.at(day).count(person) == 0) {
		return false;
	}
	for (const auto& meet : db.at(day).at(person)) {
		cout << meet.begin << " " << meet.duration << " ";
		PrintVector(meet.partipicians);
		cout << endl;
	}

	return true;
}



int main() {
	map<int, map<string, set<Meeting>>> db;
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;
		if (command == "APPOINT") {
			Appoint(db);
		}
		if (command == "PRINT") {
			Print(db);
		}
	}
	return 0;
}
