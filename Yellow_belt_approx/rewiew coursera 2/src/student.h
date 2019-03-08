#pragma once

#include "person.h"

class Student : public Person {
public:
    Student(const std::string& name, const std::string& favouriteSong);

    void                    learn() const;
    void                    walk(const std::string& destination) const override;
    void                    singSong() const;

private:
    const std::string       _favouriteSong;
};
