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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

constexpr size_t FIELD_SIDE = 100; // сторона квадратного поля, в котором размещен лабиринт

struct LabyrinthDyn
{
	size_t width;
	size_t height;
	int* mark;
	bool* path;
	size_t* frontCells;
	size_t frontCellsNumber;
	int frontMark;
	size_t aPosition;
	size_t bPosition;
};

enum Cell
{
	Wall = -1,
	Floor = -2,
	Start = -3,
	Finish = -4,
	NoNeigh = FIELD_SIDE * FIELD_SIDE
};

size_t GetAbove(size_t cellPos, size_t width)
{
	return (cellPos >= width) ? (cellPos - width) : NoNeigh;
}

size_t GetUnder(size_t cellPos, size_t width, size_t height)
{
	return (cellPos < width * (height - 1)) ? (cellPos + width) : NoNeigh;
}

size_t GetLeft(size_t cellPos, size_t width)
{
	return (cellPos % width != 0) ? (cellPos - 1) : NoNeigh;
}

size_t GetRight(size_t cellPos, size_t width, size_t height)
{
	return ((cellPos + 1) % width != 0) ? (cellPos + 1) : NoNeigh;
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
		throw std::invalid_argument("Unexpected symbol in labyrinth description");
	}
}

LabyrinthDyn* AllocLabyrinth(size_t width, size_t height)
{
	LabyrinthDyn* newLabyrinthDyn = new LabyrinthDyn;
	int* markptr = new int[width * height];
	bool* pathptr = new bool[width * height];
	size_t* frontCellsptr = new size_t[width * height];

	newLabyrinthDyn->mark = markptr;
	newLabyrinthDyn->path = pathptr;
	newLabyrinthDyn->frontCells = frontCellsptr;

	return newLabyrinthDyn;
}

void FreeLabyrinthMemory(LabyrinthDyn* labyrinth)
{
	delete[] labyrinth->mark;
	delete[] labyrinth->path;
	delete[] labyrinth->frontCells;
	delete labyrinth;
}

void SetLabyrinthInitials(LabyrinthDyn* labyrinth, const std::string& labyrinthData)
{
	int starts = 0;
	int finishes = 0;
	size_t labBodySize = labyrinth->width * labyrinth->height;
	for (size_t n = 0; n < labBodySize; ++n)
	{
		labyrinth->path[n] = false;
		char ch = labyrinthData[n];
		labyrinth->mark[n] = GetCellInitCode(ch);

		if (IsStartSign(ch))
		{
			labyrinth->aPosition = n;
			starts++;
		}
		if (IsFinishSign(ch))
		{
			labyrinth->bPosition = n;
			finishes++;
		}
	}

	if ((starts != 1) || (finishes != 1))
	{
		throw std::invalid_argument("Not unique start or finish position.\n"
			"Labyrinth must contain exactly one \'A\' and exactly one \'B\'. Try again");
	}
	labyrinth->frontCellsNumber = 1;
	labyrinth->frontCells[0] = labyrinth->aPosition;
	labyrinth->frontMark = 0;
}

void SetLabyrinthSizes(LabyrinthDyn* labyrinth, size_t width, size_t height)
{
	labyrinth->width = width;
	labyrinth->height = height;
}

std::string LoadLabyrinthData(std::istream& labyrinthFile, size_t& width, size_t& height) //
{
	std::string labyrinthData;
	std::string rowSet[FIELD_SIDE];
	size_t maxRowLength = 0;
	size_t rowCounter = 0;

	while (getline(labyrinthFile, rowSet[rowCounter]) && (rowCounter < FIELD_SIDE))
	{
		maxRowLength = (rowSet[rowCounter].size() > maxRowLength)
			? rowSet[rowCounter].size()
			: maxRowLength;
		rowCounter++;
	}
	if ((maxRowLength > FIELD_SIDE) || (rowCounter == FIELD_SIDE))
	{
		throw std::invalid_argument("Labyrinth sizes overflow!");
	}
	else
	{
		for (size_t i = 0; i < rowCounter; ++i)
		{
			labyrinthData += rowSet[i];
			labyrinthData.append(maxRowLength - rowSet[i].size(), ' ');
		}
		width = maxRowLength;
		height = rowCounter;
	}

	return labyrinthData;
}

Cell ShareWaveFromFrontCell(LabyrinthDyn* labyrinth, size_t frontCellPos)
{
	Cell cell = NoNeigh;
	int currMark = labyrinth->frontMark;

	size_t neighs[4] = {
		GetAbove(frontCellPos, labyrinth->width),
		GetRight(frontCellPos, labyrinth->width, labyrinth->height),
		GetUnder(frontCellPos, labyrinth->width, labyrinth->height),
		GetLeft(frontCellPos, labyrinth->width)
	};
	for (size_t const& nei : neighs)
	{
		if (nei != NoNeigh)
		{
			if (labyrinth->mark[nei] == Floor || labyrinth->mark[nei] == currMark + 1)
			{
				labyrinth->mark[nei] = currMark + 1;
				cell = Floor;
			}
			if (labyrinth->mark[nei] == Finish)
			{
				labyrinth->mark[nei] = currMark + 1;
				return Finish;
			}
		}
	}
	return cell;
}

