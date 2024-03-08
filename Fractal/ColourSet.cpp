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
