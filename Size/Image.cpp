#include "Image.h"
#include <fstream>
using namespace std;

Image::Image()
{
	this->m_data = nullptr;
	this->m_width = 0;
	this->m_height = 0;
}

Image::Image(unsigned int w, unsigned int h)
{
	this->m_height = h;
	this->m_width = w;
	this->m_data = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		this->m_data[i] = new unsigned char[w];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			this->m_data[i][j] = 0;
	
}

Image::Image(const Image& other)
{
	this->m_height = other.m_height;
	this->m_width = other.m_width;
	this->m_data = new unsigned char* [other.m_height];
	for (int i = 0; i < other.m_height; i++)
		this->m_data[i] = new unsigned char[other.m_width];

	for (int i = 0; i < other.m_height; i++)
		for (int j = 0; j < other.m_width; j++)
			this->m_data[i][j] = other.m_data[i][j];
}

Image::~Image()
{
	if (m_data) 
		for (int i = 0; i < m_height; ++i) {
			delete[] m_data[i];
		}
	delete[] this->m_data;
}

Image& Image::operator=(const Image& other) {

	if (this != &other) {
		for (int i = 0; i < this->m_height; i++) {
			delete[] this->m_data[i];
		}

		delete[] this->m_data;

		m_height = other.m_height;
		m_width = other.m_width;
		this->m_data = new unsigned char* [other.m_height];
		for (int i = 0; i < other.m_height; i++)
			this->m_data[i] = new unsigned char[other.m_width];

		for (int i = 0; i < other.m_height; i++)
			for (int j = 0; j < other.m_width; j++)
				this->m_data[i][j] = other.m_data[i][j];
	}
	return *this;
}


bool Image::isEmpty() const
{
	if (this->m_data == nullptr && this->m_height == 0 && this->m_width == 0)
		return true;
	return false;
}

Size Image::size() const
{
	Size s(this->m_width, this->m_height);
	return s;
}

unsigned int Image::width() const {
		return this->m_width;
}

unsigned int Image::height() const{
	return this->m_height;
}

void Image::set_width(unsigned int w)
{
	this->m_width = w;
}

void Image::set_height(unsigned int h) {
	this->m_height = h;
}

std::istream& operator>>(std::istream& is, Image& dt) {
	std::string format;
	int w, h, max_val;
	is >> format;
	if (format != "P2") {
		std::cerr << "Invalid format";
		return is;
	}
	is >> w >> h >> max_val;
	if (max_val != 255) {
		std::cerr << "Invalid value";
		return is;
	}

	Image img(w, h);
	dt = img;
	for (int i=0; i<h; i++)
		for (int j = 0; j < w; j++) {
			int val;
			is >> val;
			dt.m_data[i][j] = static_cast<int>(val);
		}

	return is;
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {

	os << "P2\n";
	os << dt.m_width << " " << dt.m_height<<"\n";
	os << "255\n";
	unsigned int h = dt.m_height;
	unsigned int w = dt.m_width;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			os << static_cast<int>(dt.m_data[i][j])<< " ";;
		}
		os << "\n";
	}
	return os;
}

bool Image::save(std::string imagePath) const {
	std::ofstream file(imagePath);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file for writing: " << imagePath << std::endl;
		return false;
	}
	file << *this;
	file.close();
	return true;
}

bool Image::load(std::string imagePath){
	std::ifstream file(imagePath);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file for reading: " << imagePath << std::endl;
		return false;
	}
	if (!(file >> *this)) {
		std::cerr << "Error: Unable to read image data from file: " << imagePath << std::endl;
		return false;
	}
	file.close();
	return true;
}

Image Image::zeros(unsigned int width, unsigned int height){
	Image img(width, height);
	img.m_data = new unsigned char* [height];
	for (int i = 0; i < height; i++)
		img.m_data[i] = new unsigned char[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img.m_data[i][j] = 0;

	return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image img(width, height);
	img.m_data = new unsigned char* [height];
	for (int i = 0; i < height; i++)
		img.m_data[i] = new unsigned char[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img.m_data[i][j] = 1;

	return img;
}

unsigned char& Image::at(unsigned int x, unsigned int y) const{
	return m_data[x][y];
}

unsigned char& Image::at(Point pt) {
	int x = pt.get_x();
	int y = pt.get_y();
	return this->m_data[x][y];
}

unsigned char* Image::row(int y)
{
	return this->m_data[y];
}

Image Image::operator+(const Image& i) {
	if (this->m_height != i.m_height or this->m_width != i.m_width)
		throw std::runtime_error("Images have different resolutions");
	int h = this->m_height;
	int w = this->m_width;
	for (int index = 0; index < h; index++) {
		for (int j = 0; j < w; j++) {
			if (this->m_data[index][j] + i.m_data[index][j] > 255)
				this->m_data[index][j] = 255;
			else
				this->m_data[index][j] += i.m_data[index][j];
		}
	}
	return *this;
}

Image Image::operator-(const Image& i) {
	if (this->m_height != i.m_height or this->m_width != i.m_width)
		throw std::runtime_error("Images have different resolutions");
	int h = this->m_height;
	int w = this->m_width;
	for (int index = 0; index < h; index++) {
		for (int j = 0; j < w; j++) {
			if (this->m_data[index][j] - i.m_data[index][j] < 0)
				this->m_data[index][j] = 0;
			else
				this->m_data[index][j] -= i.m_data[index][j];
		}
	}
	return *this;
}

Image Image::operator*(double s) {

	int h = this->m_height;
	int w = this->m_width;
	for (int index = 0; index < h; index++) {
		for (int j = 0; j < w; j++) {
			if (this->m_data[index][j] *s > 255)
				this->m_data[index][j] = 255;
			else
				this->m_data[index][j] *=s;
		}
	}
	return *this;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect)
{
	int h = roiRect.get_height();
	int w = roiRect.get_width();
	roiImg.set_height(h);
	roiImg.set_width(w);
	roiImg.m_data = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		roiImg.m_data[i] = new unsigned char[w];

	int offset_x = roiRect.get_x();
	int offset_y = roiRect.get_y();
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			roiImg.m_data[i][j] = this->m_data[i+offset_x][j+offset_y];
		}
	}
	return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	if (roiImg.m_height <= 0 || roiImg.m_width <= 0) {
		throw std::runtime_error("Valeleu");
		return false;
	}
	roiImg.set_height(height);
	roiImg.set_width(width);
	roiImg.m_data = new unsigned char* [height];
	for (int i = 0; i < height; i++)
		roiImg.m_data[i] = new unsigned char[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			roiImg.m_data[i][j] = this->m_data[i+x][j+y];
		}
	}
	return true;
}
