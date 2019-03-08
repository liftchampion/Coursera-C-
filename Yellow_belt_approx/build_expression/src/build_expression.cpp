#include <string>
#include <iostream>
#include <deque>
using namespace std;

void PrintDeque(const deque<char>& d) {
	for (const auto i : d) {
		cout << i;
	}
}

void DequePushBackInt(deque<char>& d, int n) {
	string num = to_string(n);
	for (size_t i = 0; i < num.size(); i++) {
		d.push_back(num[i]);
	}
}


void UpgradeExpresion(deque<char>& expression, char operation, int arg) {
	expression.push_front('(');
	expression.push_back(')');
	expression.push_back(' ');
	expression.push_back(operation);
	expression.push_back(' ');
	DequePushBackInt(expression, arg);
}

void UpgradeExpresion(deque<char>& expression, char operation, char last_operation, int arg) {
	if ( (last_operation == '+' || last_operation == '-') &&
			  (operation == '*' || operation == '/') ) {
		expression.push_front('(');
		expression.push_back(')');
	}
	expression.push_back(' ');
	expression.push_back(operation);
	expression.push_back(' ');
	DequePushBackInt(expression, arg);
}

/*
void UpgradeExpresion(string& expression, const string& operation,
						const string& last_operation, int arg) {
	if ( (last_operation == "+" || last_operation == "-") &&
			  (operation == "*" || operation == "/") ) {
		expression.insert(0, 1, '(');
		expression.insert(expression.size(), 1, ')');
	}

	expression += " " + operation + " " + to_string(arg);

	//cout << expression << endl;
}*/


int main() {
	int initial;
	cin >> initial;
	int n;
	cin >> n;
	deque<char> expression;
	DequePushBackInt(expression, initial);

	/*for (int i = 0; i < n; i++) {
		char operation;
		cin >> operation;
		int arg;
		cin >> arg;
		UpgradeExpresion(expression, operation, arg);
	}*/

	char last_operation;
	for (int i = 0; i < n; i++) {
			char operation;
			cin >> operation;
			int arg;
			cin >> arg;
			UpgradeExpresion(expression, operation, last_operation, arg);
			last_operation = operation;
	}

	PrintDeque(expression);
	return 0;
}
