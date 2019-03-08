#pragma once

#include "person.h"

class Policeman : public Person {
public:
    Policeman(const std::string& name);

    void                    check(const Person& person) const;
};
