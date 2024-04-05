#pragma once

class Point {

private:
	int x;
	int y;

public:
	Point();
	Point(int x, int y);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);

};