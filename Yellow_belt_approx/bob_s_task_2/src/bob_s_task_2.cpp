#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <memory>
using namespace std;

/*
 * insert 8
insert 3
insert 10
insert 1
insert 6
insert 14
insert 4
insert 7
insert 13
print 0

insert 5
insert 10
insert 6
insert 0
insert 1
insert 15
insert 5
print 0
 *
 *
 */

class Node {
public:
	Node() {
		value = 0;
		active = false;
		direction = '-';
	}
	void Insert(const int& new_value, char new_direction = '-') {
		if (!active) {
			value = new_value;
			active = true;
			direction = new_direction;
		}
		else {
			cerr << "children called" << endl;
			if (new_value < value) {
				children['L'].Insert(new_value, 'L');
			}
			else {
				children['R'].Insert(new_value, 'R');
			}
		}
	}
	void Delete(const int& del_value) {
		cerr << "deleting" << endl;
		if (del_value == value) {
			cerr << "	good node" << endl;
			if (!children['L'].active && !children['R'].active) {
				cerr << "	empty node" << endl;
				active = false;
			}
			if (children['L'].active && !children['R'].active) {

			}
			if (!children['L'].active && children['R'].active) {

			}
		}
		else if (del_value < value){
			children['L'].Delete(del_value);
		}
		else {
			children['R'].Delete(del_value);
		}
	}
	void Print() {
		if (active) {
			cout << value << " children are: ( L< ";
			children['L'].Print();
			cout << "> R<";
			children['R'].Print();
			cout << "> ) ";
		}
	}
private:
	bool active;
	int value;
	map<char, Node> children;
	char direction;
};

int main() {
	Node tree;
	string command;
	int value;
	while (cin >> command >> value) {
		if (command == "insert") {
			tree.Insert(value);
		}
		if (command == "delete") {
			tree.Delete(value);
		}
		if (command == "exists") {

		}
		if (command == "next") {

		}
		if (command == "prev") {

		}
		if (command == "print") {
			tree.Print();
		}
		else {

		}
	}
	return 0;
}
