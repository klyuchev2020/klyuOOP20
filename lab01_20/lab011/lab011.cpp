// lab011.cpp: определяет точку входа для консольного приложения.
// Отмечает номера строк в данном файле, включающих заданную подстроку

#include "findstring.h"

int main(int argc, char* argv[])
{
	std::cout << "Program is to find inclusions of the given string in given file"
		<< std::endl;

	auto args = ParseCommandLine(argc, argv);
	if (!args)
	{
		return 1; // недостаточно аргументов
	}

	// TODO: Выделить открытие и поиск в отдельную функцию
	std::string sourceFileName = args->sourceFileName;
	std::ifstream sourceFile(sourceFileName); // попытка открыть файл
	if (!sourceFile)
	{
		std::cout << "File is not found!" << std::endl;
		return 1;
	}
	
	std::string needle = args->needle; // строка, которую ищем

	if (PrintNumbersOfLinesWithText(sourceFile, needle, SubstringInStringIsFound))
	{
		std::cout << "These are numbers of strings in file " << sourceFileName <<
			", there the string \"" << needle << "\" is appear." << std::endl;
	}
	else
	{
		std::cout << "There are no appearences of string " << needle <<
			" in file " << sourceFileName << std::endl;
		return 1;
	}

	return 0;
}

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "The program must have two arguments:"
			"1) file name; 2) string to find" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.sourceFileName = argv[1];
	args.needle = argv[2];
	return args;
}

bool PrintNumbersOfLinesWithText(std::istream& sourceFile, const std::string& needle, CompareFunction const& FindNeedle) // выводит номера строк, в которых встретился образец
{
	bool found = false;
	size_t stringNumber = 1;
	std::string heystack; // очередная строка данного файла

	while (getline(sourceFile, heystack)) // пока не достигнут конец файла, читаем очередную его строку в currString
	{
		if (FindNeedle(needle, heystack))
		{
			std::cout << stringNumber << std::endl;
			found = true;
		}
		stringNumber++;
	}

	return found; // true, если текст встретился
}

bool SubstringInStringIsFound(std::string const& needle, std::string const& heystack)
{
	std::string::size_type positionToFind = heystack.find(needle);
	return (positionToFind != std::string::npos);
}


