#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Role {
public:
	Role(const string& name = "name", const string& role = "role")
						: name_(name), role_(role) {}

	virtual void Walk(const string& destination) const {
		cout << role_ << ": " << name_ << " walks to: " << destination << endl;
	}

	virtual ~Role() {} //Виртуальный дестркутор, чтобы убрать warning

	const string name_;
	const string role_;
};


class Student : public Role {
public:
    Student(const string& name, const string& favouriteSong)
					: Role(name, "Student"),
					  favouriteSong_(favouriteSong) {}

    void Learn() const {
        cout << role_ << ": " << name_ << " learns" << endl;
    }

    void Walk(const string& destination) const {
    	cout << role_ << ": " << name_ << " walks to: " << destination << endl;
    	cout << role_ << ": " << name_ << " sings a song: " << favouriteSong_ << endl;
    }

    void SingSong() const {
    	cout << role_ << ": " << name_ << " sings a song: " << favouriteSong_ << endl;
    }

private:
    const string favouriteSong_;
};


class Teacher : public Role {
public:

    Teacher(const string& name, const string& subject)
				: Role(name, "Teacher"), subject_(subject) {}

    void Teach() const {
    	cout << role_ << ": " << name_ << " teaches: " << subject_ << endl;
    }

    const string subject_;
};


class Policeman : public Role {
public:
    Policeman(const string& name)
				: Role(name, "Policeman") {}

    void Check(const Role& r) const {
    	cout << role_ << ": " << name_ << " checks " << r.role_ <<
    			". " << r.role_ << "'s name is: " << r.name_ << endl;
    }
};


void VisitPlaces(const Role& r, const vector<string>& places) {
    for (const auto& p : places) {
        r.Walk(p);
    }
}


int main() {
	//Main из условия
	{
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	}

	cout << endl << endl << endl;

	//Тест всех функций класса
	{
    cout << "***Checking Student***" << endl;
    Student s("Ann", "We will rock you");
    cout << "	***Learn***" << endl;
    s.Learn();
    cout << "	***Walk***" << endl;
    s.Walk("Hell");
    cout << "	***Sing***" << endl;
    s.SingSong();
    cout << endl;

    cout << "***Checking Teacher***" << endl;
    Teacher t("Jim", "Math");
    cout << "	***Teach***" << endl;
    t.Teach();
    cout << "	***Walk***" << endl;
    t.Walk("Hell");
    cout << endl;

    cout << "***Checking Policeman***" << endl;
    Policeman p("Bob");
    cout << "	***Check***" << endl;
    p.Check(s);
    p.Check(t);
    p.Check(p);
    cout << "	***Walk***" << endl;
    p.Walk("Hell");
    cout << endl;
	}

    return 0;
}
