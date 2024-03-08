#pragma once
#include "Complex.h"
#include "Bounds.h"
#include "ColourSet.h"

#include <vector>
#include <memory>
#include <functional>
#include <thread>


typedef std::function<float(float, float, float)> FractalColourFunction;

class FractalImageGenerator
{
private:
	std::vector<std::unique_ptr<cv::Mat>> mImages;

	ColourSet mColourSet;

	cv::Mat* createImage(unsigned int width, unsigned int height, int type, cv::Scalar initialColour);

public:
	FractalImageGenerator();

	void setColourSet(const ColourSet& colourSet);

	void generateFractalImageRegion(const Region computeRegion, const unsigned int maximumIterations, cv::Mat* const image, const UIRegion imageRegion, const FractalColourFunction& colourFunction);

	std::vector<UIRegion> getWorkerThreadImageRegions(const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int sqrtNThreads);

	void createWorkerThreads(const Region computeRegion, const unsigned int maximumIterations, cv::Mat* image, const unsigned int maximumThreads, std::vector<std::unique_ptr<std::thread>>& threadsOut);

	void joinWorkerThreads(std::vector<std::unique_ptr<std::thread>>& threads);

	cv::Mat* generateFractalImageMt(const Region computeRegion, const unsigned int maximumIterations, const unsigned int resolution, const unsigned int maximumThreads);
};

float mandelbrotColourFunction(float x, float y, float maximumIterations);