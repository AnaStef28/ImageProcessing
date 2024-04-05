#define _CRTDBG_MAP_ALLOC
#include "ImageProcessing.h"
#include <crtdbg.h>
#include <fstream>
#include <cmath>

BrightnessContrast::BrightnessContrast()
{
	this->alpha = 1;
	this->beta = 0;
}

BrightnessContrast::BrightnessContrast(double alpha, double beta)
{
	this->alpha = alpha;
	this->beta = beta;
}

void BrightnessContrast::process(const Image& src, Image& dst)
{
	dst = src;
	dst = dst * this->alpha;
	Image betas = Image::ones(dst.width(), dst.height());
	betas=betas * (this->beta); 
	dst = dst + betas;
}


GammaCorrection::GammaCorrection()
{
	this->gamma = 1;
}

GammaCorrection::GammaCorrection(double gamma){
	this->gamma = gamma;
}

void GammaCorrection::process(const Image& src, Image& dst){
	dst = src;
	for (int i=0; i<dst.height(); i++)
		for (int j = 0; j < dst.width(); j++) {
			if (pow(dst.at(i, j), this->gamma) > 255)
				dst.at(i, j) = 255;
			else
				dst.at(i, j) = pow(dst.at(i, j), this->gamma);
		}
}


void Convolution::process(const Image& src, Image& dst) {
    dst = src;
    for (int row = 0; row < src.height(); row++) {
        for (int col = 0; col < src.width(); col++) {
            double sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (row + i >= 0 && row + i < src.height() && col + j >= 0 && col + j < src.width())
                        sum += src.at(row + i, col + j) * m_kernel[i + 1][j + 1];
                }
            }
            switch (type)
            {
            case Identity:
                dst.at(row, col) = sum;
                break;
            case MeanBlur:
                dst.at(row, col) = sum / 9;
                break;
            case GaussianBlur:
                dst.at(row, col) = sum / 16;
                break;
            case HorizontalSobel:
                dst.at(row, col) = sum / 8 + 127.5;
                break;
            case VerticalSobel:
                dst.at(row, col) = sum / 8 + 127.5;
                break;
            case Laplacian:
                dst.at(row, col) = sum;
                break;
            default:
                dst.at(row, col) = sum;
                break;
            }

        }
    }
}

