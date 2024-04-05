#include "Drawing.h"
#include <fstream>

void Drawing::drawCircle(Image& img, Point center, int radius, unsigned char color)
{
	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++) {
			if ((i-center.get_x())*(i - center.get_x()) + (j - center.get_y()) * (j - center.get_y()) <=(radius*radius))
				img.at(i, j) = color;
		}

}

void Drawing::drawLine(Image& img, Point p1, Point p2, unsigned char color)
{
	float aux;
	if ((p2.get_x() - p1.get_x()) != 0 && (p2.get_y() - p1.get_y()) != 0)
		aux = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
	else aux = 0;

	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++) {
			if ((i - p1.get_y()) == aux * (j - p1.get_x()))
				img.at(i, j) = color;
		}
}

void drawRectangle(Image& img, Rectangle r, unsigned char color) {
    int x = r.get_x();
    int y = r.get_y();
    int width = r.get_width();
    int height = r.get_height();

    for (int i = x; i < x + width; ++i) {
        img.at(i, y) = color;
        img.at(i, y + height - 1) = color;
    }

    for (int i = y; i < y + height; ++i) {
        img.at(x, i) = color;
        img.at(x + width - 1, i) = color;
    }
}

void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
    int minX = std::min(tl.get_x(), br.get_x());
    int minY = std::min(tl.get_y(), br.get_y());
    int maxX = std::max(tl.get_x(), br.get_x());
    int maxY = std::max(tl.get_y(), br.get_y());
    Point p(minX, minY);
    Size s(maxX - minX + 1, maxY - minY + 1);
    Rectangle rect(p, s);
    drawRectangle(img, rect, color);
}





