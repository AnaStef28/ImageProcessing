#pragma once
#include "Image.h"
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

class ImageProcessing {

public:
	virtual void process(const Image& src, Image& dst) = 0;
};

class BrightnessContrast : private ImageProcessing {
private:
	double alpha;
	double beta;
public:
	BrightnessContrast();
	BrightnessContrast(double alpha, double beta);
	void process(const Image& src, Image& dst)override;
};

class GammaCorrection : private ImageProcessing {
private:
	double gamma;
public:
	GammaCorrection();
	GammaCorrection(double gamma);
	void process(const Image& src, Image& dst)override;
};


class Convolution : public ImageProcessing
{
public:
    enum ConvolutionType {
        Identity,
        MeanBlur,
        GaussianBlur,
        HorizontalSobel,
        VerticalSobel,
        Laplacian
    };
private:
    int** m_kernel;
    unsigned int m_kernelWidth;
    unsigned int m_kernelHeight;
    ConvolutionType type;
public:
    Convolution() {
        m_kernelWidth = 3;
        m_kernelHeight = 3;
        m_kernel = new int* [m_kernelHeight];
        for (int i = 0; i < m_kernelHeight; i++)
        {
            m_kernel[i] = new int[m_kernelWidth];
        }
        type = Identity;
        for (int i = 0; i < m_kernelHeight; i++)
        {
            for (int j = 0; j < m_kernelWidth; j++)
            {
                m_kernel[i][j] = 0;
            }
        }
        m_kernel[1][1] = 1;
    };

    Convolution(ConvolutionType convType) {
        m_kernelWidth = 3;
        m_kernelHeight = 3;
        m_kernel = new int* [m_kernelHeight];
        type = convType;
        switch (type)
        {
        case Identity:
            for (unsigned int i = 0; i < m_kernelHeight; i++)
            {
                m_kernel[i] = new int[m_kernelWidth];
            }
            for (unsigned int i = 0; i < m_kernelHeight; i++)
            {
                for (unsigned int j = 0; j < m_kernelWidth; j++)
                {
                    m_kernel[i][j] = 0;
                }
            }
            m_kernel[1][1] = 1;
            break;
        case MeanBlur:
            m_kernel[0] = new int[3] {1, 1, 1};
            m_kernel[1] = new int[3] {1, 1, 1};
            m_kernel[2] = new int[3] {1, 1, 1};
            break;
        case GaussianBlur:
            m_kernel[0] = new int[3] {1, 2, 1};
            m_kernel[1] = new int[3] {2, 4, 2};
            m_kernel[2] = new int[3] {1, 2, 1};
            break;
        case HorizontalSobel:
            m_kernel[0] = new int[3] {-1, -2, -1};
            m_kernel[1] = new int[3] {0, 0, 0};
            m_kernel[2] = new int[3] {1, 2, 1};
            break;
        case VerticalSobel:
            m_kernel[0] = new int[3] {-1, 0, 1};
            m_kernel[1] = new int[3] {-2, 0, 2};
            m_kernel[2] = new int[3] {-1, 0, 1};
            break;
        case Laplacian:
            m_kernel[0] = new int[3] {1, 1, 1};
            m_kernel[1] = new int[3] {1, -8, 1};
            m_kernel[2] = new int[3] {1, 1, 1};
            break;
        default:
            std::cerr << "Unknown convolution type!" << std::endl;
            break;
        }

    };

    ~Convolution() {
        for (int i = 0; i < m_kernelHeight; i++) {
            delete[] m_kernel[i];
        }
        delete[] m_kernel;
    };

    void process(const Image& src, Image& dst) override;
};



