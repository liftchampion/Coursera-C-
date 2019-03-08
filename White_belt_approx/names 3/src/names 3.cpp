#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Person {
public:
	Person (const string& initial_firstname, const string& initial_lastname, int new_birth_year) {
		birth_year = new_birth_year;
		last_names[birth_year] = initial_lastname;
		first_names[birth_year] = initial_firstname;
	}
	void ChangeFirstName(int year, const string& new_first_name) {
		if (year >= birth_year) {
			first_names[year] = new_first_name;
		}
	}
	void ChangeLastName(int year, const string& new_last_name) {
		if (year >= birth_year) {
			last_names[year] = new_last_name;
		}
	}
	string GetFullName (int year) const {
		string actual_firstname = FindName(year, first_names);
		string actual_lastname = FindName(year, last_names);

		if (year < birth_year) {
			return "No person";
		}
		if (actual_firstname.size() == 0 && actual_lastname.size() == 0) {
			return "Incognito";
		}
		if (actual_firstname.size() == 0) {
			return actual_lastname + " with unknown first name";
		}
		if (actual_lastname.size() == 0) {
			return actual_firstname + " with unknown last name";
		}
		else {
			return actual_firstname + " " + actual_lastname;
		}

	}
	string GetFullNameWithHistory (int year) const {
		string actual_firstname = GetFormattedNamesHistory(year, first_names);
		string actual_lastname = GetFormattedNamesHistory(year, last_names);

		if (year < birth_year) {
			return "No person";
		}
		if (actual_firstname.size() == 0 && actual_lastname.size() == 0) {
			return "Incognito";
		}
		if (actual_firstname.size() == 0) {
			return actual_lastname + " with unknown first name";
		}
		if (actual_lastname.size() == 0) {
			return actual_firstname + " with unknown last name";
		}
		else {
			return actual_firstname + " " + actual_lastname;
		}

	}
private:
	int birth_year;
	map<int, string> last_names;
	map<int, string> first_names;

	string FindName(int year, const map<int, string>& list) const{
		string actual_name;
		for (const auto& item : list) {
			if (item.first > year) {
				break;
			}
			if (item.second.size() != 0) {
				actual_name = item.second;
			}
		}
		return actual_name;
	}
	string GetFormattedNamesHistory(int year, const map<int, string>& list) const{
		vector<string> history;
		string formatted_history;
		for (const auto& item : list) {
			if (item.first > year) {
				break;
			}
			if (item.second.size() != 0) {
				history.push_back(item.second);
			}
		}

		while (true) {
			bool done = true;
			for (int i = 1; i < history.size(); i++) {  // ???
				string temp;
				temp = history[i-1];
				if (temp == history[i]) {
					history.erase(history.begin() + i);
					done = false;
				}
			}
			if (done) {
				break;
			}
		}

		for (int i = 0; i < history.size() / 2; i++) {
			string temp;
			temp = history[i];
			history[i] = history[history.size() - 1 - i];
			history[history.size() - 1 - i] = temp;
		}

		bool is_first = true;
		bool is_second = true;
		if (history.size() == 0) {
			return formatted_history;
		}
		if (history.size() == 1) {
			formatted_history += history[0];
			return formatted_history;
		}
		for (const auto& item : history) {
			if (is_first) {
				formatted_history += item;
				is_first = false;
			}
			else if (is_second) {
				formatted_history += " (";
				formatted_history += item;
				is_second = false;
			}
			else {
				formatted_history += ", ";
				formatted_history += item;
			}
		}
		if (is_second == false) {
			formatted_history += ")";
		}
		return formatted_history;
	}
};

/*int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}*/
