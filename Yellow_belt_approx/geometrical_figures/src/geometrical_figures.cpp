#include <memory>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
	virtual ~Figure() {}
};

class Triangle : public Figure {
public:
	Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}
	string Name() const override {
		return name_;
	}
	double Perimeter() const override {
		return a_ + b_ + c_;
	}
	double Area() const override {
		double p = Perimeter() / 2;
		return sqrt(p * (p - a_) * (p - b_) * (p - c_));
	}

private:
	string name_ = "TRIANGLE";
	int a_, b_, c_;
};

class Rect : public Figure {
public:
	Rect(int w, int h) : w_(w), h_(h) {}
	string Name() const override {
		return name_;
	}
	double Perimeter() const override {
		return (w_ + h_ ) * 2;
	}
	double Area() const override {
		return w_ * h_;
	}

private:
	string name_ = "RECT";
	int w_, h_;
};

class Circle : public Figure {
public:
	Circle(int r) : r_(r) {}
	string Name() const override {
		return name_;
	}
	double Perimeter() const override {
		return 2 * 3.14 * r_;
	}
	double Area() const override {
		return 3.14 * r_ * r_;
	}

private:
	string name_ = "CIRCLE";
	int r_;
};


shared_ptr<Figure> CreateFigure (istringstream& s) {
	string type;
	s >> type;

	//shared_ptr<Figure> s_p;
	if (type == "RECT") {
		int w, h;
		s >> w >> h;
		return make_shared<Rect>(w, h);
		//return s_p;
	}
	else if (type == "TRIANGLE") {
		int a, b, c;
		s >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
		//return s_p;
	}
	else {
		int r;
		s >> r;
		return make_shared<Circle>(r);
		//return s_p;
	}
}


int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
