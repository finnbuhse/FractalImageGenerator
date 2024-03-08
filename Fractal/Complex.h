#pragma once

class Complex;

class Imaginary
{
public:
	float value;

	Imaginary(const float& value) :
		value(value) {}

	Complex operator+(const float& addend) const;
	Imaginary operator+(const Imaginary& addend) const;
	Complex operator+(const Complex& addend) const;

	Complex operator-(const float& subtrahend) const;
	Imaginary operator-(const Imaginary& subtrahend) const;
	Complex operator-(const Complex& subtrahend) const;

	Imaginary operator*(const float& multiplier) const;
	float operator*(const Imaginary& multiplier) const;
	Complex operator*(const Complex& multiplier) const;

	Imaginary operator/(const float& divisor) const;
	float operator/(const Imaginary& divisor) const;
	Complex operator/(const Complex& divisor) const;
};

class Complex
{
public:
	float real;
	Imaginary imaginary;

	Complex(const float& real, const Imaginary& imaginary) :
		real(real), imaginary(imaginary) {}

	Complex operator+(const float& addend) const;
	Complex operator+(const Imaginary& addend) const;
	Complex operator+(const Complex& addend) const;

	Complex operator-(const float& subtrahend) const;
	Complex operator-(const Imaginary& subtrahend) const;
	Complex operator-(const Complex& subtrahend) const;

	Complex operator*(const float& multiplier) const;
	Complex operator*(const Imaginary& multiplier) const;
	Complex operator*(const Complex& multiplier) const;

	Complex operator/(const float& divisor) const;
	Complex operator/(const Imaginary& divisor) const;
	Complex operator/(const Complex& divisor) const;
};