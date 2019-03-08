#pragma once
#include <iostream>

// Write includes

using namespace std;

//Declare your functions here

class Rectangle {
public:
	Rectangle(int width, int height);
	int GetArea() const;
	int GetPerimeter() const;
	int GetWidth() const;
	int GetHeight() const;
private:
	int width_;
	int height_;
};
