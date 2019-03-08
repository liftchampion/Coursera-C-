#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		history[year].firstName = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		history[year].lastName = last_name;
	}
	string GetFullName(int year) {
		string actual_name;
		string actual_lastname;
		for (const auto& item : history) {
			if (item.first > year) {
				break;
			}
			if (item.second.firstName.size() != 0) {
				actual_name = item.second.firstName;
			}
			if (item.second.lastName.size() != 0) {
				actual_lastname = item.second.lastName;
			}
			//cout << "debug name*" << actual_name << "* surname*" << actual_lastname << "*" << endl;
		}
		if (actual_name.size() == 0 && actual_lastname.size() == 0) {
			return "Incognito";
		}
		if (actual_name.size() == 0 && actual_lastname.size() != 0) {
			return actual_lastname + " with unknown first name";
		}
		if (actual_lastname.size() == 0 && actual_name.size() != 0) {
			return actual_name + " with unknown last name";
		}
		else {
			return actual_name + " " + actual_lastname;
		}
	}

	/*void Print() {
		for (const auto& item : history) {
			cout << "Year: " << item.first << " Name: " << item.second.firstName <<
					" Surname: " << item.second.lastName << endl;
		}
	}*/
private:
	struct fullName {
		string firstName;
		string lastName;
	};
	map<int, fullName> history;
};

/*int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  //person.Print();

  return 0;
}*/
