#include <iostream>
#include "Point.h"

Point::Point() {
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

int Point::get_x() {
	return this->x;
}

int Point::get_y() {
	return this->y;
}

void Point::set_x(int x) {
	this->x=x;
}

void Point::set_y(int y) {
	this->y = y;
}