#include <iostream>
#include "SIze.h"


Size::Size() {
    this->width = 0;
    this->height = 0;
}

Size::Size(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

unsigned int Size::get_height() {
    return this->height;
}

unsigned int Size::get_width() {
    return this->width;
}

void Size::set_height(unsigned int height) {
    this->height = height;
}

void Size::set_width(unsigned int width) {
    this->width = width;
}

unsigned int Size::area() {
    return (this->width * this->height);
}

bool Size::operator==(Size& obj) {
    if (this->area() == obj.area())
        return true;
    return false;
}

bool Size::operator<(Size& obj) {
    if (this->area() < obj.area())
        return true;
    return false;
}

bool Size::operator<=(Size& obj) {
    if (this->area() <= obj.area())
        return true;
    return false;
}

bool Size::operator>(Size& obj) {
    if (this->area() > obj.area())
        return true;
    return false;
}

bool Size::operator>=(Size& obj) {
    if (this->area() >= obj.area())
        return true;
    return false;
}



