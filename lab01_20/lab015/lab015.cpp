// lab015.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Программа выполняет поиск одного из возможных кратчайших путей между двумя точками в лабиринте, заданном в текстовом файле. 
Начальные и конечные точки задаются при помощи символов A и B. Найденный путь изображается при помощи символа «точка».

Лабиринт имеет максимальные размеры до 100*100 клеток и не обязательно должен иметь прямоугольную форму – 
задача приложения самостоятельно определить границы лабиринта, просканировав входной файл.

Во входном файле могут быть не заданы начальная и конечная точки, либо заданы больше чем 1 раз. 
При обнаружении такой ситуации приложение должно сообщить пользователю об ошибке.
При отсутствии пути между точками A и B необходимо вывести лабиринт без указания пути.

Формат командой строки: labyrinth.exe <input file> <output file>
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

constexpr size_t FIELD_SIDE = 100; // сторона квадратного поля, в котором размещен лабиринт
constexpr size_t CELLS_NUMBER = FIELD_SIDE * FIELD_SIDE;
enum Cell {Wall = -1, Floor = -2, Start = -3, Finish = -4, NoNeigh = CELLS_NUMBER};

struct Labyrinth
{
	int mark[CELLS_NUMBER];
	size_t frontCells[CELLS_NUMBER];
	size_t frontCellsNumber = 1;
	size_t frontMark = 0;
	size_t aPosition;
	size_t bPosition;
};

size_t GetAbove(size_t cellPos)
{
	return (cellPos >= FIELD_SIDE) ? (cellPos - FIELD_SIDE) : NoNeigh;
}

size_t GetUnder(size_t cellPos)
{
	return (cellPos < CELLS_NUMBER - FIELD_SIDE) ? (cellPos + FIELD_SIDE) : NoNeigh;
}

size_t GetLeft(size_t cellPos)
{
	return (cellPos % FIELD_SIDE != 0) ? (cellPos - 1) : NoNeigh;
}

size_t GetRight(size_t cellPos)
{
	return ((cellPos + 1) % FIELD_SIDE != 0) ? (cellPos + 1) : NoNeigh;
}


bool IsWallSign(char ch) 
{
	return (ch == '#');
}

bool IsFloorSign(char ch)
{
	return (ch == ' ');
}

bool IsStartSign(char ch)
{
	return (ch == 'A');
}

bool IsFinishSign(char ch)
{
	return (ch == 'B');
}

void EncodeTheCell(size_t cellPos, char value)
{
	int n = 1;
}

int GetCellInitCode(char ch)
{
	if (IsFloorSign(ch))
	{
		return Floor;
	}
	else if (IsWallSign(ch))
	{
		return Wall;
	}
	else if (IsStartSign(ch))
	{
		return Start;
	}
	else if (IsFinishSign(ch))
	{
		return Finish;
	}
	else
	{
		throw
			std::invalid_argument("Unexpected symbol in labyrinth description");
	}
}


void LabyrinthInit(std::string const& labyrinthData, Labyrinth& labyrinth)
{
	int starts = 0;
	int finishes = 0;
	for (size_t n = 0; n < CELLS_NUMBER; ++n)
	{
		char ch = labyrinthData[n];
		labyrinth.mark[n] = GetCellInitCode(ch);
		if (IsStartSign(ch))
		{
			labyrinth.aPosition = n;
			starts++;
		}
		if (IsFinishSign(ch))
		{
			labyrinth.bPosition = n;
			finishes++;
		}
	}
	if ((starts != 1) || (finishes != 1))
	{
		throw
			std::invalid_argument("Not unique start or finish position");
	}
}


std::string LoadLabyrinthData(std::istream& labyrinthFile)  // 
{
	std::string labyrinthData;
	std::string row;
	size_t rowCounter = 0;
	
	while (getline(labyrinthFile, row) && (rowCounter < FIELD_SIDE)) 
	{
		size_t cellPosInRow = 0;
		for (char const& ch : row)
		{
			labyrinthData.push_back(ch);
			cellPosInRow++;
		}
		labyrinthData.append(FIELD_SIDE - cellPosInRow, ' ');
		rowCounter++;
	}
	for (size_t i = rowCounter; i < FIELD_SIDE; ++i)
	{
		labyrinthData.append(FIELD_SIDE, ' ');
	}
			
	return labyrinthData;
}

bool ShareWaveFromCell(Labyrinth& labyrinth, size_t cellPos)
{
	return true;
}

int main(int argc, char* argv[])
{
	std::string labyrinthFileName = std::string(argv[1]);
	std::ifstream labyrinthFile(labyrinthFileName); // попытка открыть файл
	if (!labyrinthFile)
	{
		std::cout << "File is not found!" << std::endl;
		return 1;
	}
		
	std::string labyrinthData = LoadLabyrinthData(labyrinthFile);
	std::cout << labyrinthData;

	Labyrinth labyrinth;
	LabyrinthInit(labyrinthData, labyrinth);

	return 0;	
}


