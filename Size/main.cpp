#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Drawing.h"
#include <iostream>
#include <algorithm>
#include "rectangle.h"
#include "image.h"
#include "imageProcessing.h"

void testIntersection() {
    Point p1(0, 0);
    Size s1(24, 10);
    Point p2(3, 2);
    Size s2(12, 3);
    Rectangle rect1(p1, s1);
    Rectangle rect2(p2, s2);
    Rectangle intersection = rect1 & rect2;

    std::cout << "Rectangle 1: (" << rect1.get_x() << ", " << rect1.get_y() << ", " << rect1.get_width() << ", " << rect1.get_height() << ")" << std::endl;
    std::cout << "Rectangle 2: (" << rect2.get_x() << ", " << rect2.get_y() << ", " << rect2.get_width() << ", " << rect2.get_height() << ")" << std::endl;

    std::cout << "Intersection Rectangle: ";
    if (intersection.get_width() == 0 || intersection.get_height() == 0) {
        std::cout << "No intersection" << std::endl;
    }
    else {
        std::cout << "(" << intersection.get_x() << ", " << intersection.get_y() << ", " << intersection.get_width() << ", " << intersection.get_height() << ")" << std::endl;
    }
    std::cout << std::endl;
}


void test_constructor_with_dimensions() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image img(width, height);
}

void test_copy_constructor() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image original(width, height);


    Image copy(original);
}

void test_copy_assignment_operator() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image original(width, height);
    Image copy = original;
}

void test_image_sum_load_save() {
    Image i1;
    Image i2;
    std::string imagePath = "baboon.ascii.pgm";
    if (!i1.load(imagePath)) {
        std::cerr << "Failed to load image from path: " << imagePath << std::endl;
        return;
    }
    if (!i2.load(imagePath)) {
        std::cerr << "Failed to load image from path: " << imagePath << std::endl;
        return;
    }

    Image i3 = i1 + i2;
    std::string outputPath = "baboon.ascii.pgm";
    if (!i3.save(outputPath)) {
        std::cerr << "Failed to save image to path: " << outputPath << std::endl;
        return;
    }

    std::cout << "Image loaded, summed, and saved successfully." << std::endl;
}

void test_roi() {
    // Load an image from file
    Image originalImage;
    if (!originalImage.load("baboon.ascii.pgm")) {
        std::cerr << "Failed to load the image." << std::endl;
    }

    // Define a rectangle for the ROI
    Point p(1, 1);
    Size s(255, 255);
    Rectangle roiRect(p, s); // Example: ROI starting from (1,1) with width=2 and height=2

    // Create an image to store the ROI
    Image roiImage;

    // Get the ROI

    if (!originalImage.getROI(roiImage, roiRect)) {
    }

    std::string outputPath = "baboonOut.pgm";
    roiImage.save(outputPath);
}

void testBright() {
    Image source;
    Image result;
    source.load("baboon.ascii.pgm");
    BrightnessContrast setting1(1, +120);
    setting1.process(source, result);
    result.save("baboonOut.pgm");
}

void testGammaCorrection() {
    Image source;
    Image result;

    // Load the source image
    source.load("baboon.ascii.pgm"); // load leaks

    // Create a GammaCorrection object with a gamma value of 1.5
    GammaCorrection gammaCorrection(0.2);

    // Apply gamma correction to the source image
    gammaCorrection.process(source, result);

    // Save the result to an output file
    result.save("baboonOut.pgm");
}

void testConvolution() {
    Image source;
    Image result;

    // Load the source image
    source.load("baboon.ascii.pgm"); // load leaks

    // Create a GammaCorrection object with a gamma value of 1.5
    Convolution identity(Convolution::ConvolutionType::MeanBlur);

    // Apply gamma correction to the source image
    identity.process(source, result);

    // Save the result to an output file
    result.save("baboonOut.pgm");
}

void testDraw() {
    Image img;
    img.load("baboon.ascii.pgm");

    Drawing drawer;
    Point center(50, 50);
    int radius = 20;
    unsigned char color = 255;

    drawer.drawCircle(img, center, radius, color);

    Point p1(10, 20);
    Point p2(30, 40);

    drawer.drawLine(img, p1, p2, color);

    Point tl(5, 5);
    Point br(55, 45);
    //drawer.drawRectangle(img, tl, br, color);

    img.save("babbonOut.pgm");
}

int main() {
    test_constructor_with_dimensions();
    test_copy_constructor();
    test_copy_assignment_operator();
    testIntersection();
    test_roi();
    test_image_sum_load_save();
    testBright();
    testGammaCorrection();
    testConvolution();
    testDraw();
    _CrtDumpMemoryLeaks();
    return 0;
}