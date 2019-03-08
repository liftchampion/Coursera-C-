#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
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

	string GetFullNameWithHistory(int year) {
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
				return actual_lastname + GetLastNameHistory(year) + " with unknown first name";
			}
			if (actual_lastname.size() == 0 && actual_name.size() != 0) {
				return actual_name + GetNameHistory(year) +" with unknown last name";
			}
			else {
				return actual_name + GetNameHistory(year) + " " + actual_lastname + GetLastNameHistory(year);
			}
	}

	string GetNameHistory (int year) {
		string name_history;
		string actual_name;
		string moment_name_history;
		set<string> used_names;
		bool is_first = true;

		for (const auto& item : history) {
			if (item.first > year) {
				break;
			}
			if (item.second.firstName.size() != 0) {
				actual_name = item.second.firstName;
			}
		}
		used_names.insert(actual_name);

		for (const auto& item : history) {
			if (item.first > year) {
				break;
			}
			if (item.second.firstName.size() != 0) {
				actual_name = item.second.firstName;
				if (used_names.count(actual_name) == 0) {
					if (is_first) {
					moment_name_history = actual_name + name_history;
					is_first = false;
					}
					else {
						moment_name_history = actual_name + " " + name_history;
					}
					name_history = moment_name_history;
					used_names.insert(actual_name);
				}

			}
		}
		moment_name_history = name_history;
		name_history = " (" + moment_name_history + ") ";
		return name_history;
	}
	string GetLastNameHistory (int year) {
		string lastname_history;
		string actual_lastname;
		string moment_lastname_history;
		for (const auto& item : history) {
			if (item.first > year) {
				break;
			}
			if (item.second.lastName.size() != 0) {
				actual_lastname = item.second.lastName;
				moment_lastname_history = actual_lastname + " " + lastname_history;
				lastname_history = moment_lastname_history;
			}
		}
		moment_lastname_history = lastname_history;
		lastname_history = " (" + moment_lastname_history + ")";
		return lastname_history;
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

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;

  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;

  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;

  return 0;
}
