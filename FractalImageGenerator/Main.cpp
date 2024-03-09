#include "FractalImageGenerator.h"

#include <chrono>

#include <iostream>

void applicationLoop()
{
	static FractalImageGenerator fractalImageGenerator;

	Region computeRegion;
	unsigned int targetResolution;
	unsigned int maximumIterations;
	unsigned int maximumThreads;

	std::cout << "X minimum: ";
	std::cin >> computeRegion.xBounds.minimum;
	std::cout << "X maximum: ";
	std::cin >> computeRegion.xBounds.maximum;
	std::cout << "Y minimum: ";
	std::cin >> computeRegion.yBounds.minimum;
	std::cout << "Y maximum: ";
	std::cin >> computeRegion.yBounds.maximum;
	std::cout << "Maximum iterations: ";
	std::cin >> maximumIterations;
	std::cout << "Target image resolution: ";
	std::cin >> targetResolution;
	std::cout << "Maximum threads (1 for single-threaded): ";
	std::cin >> maximumThreads;

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	cv::Mat* image = nullptr;
	if(maximumThreads == 1)
		image = fractalImageGenerator.generateFractalImageSt(computeRegion, maximumIterations, targetResolution);
	else
		image = fractalImageGenerator.generateFractalImageMt(computeRegion, maximumIterations, targetResolution, maximumThreads);
	
	cv::imwrite("generated_image.png", *image);

	fractalImageGenerator.destroyImages();

	float timeElasped = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - startTime).count();

	std::cout << "Finished in " << timeElasped << " seconds.\nEnter 'g' to generate another image or 'x' to exit : " << std::endl;

	char option = '?';
	std::cin >> option;
	while (option != 'g' && option != 'x')
	{
		std::cout << "Option not recognised, please enter it again: ";
		std::cin >> option;
	}
	
	if (option == 'g')
		applicationLoop();
	else if (option == 'x')
		return;
	else
		assert(("[ERROR] An invalid option was accepted by the program", false));
}

int main()
{
	applicationLoop();

	return 0;
}