#pragma once
#include "Point.h"
#include "SIze.h"

class Rectangle: public Point, public Size {

private:
	Point point;
	Size size;
public:
	Rectangle();
	Rectangle(Point point, Size size);
	Point get_point();
	Size get_size();
	void set_point(int x, int y);
	void set_size(unsigned int width, unsigned int height);
	void operator+(Point& obj);
	void operator-(Point& obj);
	Rectangle operator&(Rectangle& obj);
	Rectangle operator|(Rectangle& obj);
};