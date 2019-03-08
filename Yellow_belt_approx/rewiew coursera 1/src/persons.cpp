#include "persons.h"

/*
 * CLASS PERSON
 */
Person::Person(const string& name, const string& type)
    : Name_(name)
    , type_(type)
{
}

void Person::Appeal() const {
    cout << type_ << ": " << Name_;
}

void Person::Walk(const string& destination) const {
    Appeal();
    cout << " walks to: " << destination << endl;
}

/*
 * CLASS STUDENT
 *
 * РќР°СЃР»РґРµРЅРёРє РєР»Р°СЃСЃР° Р§РµР»РѕРІРµРєР° - РЎС‚СѓРґРµРЅС‚ */
Student::Student(const string& name, const string& favouriteSong)
    : Person(name, "Student")
    , FavouriteSong(favouriteSong)
{
}

//РјРµС‚РѕРґ Р�Р·СѓС‡РёС‚СЊ - С…Р°СЂР°РєС‚РµСЂРµРЅ С‚РѕР»СЊРєРѕ РґР»СЏ СЃС‚СѓРґРµРЅС‚Р°
void Student::Learn() const
{
    Appeal();
    cout << " learns" << endl;
}

//РѕР±С‰РёР№ РјРµС‚РѕРґ РїСЂРѕРіСѓР»СЏС‚СЊСЃСЏ. Р”Р»СЏ СЃС‚СѓРґРµРЅС‚Р° РїРѕРјРёРјРѕ РѕР±С‰РµРіРѕ С„СѓРЅРєС†РёРѕРЅР°Р»Р° С…Р°СЂР°РєС‚РµСЂРёР·СѓРµС‚СЃСЏ СЂР°СЃРїРµРІР°РµРјРѕР№ РёРј РїРµСЃРЅРµР№
void Student::Walk(const string& destination) const
{   
    Person::Walk(destination);
    SingSong();
}

//РњРµС‚РѕРґ СЃС‚СѓРґРµРЅС‚РѕРІ - РїРµС‚СЊ РїРµСЃРЅСЋ
void Student::SingSong() const
{
    Appeal();
    cout << " sings a song: " << FavouriteSong << endl;
}
/*
 * CLASS TEACHER
 *
 * РљР»Р°СЃСЃ РЈС‡РёС‚РµР»СЊ - РЅР°СЃР»РµРґРЅРёРє РєР»Р°СЃСЃР° Р§РµР»РѕРІРµРє*/
Teacher::Teacher(const string& name, const string& subject)
    : Person(name, "Teacher")
    , Subject_(subject)
{    
}

//РњРµС‚РѕРґ СѓС‡РёС‚РµР»РµР№ - РЅР°СѓС‡РёС‚СЊ РїСЂРµРґРјРµС‚Сѓ
void Teacher::Teach() const
{
    Appeal();
    cout << " teaches: " << Subject_ << endl;
}

/*
 * CLASS POLICEMAN
 *
 * РљР»Р°СЃСЃ РџРѕР»РёС†РµР№СЃРєРёР№ - РЅР°СЃР»РµРґРЅРёРє РєР»Р°СЃСЃР° Р§РµР»РѕРІРµРє */
Policeman::Policeman(const string& name)
    : Person(name, "Policeman")
{
}
//РјРµС‚РѕРґ РџРѕР»РёС†РµР№СЃРєРѕРіРѕ - РїСЂРѕРІРµСЂРёС‚СЊ
void Policeman::Check(const Person& p) const
{
    Appeal();
    cout << " checks  " << p.type_ << ". " << p.type_ << "'s name is: " << p.Name_ << endl;
}

