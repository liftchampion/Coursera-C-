#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name, const std::string& type);

    std::string             getName() const;
    std::string             getType() const;
    void                    talk(const std::string& message) const;
    virtual void            walk(const std::string& destination) const;

protected:
    const std::string       _name;
    const std::string       _type;
};
