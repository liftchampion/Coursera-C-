#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Объявление общего класса для человека */
class Person
{
public:
    Person(const string& name, const string& type);

    //виртуальный метод Прогуляться
    virtual void Walk(const string& destination) const;
    
    void Appeal() const;
    
    const string Name_; //имя 
    const string type_; //тип личности
};

/* Наслденик класса Человека - Студент */
class Student : public Person
{
public:
    //студент отдельно инициализируется с песней
    Student(const string& name, const string& favouriteSong);

    //метод Изучить - характерен только для студента
    void Learn() const;

    //общий метод прогуляться. Для студента помимо общего функционала характеризуется распеваемой им песней
    void Walk(const string& destination) const override;

    //Метод студентов - петь песню
    void SingSong() const;

    const string FavouriteSong; //песня, которую поёт студент
};

/* Класс Учитель - наследник класса Человек*/
class Teacher : public Person
{
public:
    //конструктор с дополнительным указанием преподаваемого предмета
    Teacher(const string& name, const string& subject);

    //Метод учителей - научить предмету
    void Teach() const;

    const string Subject_; //преподаваемый предмет
};

/* Класс Полицейский - наследник класса Человек */
class Policeman : public Person
{
public:
    //инициализируется только именем
    Policeman(const string& name);

    //метод Полицейского - проверить
    void Check(const Person& p) const;

};