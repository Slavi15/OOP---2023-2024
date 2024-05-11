#pragma once

#include <iostream>
#include <fstream>

class Complex
{
private:
	double realPart = 0;
	double imaginaryPart = 0;

public:
	Complex();
	Complex(double realPart, double imaginaryPart);

	Complex(const Complex& other) = default;
	Complex& operator=(const Complex& other) = default;

	Complex(Complex&& other) noexcept = default;
	Complex& operator=(Complex&& other) noexcept = default;

	const double getReal() const;
	const double getImaginary() const;

	void setReal(double realPart);
	void setImaginary(double imaginaryPart);

	Complex getConjugated() const;

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);

	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	friend Complex operator+(const Complex& lhs, const Complex& rhs);
	friend Complex operator-(const Complex& lhs, const Complex& rhs);

	friend Complex operator*(const Complex& lhs, const Complex& rhs);
	friend Complex operator/(const Complex& lhs, const Complex& rhs);

	friend const bool operator==(const Complex& lhs, const Complex& rhs);
	friend const bool operator!=(const Complex& lhs, const Complex& rhs);

	friend std::istream& operator>>(std::istream& is, Complex& ref);
	friend std::ostream& operator<<(std::ostream& os, const Complex& ref);
};