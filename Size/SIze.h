#pragma once

class Size {

private:
	unsigned int width;
	unsigned int height;
public:

	//Constructors
	Size();
	Size(unsigned int width, unsigned int height);

	//Getters and setters
	unsigned int get_width();
	unsigned int get_height();
	void set_width(unsigned int width);
	void set_height(unsigned int height);

	//Comparison operators
	bool operator==(Size& obj);
	bool operator<(Size& obj);
	bool operator<=(Size& obj);
	bool operator>(Size& obj);
	bool operator>=(Size& obj);

	//Auxiliary
	unsigned int area();
};