#include "FractalImageGenerator.h"

cv::Mat* FractalImageGenerator::createImage(unsigned int width, unsigned int height, int type, cv::Scalar initialColour)
{
	mImages.push_back(std::make_unique<cv::Mat>((int)height, (int)width, type, initialColour));
	return mImages.back().get();
}

FractalImageGenerator::FractalImageGenerator() : mColourSet(magmaColourSet) // Default to using the magma colour set
{
}

void FractalImageGenerator::setColourSet(const ColourSet& colourSet)
{
	mColourSet = colourSet;
}

void FractalImageGenerator::generateFractalImageRegion(const Region computeRegion, const unsigned int maximumIterations, cv::Mat* const image, const UIRegion imageRegion, const FractalColourFunction& colourFunction)
{
	float pixelRangeX = computeRegion.xBounds.range() / image->cols;
	float pixelRangeY = computeRegion.yBounds.range() / image->rows;

	for (unsigned int imageX = imageRegion.xBounds.minimum; imageX < imageRegion.xBounds.maximum; imageX++)
	{
		for (unsigned int imageY = imageRegion.yBounds.minimum; imageY < imageRegion.yBounds.maximum; imageY++)
		{
			// The origin for image coordinates is at the top left
			// Get cartesian coordinates where the origin is at the bottom left
			float cartesianX = computeRegion.xBounds.minimum + ((float)imageX * pixelRangeX);
			float cartesianY = computeRegion.yBounds.minimum + ((float)(image->rows - imageY - 1) * pixelRangeY);

			// Custom algorithm
			float colourNormalised = colourFunction(cartesianX, cartesianY, maximumIterations);

			unsigned char colour = colourNormalised * 255;
			image->at<cv::Vec3b>(imageY, imageX) = mColourSet[colour];
		}
	}
}

std::vector<UIRegion> FractalImageGenerator::getWorkerThreadImageRegions(const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int sqrtNThreads)
{
	std::vector<UIRegion> result;

	for (unsigned int x = 0; x < sqrtNThreads; x++)
	{
		for (unsigned int y = 0; y < sqrtNThreads; y++)
		{
			result.push_back(UIRegion{
				UIBounds{imageWidth / sqrtNThreads * x, imageWidth / sqrtNThreads * (x + 1)},
				UIBounds{imageHeight / sqrtNThreads * y, imageHeight / sqrtNThreads * (y + 1)} });
		}
	}

	return result;
}

void FractalImageGenerator::createWorkerThreads(const Region computeRegion, const unsigned int maximumIterations, cv::Mat* image, const unsigned int maximumThreads, std::vector<std::unique_ptr<std::thread>>& threadsOut)
{
	// Actual number of threads is the highest square number below max threaimage,ds to simplify image region calculation
	unsigned int sqrtNThreads = (unsigned int)std::floor(std::sqrt((float)maximumThreads));
	unsigned int nThreads = sqrtNThreads * sqrtNThreads;

	std::vector<UIRegion> threadImageRegions = getWorkerThreadImageRegions(image->cols, image->rows, sqrtNThreads);

	for (unsigned int i = 0; i < threadImageRegions.size(); i++)
	{
		threadsOut.push_back(std::make_unique<std::thread>(&FractalImageGenerator::generateFractalImageRegion, this, computeRegion, maximumIterations, image, threadImageRegions[i], mandelbrotColourFunction));
	}
}

void FractalImageGenerator::joinWorkerThreads(std::vector<std::unique_ptr<std::thread>>& threads)
{
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i].get()->join();
	}
}


cv::Mat* FractalImageGenerator::generateFractalImageMt(const Region computeRegion, const unsigned int maximumIterations, const unsigned int resolution, const unsigned int maximumThreads)
{
	float aspectRatio = computeRegion.xBounds.range() / computeRegion.yBounds.range();

	cv::Mat* image = createImage(/* Width */ (unsigned int)(aspectRatio * (float)resolution), /* Height */ resolution, CV_8UC3, cv::Scalar(255, 255, 255));

	const unsigned int imageWidth = image->cols;
	const unsigned int imageHeight = image->rows;

	std::vector<std::unique_ptr<std::thread>> threads;
	createWorkerThreads(computeRegion, maximumIterations, image, maximumThreads, threads);
	joinWorkerThreads(threads);

	return image;
}

float mandelbrotColourFunction(float x, float y, float maximumIterations)
{
	Complex c(x, y);
	Complex current(0, 0);
	unsigned int iteration = 0;
	for (iteration; iteration < maximumIterations; iteration++)
	{
		current = current * current + c;
		if (sqrtf(current.real * current.real + current.imaginary.value * current.imaginary.value) > 2)
			break;
	}
	return (float)iteration / (float)maximumIterations;
}
