#include <string>
#include <iostream>
using namespace std;

struct Specialization {
	string specialization;
	explicit Specialization(const string& obj) {
		specialization = obj;
	}
};
struct Course {
	string course;
	explicit Course(const string& obj) {
		course = obj;
	}
};
struct Week {
	string week;
	explicit Week (const string& obj) {
		week = obj;
	}
};
struct LectureTitle {
	string specialization;
	string course;
	string week;
	LectureTitle (const Specialization& new_spec,
			const Course& new_course, const Week& new_week) {
		specialization = new_spec.specialization;
		course = new_course.course;
		week = new_week.week;
	}
};

