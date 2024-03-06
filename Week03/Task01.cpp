#include <iostream>
#include <fstream>
#include <sstream>

namespace MatrixNS
{
	struct Matrix
	{
		int matrix[100][100];
		size_t rows;
		size_t columns;
	};

	unsigned int charToDigit(char ch)
	{
		return ch - '0';
	}

	unsigned int strToNumUnsigned(const char* str)
	{
		if (!str) return 0;

		unsigned res = 0;
		while (*str)
		{
			(res *= 10) += charToDigit(*str);
			str++;
		}

		return res;
	}

	int strToNum(const char* str)
	{
		if (!str) return -1;

		if (*str == '-')
		{
			str++;
			return -1 * strToNumUnsigned(str);
		}
		else
			return strToNumUnsigned(str);
	}

	void parseRow(const char* row, Matrix& mtx, size_t& rowIndex, size_t colIndex)
	{
		std::stringstream ss(row);

		char buff[1024];
		while (!ss.eof())
		{
			ss.getline(buff, 1024, ',');
			mtx.matrix[rowIndex][colIndex++] = strToNum(buff);
		}

		rowIndex++;
		mtx.columns = colIndex;
	}

	Matrix readMatrix(std::ifstream& ifs)
	{
		Matrix mtx;

		size_t row = 0, column = 0;

		char currentNum[1024];
		while (!ifs.eof())
		{
			ifs.getline(currentNum, 1024, '|');
			parseRow(currentNum, mtx, row, column);
		}

		mtx.rows = row;

		return mtx;
	}

	Matrix readMatrix(const char* fileName)
	{
		if (!fileName) return {};

		std::ifstream ifs(fileName, std::ios::in);
		if (!ifs.is_open()) return {};

		return readMatrix(ifs);
	}

	Matrix multiplyMatrices(const Matrix& mtx1, const Matrix& mtx2)
	{
		Matrix mtx;

		mtx.rows = mtx1.rows;
		mtx.columns = mtx2.columns;

		for (size_t i = 0; i < mtx1.rows; i++)
			for (size_t j = 0; j < mtx2.columns; j++)
			{
				mtx.matrix[i][j] = 0;

				for (size_t k = 0; k < mtx2.rows; k++)
					mtx.matrix[i][j] += mtx1.matrix[i][k] * mtx2.matrix[k][j];
			}

		return mtx;
	}

	void writeMatrix(std::ofstream& ofs, const Matrix& mtx)
	{
		for (size_t i = 0; i < mtx.rows; i++)
		{
			for (size_t j = 0; j < mtx.columns; j++)
				j != mtx.columns - 1 ? ofs << mtx.matrix[i][j] << ',' : ofs << mtx.matrix[i][j];
			ofs << '|';
		}
	}

	void writeMatrix(const char* fileName, const Matrix& mtx)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName, std::ios::out);
		if (!ofs.is_open()) return;

		return writeMatrix(ofs, mtx);
	}

	void printMatrix(const Matrix& mtx)
	{
		for (size_t i = 0; i < mtx.rows; i++)
		{
			for (size_t j = 0; j < mtx.columns; j++)
				std::cout << mtx.matrix[i][j] << ' ';
			std::cout << std::endl;
		}
	}
}

int main()
{
	MatrixNS::Matrix mtx1 = MatrixNS::readMatrix("first.txt");
	MatrixNS::Matrix mtx2 = MatrixNS::readMatrix("second.txt");

	MatrixNS::Matrix mtx3 = MatrixNS::multiplyMatrices(mtx1, mtx2);

	MatrixNS::printMatrix(mtx3);

	MatrixNS::writeMatrix("result.txt", mtx3);

	return 0;
}