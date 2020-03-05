// lab013.cpp: определяет точку входа для консольного приложения.
// Читает матрицу 3 на 3 из файла и находит обратную

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


#define MSIZE 5                          // максимальный размер матрицы

const int sizeM = 3;                     // актуальный размер матрицы
const float zeroBorder = (float) 1.e-7;  // граница практического ноля


struct Matrix // квадратная матрица размером не более MSIZE
{
	float elem[MSIZE][MSIZE];
	unsigned int matSize;
};

Matrix GetIdentityMatrix(unsigned int matrixSize)
{
	Matrix iden;
	iden.matSize = matrixSize;
	for (size_t i = 0; i < iden.matSize; ++i)
		for (size_t j = 0; j < iden.matSize; ++j)
		{
			iden.elem[i][j] = (i == j) ? (float) 1.0 : (float) 0.0;
		}
	return iden;
}

bool IsPracticalZero(float numberValue)
{
	return ((float)std::abs(numberValue) < zeroBorder);
}

bool IsPracticalEqualSquareMatrices(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.matSize != matrix2.matSize)
	{
		return false;
	}
	bool allElementsAreEqual = true;
	for (size_t i = 0; i < matrix1.matSize; ++i)
		for (size_t j = 0; j < matrix1.matSize; ++j)
		{
			if (!IsPracticalZero(matrix1.elem[i][j] - matrix2.elem[i][j])) allElementsAreEqual = false;
		}
	return allElementsAreEqual;
}

void FillMatrixRow(const std::string line, const size_t rowNumber, Matrix& matrix)
{
	std::istringstream dataPieces(line);
	float currentNumber;
	for (size_t j = 0; j < matrix.matSize; j++)
	{
		dataPieces >> currentNumber;
		if (dataPieces.fail())
		{
			throw
				std::invalid_argument("Ill matrix elements");
		}
		else
		{
			matrix.elem[rowNumber][j] = currentNumber;
		}
	}
}

unsigned int SetMatrixSize(unsigned int mSize)
{
	if (mSize > MSIZE)
	{
		std::cout << "This version of program operates with matrices of size not over "
			<< MSIZE << "." << std::endl;
		std::cout << "Matrix size will be set to " << MSIZE << std::endl;
		return MSIZE;
	}
	else
	{
		return mSize;
	}
}

Matrix ReadMatrix(std::istream& matrixFile, const unsigned int mSize)
{
	Matrix resMatrix;
	resMatrix.matSize = SetMatrixSize(mSize);
	
	std::string line;
	
	for (size_t i = 0; i < resMatrix.matSize; i++)
	{
		if (getline(matrixFile, line))
		{
			FillMatrixRow(line, i, resMatrix);
		}
		else
		{
			throw
				std::invalid_argument("Few strings in matrix file!");
		}
	}
	return resMatrix;
}

Matrix Minor(const Matrix& matrix, const unsigned int row, const unsigned int col)
{
	Matrix minor;

	minor.matSize = matrix.matSize - 1;
	unsigned int i = 0;

	while (i < minor.matSize)
	{
		unsigned int j = 0;
		while (j < minor.matSize)
		{
			minor.elem[i][j] = matrix.elem[i + (int)(i >= row)][j + (int)(j >= col)];
			j++;
		}
		i++;
	}

	return minor;
}

bool LoadMatrixFromFile(const std::string matrixFileName, Matrix& matrix, const int size)
{
	std::ifstream matrixFile(matrixFileName); // попытка открыть файл
	
	if (!matrixFile)
	{
		throw 
			std::invalid_argument("Can't open matrix file!");
	}
	matrix = ReadMatrix(matrixFile, size);
	return !!matrixFile;
}

void PrintMatrix(const Matrix& matrix)
{
	for (unsigned int i = 0; i < matrix.matSize; i++)
	{
		for (unsigned int j = 0; j < matrix.matSize; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << std::setw(12) << matrix.elem[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

float MatDeterm(const Matrix& matrix)
{
	float result;
	if (matrix.matSize == 1)
	{
		result = matrix.elem[0][0];
	}
	else
	{
		result = 0.0;
		for (unsigned int i = 0; i < matrix.matSize; i++)
		{
			Matrix minor = Minor(matrix, 0, i);
			result = result + matrix.elem[0][i] * (1 - 2 * ((int)i % 2)) * MatDeterm(minor);

		}
	}

	return result;
}

Matrix InverseForNonsingularMatrix(const Matrix& matrix)
{
	Matrix invMatrix;
	invMatrix.matSize = matrix.matSize;

	float det = MatDeterm(matrix);

	for (unsigned int i = 0; i < invMatrix.matSize; i++)
	{
		for (unsigned int j = 0; j < invMatrix.matSize; j++)
		{
			int signum = 1 - 2 * ((int)(i + j) % 2);
			invMatrix.elem[i][j] = MatDeterm(Minor(matrix, j, i)) * signum / det;
		}
	}
	return invMatrix;
}

bool EnoughArgs(const int numArg)
{
	if (numArg < 2)
	{
		throw
			std::invalid_argument("No enough arguments to program!\n"
				"The program must have one argument: name of file where given matrix is");
	}
	return (numArg >= 2);
}

bool FindInverse(const Matrix& matrix, Matrix& inverse)
{
	float det = MatDeterm(matrix);
	if (!IsPracticalZero(det))
	{
		inverse = InverseForNonsingularMatrix(matrix);		
	}
	else
	{
		throw
			std::domain_error("Matrix is singular so it has no inverse");
	}
	return (!IsPracticalZero(det));
}

Matrix MultiplySquareMatricesForTesting(const Matrix& left, const Matrix& right)
{
	Matrix product;
	unsigned int size = product.matSize = left.matSize;
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
		{
			product.elem[i][j] = 0;
			for (size_t k = 0; k < size; ++k)
				product.elem[i][j] += left.elem[i][k] * right.elem[k][j];
		}
	return product;
}

void PrintResults(const Matrix& matrix, const Matrix& inverseMatrix)
{
	std::cout << "Calculates inverse matrix for given 3x3 matrix" << std::endl;
	PrintMatrix(matrix);
	Matrix testProduct = MultiplySquareMatricesForTesting(matrix, inverseMatrix);
	if (IsPracticalEqualSquareMatrices(testProduct, GetIdentityMatrix(matrix.matSize)))
	{
		std::cout << "Inverse for given matrix is matrix" << std::endl;
		PrintMatrix(inverseMatrix);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Matrix dataMatrix, inverseMatrix;
		if (EnoughArgs(argc))
		{
			LoadMatrixFromFile(argv[1], dataMatrix, sizeM);
			FindInverse(dataMatrix, inverseMatrix);
			PrintResults(dataMatrix, inverseMatrix);
		}
		return 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Wrong data: " << e.what() << std::endl;
	}
	catch (const std::domain_error& e)
	{
		std::cout << "Impossible operation: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception occured!" << std::endl;
	}

	
}