Cell PropagateNextMark(LabyrinthDyn* labyrinth)
{
	Cell result = NoNeigh;
	for (size_t i = 0; i < labyrinth->frontCellsNumber; ++i)
	{
		Cell nextCellResult = ShareWaveFromFrontCell(labyrinth, labyrinth->frontCells[i]);
		if (nextCellResult == Floor)
		{
			result = Floor;
		}

		if (Finish == nextCellResult)
		{
			return Finish;
		}
	}

	return result;
}

void SetNewFrontCells(LabyrinthDyn* labyrinth)
{
	int newFrontMark = ++labyrinth->frontMark;
	size_t newFrontCellsNumber = 0;
	size_t cellsNumber = labyrinth->width * labyrinth->height;
	for (size_t i = 0; i < cellsNumber; ++i)
	{
		if (newFrontMark == labyrinth->mark[i])
		{
			labyrinth->frontCells[newFrontCellsNumber] = i;
			newFrontCellsNumber++;
		}
	}
	labyrinth->frontCellsNumber = newFrontCellsNumber;
}

Cell RunForwardWave(LabyrinthDyn* labyrinth)
{
	Cell found = Floor;

	while ((found != Finish) && (found != NoNeigh))
	{
		found = PropagateNextMark(labyrinth);
		SetNewFrontCells(labyrinth);
	}

	return found;
}

size_t StepВackward(const LabyrinthDyn* labyrinth, size_t position)
{
	size_t stepToStart = position;
	int currMark = labyrinth->mark[position];
	size_t neighs[4] = {
		GetAbove(position, labyrinth->width),
		GetRight(position, labyrinth->width, labyrinth->height),
		GetUnder(position, labyrinth->width, labyrinth->height),
		GetLeft(position, labyrinth->width)
	};

	for (size_t const& nei : neighs)
	{
		if ((nei != NoNeigh) && (currMark == labyrinth->mark[nei] + 1))
		{
			return nei;
		}
	}
	return position;
}

bool FillLabyrinthPath(LabyrinthDyn* labyrinth)
{
	size_t len = 0;
	size_t prev = labyrinth->bPosition;
	labyrinth->path[prev] = true;
	size_t next = StepВackward(labyrinth, prev);
	while ((next != prev) && (next != labyrinth->aPosition))
	{
		prev = next;
		next = StepВackward(labyrinth, prev);
		labyrinth->path[prev] = true;
	}
	return next == labyrinth->aPosition;
}

void PrintLabyrinthOut(const LabyrinthDyn* labyrinth)
{
	for (size_t i = 0; i < labyrinth->height; ++i)
	{
		for (size_t j = 0; j < labyrinth->width; ++j)
		{
			size_t pos = (labyrinth->width) * i + j;
			char visual = ' ';
			if (labyrinth->mark[pos] == Wall)
			{
				visual = '#';
			}
			if (labyrinth->path[pos])
			{
				visual = '.';
			}
			if (pos == labyrinth->aPosition)
			{
				visual = 'A';
			}
			if (pos == labyrinth->bPosition)
			{
				visual = 'B';
			}

			std::cout << visual;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PrintLabyrinthDebug(const LabyrinthDyn* labyrinth)
{
	for (size_t i = 0; i < labyrinth->height; ++i)
	{
		for (size_t j = 0; j < labyrinth->width; ++j)
		{
			int curr = labyrinth->mark[(labyrinth->width) * i + j];
			char visual = ' ';
			if (curr == Wall)
			{
				visual = '#';
			}
			else if (curr == Floor)
			{
				visual = ' ';
			}
			else if (curr == Start)
			{
				visual = 'A';
			}
			else if (curr == Finish)
			{
				visual = 'B';
			}
			else
			{
				visual = curr - '0';
			}
			std::cout << visual;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::string ParseCommandLine(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("The program must have argument -- labyrinth data file name");
	}
	return std::string(argv[1]);
}

int main(int argc, char* argv[])
{
	try
	{
		std::ifstream labyrinthFile(ParseCommandLine(argc, argv)); // попытка открыть файл
		if (!labyrinthFile)
		{
			std::cout << "File is not found!" << std::endl;
			return 1;
		}

		size_t width;
		size_t height;
		std::string labyrinthData = LoadLabyrinthData(labyrinthFile, width, height);

		LabyrinthDyn* labyrinth = AllocLabyrinth(width, height);
		SetLabyrinthSizes(labyrinth, width, height);
		SetLabyrinthInitials(labyrinth, labyrinthData);

		if (Finish == RunForwardWave(labyrinth))
		{
			FillLabyrinthPath(labyrinth);
			PrintLabyrinthOut(labyrinth);
		}
		else
		{
			PrintLabyrinthOut(labyrinth);
			throw std::range_error("Path from A to B not exists in this labyrinth");
		}

		FreeLabyrinthMemory(labyrinth);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Wrong data: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::range_error& e)
	{
		std::cout << e.what() << std::endl;
		return 2;
	}
	catch (...)
	{
		std::cout << "Unknown exception" << std::endl;
		return 3;
	}

	return 0;
}
