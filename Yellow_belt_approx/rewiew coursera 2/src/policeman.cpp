#include <iostream>

#include "policeman.h"

using namespace std;

Policeman::Policeman(const std::string& name)
    : Person(name, "Policeman") {}

void Policeman::check(const Person& person) const {
    string personType = person.getType();
    string message = "checks " + personType + ". "
        + personType + "'s name is: " + person.getName();
    
    talk(message);
}
