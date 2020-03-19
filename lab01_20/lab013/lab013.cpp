// lab013.cpp: определяет точку входа для консольного приложения.
// Читает матрицу 3 на 3 из файла и находит обратную

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <optional>


constexpr int MAX_MATRIX_SIZE = 5;                          // максимальный размер матрицы
const int MATRIX_SIZE = 3;                     // актуальный размер матрицы
const float ZERO_BORDER = (float) 1.e-5;  // граница практического ноля


struct Matrix // квадратная матрица размером не более MAX_MATRIX_SIZE
{
	float elem[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
	unsigned int matrixSize;
};

Matrix GetIdentityMatrix(unsigned int matrixSize)
{
	Matrix iden;
	iden.matrixSize = matrixSize;
	for (size_t i = 0; i < iden.matrixSize; ++i)
	{
		for (size_t j = 0; j < iden.matrixSize; ++j)
		{
			iden.elem[i][j] = (i == j) ? (float) 1.0 : (float) 0.0;
		}
	}
	return iden;
}

bool IsCloseToZero(float numberValue)
{
	return ((float)std::abs(numberValue) < ZERO_BORDER);
}

bool AreMatricesCloseToBeEqual(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.matrixSize != matrix2.matrixSize)
	{
		return false;
	}
	bool allElementsAreEqual = true;
	for (size_t i = 0; i < matrix1.matrixSize; ++i)
	{
		for (size_t j = 0; j < matrix1.matrixSize; ++j)
		{
			if (!IsCloseToZero(matrix1.elem[i][j] - matrix2.elem[i][j])) allElementsAreEqual = false;
		}
	}
	return allElementsAreEqual;
}

void FillMatrixRow(const std::string& line, const size_t rowNumber, Matrix& matrix)
{
	std::istringstream dataPieces(line);
	float currentNumber;
	for (size_t j = 0; j < matrix.matrixSize; j++)
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
	if (mSize > MAX_MATRIX_SIZE)
	{
		std::cout << "This version of program operates with matrices of size not over "
			<< MAX_MATRIX_SIZE << "." << std::endl;
		std::cout << "Matrix size will be set to " << MAX_MATRIX_SIZE << std::endl;
		return MAX_MATRIX_SIZE;
	}
	else
	{
		return mSize;
	}
}

Matrix LoadMatrix(std::istream& matrixFile, const unsigned int mSize)
{
	Matrix resMatrix;
	resMatrix.matrixSize = SetMatrixSize(mSize);
	
	std::string line;
	
	for (size_t i = 0; i < resMatrix.matrixSize; i++)
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

	minor.matrixSize = matrix.matrixSize - 1;
	unsigned int i = 0;

	while (i < minor.matrixSize)
	{
		unsigned int j = 0;
		while (j < minor.matrixSize)
		{
			minor.elem[i][j] = matrix.elem[i + (int)(i >= row)][j + (int)(j >= col)];
			j++;
		}
		i++;
	}

	return minor;
}

bool LoadMatrixFromFile(const std::string& matrixFileName, Matrix& matrix, const int size)
{
	std::ifstream matrixFile(matrixFileName); // попытка открыть файл
	
	if (!matrixFile)
	{
		throw 
			std::invalid_argument("Can't open matrix file!");
	}
	matrix = LoadMatrix(matrixFile, size);
	return !!matrixFile;
}

void PrintMatrix(const Matrix& matrix)
{
	for (unsigned int i = 0; i < matrix.matrixSize; i++)
	{
		for (unsigned int j = 0; j < matrix.matrixSize; j++)
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
	if (matrix.matrixSize == 1)
	{
		result = matrix.elem[0][0];
	}
	else
	{
		result = 0.0;
		int signum = 1;
		for (unsigned int i = 0; i < matrix.matrixSize; i++)
		{
			Matrix minor = Minor(matrix, 0, i);
			result = result + matrix.elem[0][i] * signum * MatDeterm(minor);
			signum = -signum;
		}
	}

	return result;
}

Matrix GetInverseForNonsingularMatrix(const Matrix& matrix, float det)
{
	Matrix invMatrix;
	invMatrix.matrixSize = matrix.matrixSize;

	if (det == 0)
	{
		throw
			std::domain_error("Matrix is singular so it has no inverse");
	}
	int signum1 = 1;
	for (unsigned int i = 0; i < invMatrix.matrixSize; i++)
	{
		int signum2 = 1;
		for (unsigned int j = 0; j < invMatrix.matrixSize; j++)
		{
			invMatrix.elem[i][j] = MatDeterm(Minor(matrix, j, i)) * signum1 * signum2  / det;
			signum2 = -signum2;
		}
		signum1 = -signum1;
	}
	return invMatrix;
}

bool FindInverse(const Matrix& matrix, Matrix& inverse)
{
	float det = MatDeterm(matrix);
	if (!IsCloseToZero(det))
	{
		inverse = GetInverseForNonsingularMatrix(matrix, det);		
	}
	else
	{
		throw
			std::domain_error("Matrix is singular so it has no inverse");
	}
	return (!IsCloseToZero(det));
}

Matrix MultiplySquareMatricesForTesting(const Matrix& left, const Matrix& right)
{
	Matrix product;
	unsigned int size = product.matrixSize = left.matrixSize;
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			product.elem[i][j] = 0;
			for (size_t k = 0; k < size; ++k)
			{
				product.elem[i][j] += left.elem[i][k] * right.elem[k][j];
			}
		}
	}
	return product;
}

void PrintResults(const Matrix& matrix, const Matrix& inverseMatrix)
{
	std::cout << "Calculates inverse matrix for given 3x3 matrix" << std::endl;
	PrintMatrix(matrix);
	Matrix testProduct = MultiplySquareMatricesForTesting(matrix, inverseMatrix);
	if (AreMatricesCloseToBeEqual(testProduct, GetIdentityMatrix(matrix.matrixSize)))
	{
		std::cout << "Inverse for given matrix is matrix" << std::endl;
		PrintMatrix(inverseMatrix);
	}
}

std::string ParseCommandLine(int argc, char* argv[])
{
	if (argc < 2)
	{
		throw
			std::invalid_argument("No enough arguments to program!\n"
				"The program must have one argument: name of file where given matrix is");
	}
	
	return std::string(argv[1]);
}

int main(int argc, char* argv[])
{
	try
	{
		Matrix dataMatrix, inverseMatrix;
		std::string matrixFileName = ParseCommandLine(argc, argv);
		
		LoadMatrixFromFile(matrixFileName, dataMatrix, MATRIX_SIZE);
		FindInverse(dataMatrix, inverseMatrix);
		PrintResults(dataMatrix, inverseMatrix);
		
		return 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Wrong data: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::domain_error& e)
	{
		std::cout << "Impossible operation: " << e.what() << std::endl;
		return 2;
	}
	catch (...)
	{
		std::cout << "Unknown exception occured!" << std::endl;
		return 3;
	}
}


