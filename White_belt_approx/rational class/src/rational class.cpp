#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <exception>
using namespace std;

class Rational {
public:
	Rational () { p = 0; q = 1; }
	Rational (int new_p, int new_q) {
		if (new_q == 0) {
			throw invalid_argument("denominator couldnt be zero");
		}
		else {
			if (new_p == 0) {
				p = new_p;
				q = 1;
			}
			else {
				p = abs( new_p / NODFind(new_p, new_q) );
				q = abs( new_q / NODFind(new_p, new_q) );
				if ( (new_p < 0 && new_q > 0) || (new_p > 0 && new_q < 0)) {
					p *= -1;
				}
			}
		}
	}

	int Numerator() const {
		return p;
	}
	int Denominator() const {
		return q;
	}


private:
	int NODFind (int p, int q) const {
		int t;
		while (q != 0) {
			t = q;
			q = p % q;
			p = t;
		}
		return p;
	}

	int p;
	int q;
};

Rational operator + (const Rational& lhs, const Rational& rhs) {
	int numerator;
	int denominator;
	numerator = lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator();
	denominator = lhs.Denominator() * rhs.Denominator();
	return {numerator, denominator};
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	int numerator;
	int denominator;
	numerator = lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator();
	denominator = lhs.Denominator() * rhs.Denominator();
	return {numerator, denominator};
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	int numerator = lhs.Numerator() * rhs.Numerator();
	int denominator = lhs.Denominator() * rhs.Denominator();
	return {numerator, denominator};
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("division by zero");
	}
	else {
		int numerator = lhs.Numerator() * rhs.Denominator();
		int denominator = lhs.Denominator() * rhs.Numerator();
		return {numerator, denominator};
	}

}

bool operator == (const Rational& lhs, const Rational& rhs) {
	int num1 = lhs.Numerator() * rhs.Denominator();
	int num2 = rhs.Numerator() * lhs.Denominator();
	return (num1 == num2);
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	int num1 = lhs.Numerator() * rhs.Denominator();
	int num2 = rhs.Numerator() * lhs.Denominator();
	return (num1 < num2);
}

istream& operator >> (istream& stream, Rational& item) {
	int num;
	int den;
	bool is_full1 = false;
	bool is_full2 = false;
	if (stream) {
		if (stream >> num) {
			is_full1 = true;
		}
		stream.ignore(1);
		if (stream >> den) {
			is_full2 = true;
		}
		if (is_full1 && is_full2) {
			item = {num, den};
		}

	}

	return stream;
}

ostream& operator << (ostream& stream, const Rational& item) {
	stream << item.Numerator() << "/" << item.Denominator();
	return stream;
}




/*int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}*/
