// lab013.cpp: определяет точку входа для консольного приложения.
// Читает матрицу 3 на 3 из файла и находит обратную

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>



#define MSIZE 5
#define TESTING_MODE 1

enum errorType { NoError = 0, NoEnoughArgs, NoMatrixFile, SingularMatrix };

const int sizeM = 3;


struct Matrix // квадратная матрица размером не более MSIZE
{
	float elem[MSIZE][MSIZE];
	unsigned int matSize;
};

Matrix ReadMatrix(std::istream& matrixFile, const unsigned int& mSize)
{
	Matrix resMatrix;

	if (mSize > MSIZE)
	{
		resMatrix.matSize = MSIZE;
	}
	else
	{
		resMatrix.matSize = mSize;
	}

	std::string line;

	for (unsigned int i = 0; i < resMatrix.matSize; i++)
	{
		getline(matrixFile, line);
		std::istringstream dataPieces(line);
		for (unsigned int j = 0; j < resMatrix.matSize; j++)
		{
			dataPieces >> resMatrix.elem[i][j];
		}
	}
	return resMatrix;
}

Matrix Minor(const Matrix& matr, const unsigned int row, const unsigned int col)
{
	Matrix minor;

	minor.matSize = matr.matSize - 1;
	unsigned int i = 0;

	while (i < minor.matSize)
	{
		unsigned int j = 0;
		while (j < minor.matSize)
		{
			minor.elem[i][j] = matr.elem[i + (int)(i >= row)][j + (int)(j >= col)];
			j++;
		}
		i++;
	}

	return minor;
}

bool LoadMatrixFromFile(const std::string matrixFileName, Matrix& matr, const int size, errorType& error)
{
	std::ifstream matrixFile(matrixFileName); // попытка открыть файл
	
	if (!matrixFile)
	{
		error = NoMatrixFile;
	}
	matr = ReadMatrix(matrixFile, size);
	return !!matrixFile;
}

void PrintMatrix(const Matrix& matr)
{
	for (unsigned int i = 0; i < matr.matSize; i++)
	{
		for (unsigned int j = 0; j < matr.matSize; j++)
		{
			std::cout << std::setprecision(3) << std::setw(12) << matr.elem[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PrintMatrixRawData(const Matrix& matr)
{
	for (unsigned int i = 0; i < matr.matSize; i++)
	{
		for (unsigned int j = 0; j < matr.matSize; j++)
		{
			std::cout << std::setprecision(3) << matr.elem[i][j] << " ";
		}
	}
	std::cout << std::endl;
}



float MatDeterm(const Matrix& matr)
{
	float result;
	if (matr.matSize == 1)
	{
		result = matr.elem[0][0];
	}
	else
	{
		result = 0.0;
		for (unsigned int i = 0; i < matr.matSize; i++)
		{
			Matrix minor = Minor(matr, 0, i);
			result = result + matr.elem[0][i] * (1 - 2 * ((int)i % 2)) * MatDeterm(minor);

		}
	}

	return result;
}

Matrix InverseForNonsingular(const Matrix& theMatrix)
{
	Matrix invMat;

	invMat.matSize = theMatrix.matSize;

	float det = MatDeterm(theMatrix);

	for (unsigned int i = 0; i < invMat.matSize; i++)
	{
		for (unsigned int j = 0; j < invMat.matSize; j++)
		{
			int signum = 1 - 2 * ((int)(i + j) % 2);
			invMat.elem[i][j] = MatDeterm(Minor(theMatrix, j, i)) * signum / det;
		}
	}
	return invMat;
}

bool EnoughArgs(const int numArg, errorType& error)
{
	if (numArg < 2)
	{
		error = NoEnoughArgs;	// недостаточно аргументов
	}
	return (numArg >= 2);
}

bool FindInverse(const Matrix& matr, Matrix& inverse, errorType& error)
{
	float det = MatDeterm(matr);
	if (abs(det) > 1.e-8)
	{
		inverse = InverseForNonsingular(matr);		
	}
	else
	{
		error = SingularMatrix;		
	}
	return (abs(det) > 1.e-8);
}

void PrintResults(const Matrix& matrix, const Matrix& inverse, const errorType& error)
{
	if (TESTING_MODE) {
		if (!error)
		{
			PrintMatrixRawData(inverse);
		}
		else
		{
			std::cout << (int)error << std::endl;
		}
	}
	else
	{
		std::cout << "Calculates inverse matrix for given 3x3 matrix" << std::endl;

		switch (error)
		{
		case NoEnoughArgs:
			std::cout << "The program must have argument: name of file where given matrix is" << std::endl;
			break;
		case NoMatrixFile:
			std::cout << "File is not found!" << std::endl;
			break;
		case SingularMatrix:
			PrintMatrix(matrix);
			std::cout << "Given matrix is singular, so there is no inverse for it!" << std::endl;
			break;
		default:
			PrintMatrix(matrix);
			std::cout << "Inverse for given matrix is matrix" << std::endl;
			PrintMatrix(inverse);			
		}
	}
}

int main(int argc, char* argv[])
{
	
	Matrix dataMat, inverse;
	errorType error = NoError;

	if (!EnoughArgs(argc, error))
	{
		PrintResults(dataMat, inverse, error);
		return 1; // недостаточно аргументов
	}
	if (!LoadMatrixFromFile(argv[1], dataMat, sizeM, error))
	{
		PrintResults(dataMat, inverse, error);
		return 2; // не загружена матрица из файла
	}
	
	FindInverse(dataMat, inverse, error);
	PrintResults(dataMat, inverse, error);

	return 0;
}



