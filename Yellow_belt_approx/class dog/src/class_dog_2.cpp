#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    // ваш код
	Animal(const string& name) : Name(name) {}

	void DoABarrelRoll() {
		cout << Name << " rolled !!!" << endl;
	}

    const string Name;
};


class Dog : public Animal {
public:
    // ваш код
	Dog(const string& name) : Animal(name) {}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};


int main() {
	Dog bobby("bobby");
	Dog stephany("staphany");
	cout << bobby.Name << endl;
	cout << stephany.Name << endl;
	bobby.Bark();
	bobby.DoABarrelRoll();
	stephany.DoABarrelRoll();
}
