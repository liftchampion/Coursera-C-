#include <string>
#include <vector>
#include <iostream>

#include "visit.h"
#include "student.h"
#include "teacher.h"
#include "policeman.h"

using namespace std;

int main() {
    Teacher teacher("Jim", "Math");
    Student student("Ann", "We will rock you");
    Policeman poiceman("Bob");

    visitPlaces(teacher, { "Moscow", "London" });
    visitPlaces(student, { "Moscow", "London" });
    poiceman.check(teacher);
    poiceman.check(student);

    return 0;
}
