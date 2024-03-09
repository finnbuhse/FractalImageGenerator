#pragma once

template <typename T>
struct BoundsBase
{
	T minimum;
	T maximum;

	T range() const
	{
		return maximum - minimum;
	}
};

struct Bounds : BoundsBase<float>
{

};

struct Region
{
	Bounds xBounds;
	Bounds yBounds;
};

struct UIBounds : BoundsBase<unsigned int>
{

};

struct UIRegion
{
	UIBounds xBounds;
	UIBounds yBounds;
};