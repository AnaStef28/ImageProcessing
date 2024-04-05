#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle() {
	this->point = Point(0, 0);
	this->size = Size(0, 0);
}

Rectangle::Rectangle(Point p, Size s) {
	this->point = p;
	this->size = s;
}

Point Rectangle::get_point(){
	return this->point;
}

Size Rectangle::get_size() {
	return this->size;
}

void Rectangle::set_point(int x, int y) {
	this->point.set_x(x);
	this->point.set_y(y);
}

void Rectangle::set_size(unsigned int width, unsigned int height) {
	this->size.set_height(height);
	this->size.set_width(width);
}

void Rectangle::operator+(Point& obj){
	this->point.set_x(obj.get_x()+this->point.get_x());
	this->point.set_y(obj.get_y() + this->point.get_y());
}

void Rectangle::operator-(Point& obj) {
	this->point.set_x(this->point.get_x()-obj.get_x());
	this->point.set_y(this->point.get_y() - obj.get_y());
}

Rectangle Rectangle::operator&(Rectangle& other) {
	Point p1 = this->point;
	Size s1 = this->size;
	Point p2 = other.point;
	Size s2 = other.size;

	int x1 = std::max(p1.get_x(), p2.get_x());
	int y1 = std::max(p1.get_y(), p2.get_y());
	int x2 = std::min(p1.get_x() + s1.get_width(), p2.get_x() + s2.get_width());
	int y2 = std::min(p1.get_y() + s1.get_height(), p2.get_y() + s2.get_height());
	int newWidth = std::max(0, x2 - x1);
	int newHeight = std::max(0, y2 - y1);
	Point res1(x1, y1);
	Size res2(newWidth, newHeight);
	return Rectangle(res1, res2);
}

Rectangle Rectangle::operator|(Rectangle& other) {
	Point p1 = this->point;
	Size s1 = this->size;
	Point p2 = other.point;
	Size s2 = other.size;

	int x1 = std::min(p1.get_x(), p2.get_x());
	int y1 = std::min(p1.get_y(), p2.get_y());
	int x2 = std::max(p1.get_x() + s1.get_width(), p2.get_x() + s2.get_width());
	int y2 = std::max(p1.get_y() + s1.get_height(), p2.get_y() + s2.get_height());
	int newWidth = x2 - x1;
	int newHeight = y2 - y1;
	Point res1(x1, y1);
	Size res2(newWidth, newHeight);
	return Rectangle(res1, res2);
}
