#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace ComplexNumbers
{
	struct ComplexNumber
	{
		double realPart, imaginaryPart;
	};

	ComplexNumber sumComplexNumbers(const ComplexNumber& c1, const ComplexNumber& c2)
	{
		return ComplexNumber{ c1.real + c2.real, c1.imaginary + c2.imaginary };
	}

	ComplexNumber subtractComplexNumbers(const ComplexNumber& c1, const ComplexNumber& c2)
	{
		return ComplexNumber{ c1.real - c2.real, c1.imaginary - c2.imaginary };
	}

	ComplexNumber multiplyComplexNumbers(const ComplexNumber& c1, const ComplexNumber& c2)
	{
		return ComplexNumber{ 
			(c1.realPart * c2.realPart) - (c1.imaginaryPart * c2.imaginaryPart), 
			(c1.realPart * c2.imaginaryPart) + (c1.imaginaryPart * c2.realPart) 
		};
	}

	ComplexNumber divideComplexNumbers(const ComplexNumber& c1, const ComplexNumber& c2)
	{
		return ComplexNumber{
			((c1.realPart * c2.realPart) + (c1.imaginaryPart * c2.imaginaryPart)) / (c2.realPart * c2.realPart + c2.imaginaryPart * c2.imaginaryPart),
			((c1.imaginaryPart * c2.realPart) - (c1.realPart * c2.imaginaryPart)) / (c2.realPart * c2.realPart + c2.imaginaryPart * c2.imaginaryPart)
		};
	}

	void printNumber(const ComplexNumber& complexNumber)
	{
		cout << "( " << complexNumber.realPart << ", " << complexNumber.imaginaryPart << ") " << endl;
	}
}

int main()
{
	using namespace ComplexNumbers;

	ComplexNumber complexOne = { 1, 2 };
	ComplexNumber complexTwo = { 2, 3 };

	ComplexNumber complexResult = sumComplexNumbers(complexOne, complexTwo);

	printNumber(complexResult);

	return 0;
}