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

const int sizeM = 3;

using namespace std;



struct Matrix // квадратная матрица размером не более MSIZE
{
	float elem[MSIZE][MSIZE];
	unsigned int matSize;
};

Matrix ReadMatrix(istream& matrixFile, const unsigned int& mSize)
{
	Matrix resMatrix;

	if (mSize > MSIZE)
	{
		cout << "Matrix size is setted to max size " << MSIZE << endl;
		resMatrix.matSize = MSIZE;
	}
	else
	{
		resMatrix.matSize = mSize;
	}

	string line;

	for (unsigned int i = 0; i < resMatrix.matSize; i++)
	{
		getline(matrixFile, line);
		istringstream dataPieces(line);
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

	if ((row >= matr.matSize) || (col >= matr.matSize))
	{
		cout << "Unable to set minor!" << endl;
	}


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

bool LoadMatrixFromFile(const string matrixFileName, Matrix& matr, const int size)
{
	ifstream matrixFile(matrixFileName); // попытка открыть файл
	bool result = true;
	if (!matrixFile)
	{
		cout << "File is not found!" << endl;
		result = false;
	}
	matr = ReadMatrix(matrixFile, size);
	return result;
}

void PrintMatrix(const Matrix& matr)
{
	for (unsigned int i = 0; i < matr.matSize; i++)
	{
		for (unsigned int j = 0; j < matr.matSize; j++)
		{
			cout << setprecision(3) << setw(12) << matr.elem[i][j];
		}
		cout << endl;
	}
	cout << endl;
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

bool EnoughArgs(const int numArg)
{
	bool result = true;
	if (numArg < 2)
	{
		cout << "The program must have argument: name of file where given matrix is" << endl;
		result = false; // недостаточно аргументов
	}
	return result;
}

bool FindInverse(const Matrix& matr, Matrix& Inverse)
{
	bool result = true;
	float det = MatDeterm(matr);
	if (abs(det) < 1.e-8)
	{
		cout << "Given matrix is singular, so there is no inverse for it!" << endl;
		result = false;
	}
	else
	{
		cout << "Inverse for given matrix is matrix" << endl;
		Inverse = InverseForNonsingular(matr);
	}
	return result;
}

int main(int argc, char* argv[])
{
	cout << "Calculates inverse matrix for given 3x3 matrix" << endl;
	Matrix dataMat, Inverse;

	if (!EnoughArgs(argc)) return 0; // недостаточно аргументов
	if (!LoadMatrixFromFile(argv[1], dataMat, sizeM)) return 1; // не загружена матрица из файла

	PrintMatrix(dataMat);
	if (FindInverse(dataMat, Inverse))
	{
		PrintMatrix(Inverse);
	}

	return 0;
}



int main()
{
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
