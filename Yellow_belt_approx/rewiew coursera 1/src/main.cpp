#include <iostream>
#include "persons.h"
#include <vector>

using namespace std;

//Функция посетить места - универсальна для любого человека
void VisitPlaces(const Person& person, vector<string> places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

int main() {
    
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
