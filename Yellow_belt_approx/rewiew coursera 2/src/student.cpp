#include <iostream>

#include "student.h"

using namespace std;

Student::Student(const string& name, const string& favouriteSong)
    : Person(name, "Student")
    , _favouriteSong(favouriteSong) {}

void Student::learn() const {
    talk("learns");
}

void Student::walk(const string& destination) const {
    Person::walk(destination);
    singSong();
}

void Student::singSong() const {
    talk("sings a song: " + _favouriteSong);
}
