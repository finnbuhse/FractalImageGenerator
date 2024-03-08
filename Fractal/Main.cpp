#include "FractalImageGenerator.h"

#include <time.h>

#include <iostream>
#include <conio.h>

int main()
{
	float xMinimum, xMaximum, yMinimum, yMaximum;
	unsigned int resolution;
	unsigned int maximumIterations;
	std::cout << "X minimum: ";
	std::cin >> xMinimum;
	std::cout << "X maximum: ";
	std::cin >> xMaximum;
	std::cout << "Y minimum: ";
	std::cin >> yMinimum;
	std::cout << "Y maximum: ";
	std::cin >> yMaximum;
	std::cout << "Maximum iterations: ";
	std::cin >> maximumIterations;
	std::cout << "Image resolution: ";
	std::cin >> resolution;

	const Region computeRegion = { {xMinimum, xMaximum}, {yMinimum, yMaximum} };

	FractalImageGenerator fractalImageGenerator;

	cv::Mat* image = fractalImageGenerator.generateFractalImageMt(computeRegion, maximumIterations, resolution, 9);

	cv::imwrite("generated_image.png", *image);

	std::cout << "Done." << std::endl;

	std::cout << "Press any key to exit...";

	_getch();

	return 0;
}