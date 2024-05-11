#include "Complex.h"

Complex::Complex() = default;

Complex::Complex(double realPart, double imaginaryPart) : realPart(realPart), imaginaryPart(imaginaryPart) {}

const double Complex::getReal() const
{
	return this->realPart;
}

const double Complex::getImaginary() const
{
	return this->imaginaryPart;
}

void Complex::setReal(double realPart)
{
	this->realPart = realPart;
}

void Complex::setImaginary(double imaginaryPart)
{
	this->imaginaryPart = imaginaryPart;
}

Complex Complex::getConjugated() const
{
	return Complex(getReal(), -getImaginary());
}

Complex& Complex::operator+=(const Complex& other)
{
	this->realPart += other.realPart;
	this->imaginaryPart += other.imaginaryPart;

	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	this->realPart -= other.realPart;
	this->imaginaryPart -= other.imaginaryPart;

	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	this->realPart = (getReal() * other.getReal()) - (getImaginary() * other.getImaginary());
	this->imaginaryPart = (getReal() * other.getImaginary()) + (getImaginary() * other.getReal());

	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	Complex conjugated = other.getConjugated();

	Complex otherCopy(other);

	(*this) *= conjugated;

	otherCopy *= conjugated;

	if (otherCopy.getReal() != 0)
	{
		this->realPart /= otherCopy.getReal();
		this->imaginaryPart /= otherCopy.getImaginary();
	}

	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex toReturn(lhs);
	toReturn += rhs;
	return toReturn;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex toReturn(lhs);
	toReturn -= rhs;
	return toReturn;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex toReturn(lhs);
	toReturn *= rhs;
	return toReturn;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex toReturn(lhs);
	toReturn /= rhs;
	return toReturn;
}

const bool operator==(const Complex& lhs, const Complex& rhs)
{
	return lhs.getReal() == rhs.getReal() && lhs.getImaginary() == rhs.getImaginary();
}

const bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Complex& ref)
{
	return is >> ref.realPart >> ref.imaginaryPart;
}

std::ostream& operator<<(std::ostream& os, const Complex& ref)
{
	return os << ref.realPart << " + " << ref.imaginaryPart << "i" << std::endl;
}