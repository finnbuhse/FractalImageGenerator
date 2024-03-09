#include "ColourSet.h"

ColourSet::ColourSet(unsigned int nColours, const cv::Vec3b* const colours) : mColours(nColours)
{
	memcpy(mColours.data(), colours, nColours * sizeof(cv::Vec3b));
}

ColourSet::ColourSet(const ColourSet& other) : mColours(other.mColours)
{

}

cv::Vec3b ColourSet::operator[](const unsigned int index)
{
	return mColours[index];
}

cv::Vec3b ColourSet::sample(const float value, const bool invert)
{
	float floatIndex = (invert ? 1.0 - value : value) * (mColours.size() - 1);
	unsigned int lowerIndex = std::floor(floatIndex);
	unsigned int higherIndex = lowerIndex == (mColours.size() - 1) ? lowerIndex : lowerIndex + 1;

	cv::Vec3b c1 = mColours[lowerIndex];
	cv::Vec3b c2 = mColours[higherIndex];
	float sampleProgress = floatIndex - (float)lowerIndex;

	return c1 + sampleProgress * (c2 - c1);
}

cv::Vec3b ColourSet::quickSample(const float value, const bool invert)
{
	unsigned int index = std::floor((invert ? 1.0 - value : value) * (mColours.size() - 1));
	return mColours[index];
}
