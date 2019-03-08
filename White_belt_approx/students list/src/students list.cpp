/*
 *
 * 3 Ivan Ivanov 1 1 1901 Petr Petrox 2 2 1902 Alexander Sidorov 3 3 1903 3 mark 5 name 1 date 3
 *
 */

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Student {
	string first_name;
	string last_name;
	int day_birth;
	int month_birth;
	int year_birth;
};

istream& operator >> (istream& stream, Student& new_student) {
	stream >> new_student.first_name >> new_student.last_name >> new_student.day_birth >>
								 new_student.month_birth >> new_student.year_birth;
	return stream;
}

ostream& operator << (ostream& stream, const Student& student) {
	stream << student.first_name << " " << student.last_name << " " <<  student.day_birth << " " <<
								 student.month_birth << " " <<  student.year_birth;
	return stream;
}

void PrintVector(const vector<Student>& v) {
	for (const auto& i : v) {
		cout << i << endl;
	}
}

void ReadStudents(vector<Student>& student_list) {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		Student new_student;
		cin >> new_student;
		student_list.push_back(new_student);
	}
}

void DoRequests(const vector<Student>& student_list) {
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		string command;
		int k;
		cin >> command >> k;
		if (1 <= k && k <= student_list.size()) {
			if (command == "name") {
			cout << student_list[k - 1].first_name << " " << student_list[k - 1].last_name << endl;
			}
			else if (command == "date") {
				cout <<  student_list[k - 1].day_birth << "." << student_list[k - 1].month_birth
					<< "." <<  student_list[k - 1].year_birth << endl;
			}
			else {
				//cout << "<" << command << ">" << endl;
				cout << "bad request" << endl;
			}
		}
		else {
			cout << "bad request" << endl;
		}
	}
}

int main() {
	vector<Student> student_list;
	ReadStudents(student_list);
	//PrintVector(student_list);
	DoRequests(student_list);

	return 0;
}
