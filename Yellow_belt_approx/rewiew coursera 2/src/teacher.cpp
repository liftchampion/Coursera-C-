#include <iostream>

#include "teacher.h"

using namespace std;

Teacher::Teacher(const string& name, const string& subject)
    : Person(name, "Teacher")
    , _subject(subject) {}

void Teacher::teach() const {
    talk("teaches: " + _subject);
}
