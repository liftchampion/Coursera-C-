#pragma once

#include "person.h"

class Teacher : public Person {
public:
    Teacher(const std::string& name, const std::string& subject);
    
    void                    teach() const;

private:
    const std::string       _subject;
};
