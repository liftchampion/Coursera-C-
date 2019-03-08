#include "visit.h"

using namespace std;

void visitPlaces(const Person& person, const vector<string>& places) {
    for (auto place : places) {
        person.walk(place);
    }
}
