#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class SortedStrings {
public:
	void AddString(const string& s) {
		strings.push_back(s);
		sort(begin(strings), end(strings));
	}
	vector<string> GetSortedStrings() {
		return strings;
	}
private:
	vector<string> strings;
};

/*void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;

  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);

  strings.AddString("second");
  PrintSortedStrings(strings);

  return 0;
}*/



