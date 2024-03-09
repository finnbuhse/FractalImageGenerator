#include "Complex.h"

Complex Imaginary::operator+(const float& addend) const
{
	return Complex(value, addend);
}

Imaginary Imaginary::operator+(const Imaginary& addend) const
{
	return Imaginary(value + addend.value);
}

Complex Imaginary::operator+(const Complex& addend) const
{
	return Complex(addend.real, value + addend.imaginary.value);
}

Complex Imaginary::operator-(const float& subtrahend) const
{
	return Complex(value, -subtrahend);
}

Imaginary Imaginary::operator-(const Imaginary& subtrahend) const
{
	return Imaginary(value - subtrahend.value);
}

Complex Imaginary::operator-(const Complex& subtrahend) const
{
	return Complex(-subtrahend.real, value - subtrahend.imaginary.value);
}

Imaginary Imaginary::operator*(const float& multiplier) const
{
	return Imaginary(value * multiplier);
}

float Imaginary::operator*(const Imaginary& multiplier) const
{
	return -value * multiplier.value;
}

Complex Imaginary::operator*(const Complex& multiplier) const
{
	return Complex(-value * multiplier.imaginary.value, value * multiplier.real);
}

Imaginary Imaginary::operator/(const float& divisor) const
{
	return Imaginary(value/divisor);
}

float Imaginary::operator/(const Imaginary& divisor) const
{
	return value/divisor.value;
}

Complex Imaginary::operator/(const Complex& divisor) const
{
	float r = divisor.real * divisor.real + divisor.imaginary.value * divisor.imaginary.value;
	return Complex((value * divisor.imaginary.value)/r, (value * divisor.real)/r);
}

Complex Complex::operator+(const float& addend) const
{
	return Complex(real + addend, imaginary);
}

Complex Complex::operator+(const Imaginary& addend) const
{
	return Complex(real, imaginary.value + addend.value);
}

Complex Complex::operator+(const Complex& addend) const
{
	return Complex(real + addend.real, imaginary.value + addend.imaginary.value);
}

Complex Complex::operator-(const float& subtrahend) const
{
	return Complex(real - subtrahend, imaginary);
}

Complex Complex::operator-(const Imaginary& subtrahend) const
{
	return Complex(real, imaginary.value - subtrahend.value);
}

Complex Complex::operator-(const Complex& subtrahend) const
{
	return Complex(real - subtrahend.real, imaginary - subtrahend.imaginary);
}

Complex Complex::operator*(const float& multiplier) const
{
	return Complex(real * multiplier, imaginary * multiplier);
}

Complex Complex::operator*(const Imaginary& multiplier) const
{
	return Complex(-imaginary.value * multiplier.value, real * multiplier.value);
}

Complex Complex::operator*(const Complex& multiplier) const
{
	return Complex(real * multiplier.real - imaginary.value * multiplier.imaginary.value, real * multiplier.imaginary.value + imaginary.value * multiplier.real);
}

Complex Complex::operator/(const float& divisor) const
{
	return Complex(real/divisor, imaginary.value/divisor);
}

Complex Complex::operator/(const Imaginary& divisor) const
{
	return Complex(imaginary.value/divisor.value, -real/divisor.value);
}

Complex Complex::operator/(const Complex& divisor) const
{
	float r = divisor.real * divisor.real + divisor.imaginary.value * divisor.imaginary.value;
	return Complex((real * divisor.real + imaginary.value * divisor.imaginary.value)/r, (imaginary.value * divisor.real - real * divisor.imaginary.value)/r);
}