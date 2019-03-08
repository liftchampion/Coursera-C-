#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& new_first_name) {
		first_names[year] = new_first_name;
	}
	void ChangeLastName(int year, const string& new_last_name) {
		last_names[year] = new_last_name;
	}
	string GetFullName (int year) {
		string actual_firstname = FindName(year, first_names);
		string actual_lastname = FindName(year, last_names);

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
	string GetFullNameWithHistory (int year) {
		string actual_firstname = GetFormattedNamesHistory(year, first_names);
		string actual_lastname = GetFormattedNamesHistory(year, last_names);

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
	map<int, string> last_names;
	map<int, string> first_names;

	string FindName(int year, const map<int, string>& list) {
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
	string GetFormattedNamesHistory(int year, const map<int, string>& list) {
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
  Person person;

  person.ChangeFirstName(1900, "Eugene");
  person.ChangeLastName(1900, "Sokolov");
  person.ChangeLastName(1910, "Sokolov");
  person.ChangeFirstName(1920, "Evgeny");
  person.ChangeLastName(1930, "Sokolov");
  cout << person.GetFullNameWithHistory(1940) << endl;

  return 0;
}*/

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
