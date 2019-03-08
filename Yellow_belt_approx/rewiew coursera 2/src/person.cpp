#include <iostream>

#include "Person.h"

using namespace std;

Person::Person(const string& name, const string& type = "Person")
    : _name(name)
    , _type(type) {}

string Person::getName() const {
    return _name;
}

string Person::getType() const {
    return _type;
}

void Person::talk(const string& message) const {
    cout << _type << ": " << _name << " " << message << endl;
}

void Person::walk(const std::string& destination) const {
    talk("walks to: " + destination);
}
