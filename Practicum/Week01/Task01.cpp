#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int** createMatrix(size_t N, size_t M)
{
	int** mtx = new int* [N];

	for (size_t i = 0; i < N; i++)
	{
		mtx[i] = new int[M];

		for (size_t j = 0; j < M; j++)
		{
			int num;
			cin >> num;

			mtx[i][j] = num;
		}
	}

	return mtx;
}

int** transposeMatrix(int** mtx, size_t N, size_t M)
{
	if (!mtx)
		return nullptr;

	int** transpose = new int* [M];

	for (size_t i = 0; i < M; i++)
	{
		transpose[i] = new int[N];

		for (size_t j = 0; j < N; j++)
			transpose[i][j] = mtx[j][i];
	}

	return transpose;
}

void freeMatrix(int** mtx, size_t N, size_t M)
{
	if (!mtx)
		return;

	for (size_t i = 0; i < N; i++)
		delete[] mtx[i];

	delete[] mtx;
}

void printMatrix(int** mtx, size_t rows, size_t colls)
{
	if (!mtx)
		return;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < colls; j++)
			cout << mtx[i][j] << ' ';

		cout << endl;
	}
}

int main()
{
	unsigned int N, M;
	cin >> N >> M;

	int** matrix = createMatrix(N, M);
	int** transpose = transposeMatrix(matrix, N, M);

	printMatrix(transpose, M, N);

	freeMatrix(matrix, N, M);
	freeMatrix(transpose, N, M);
}