// lab014.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// crypt -- шифрование и дешифрование бинарного файла

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <string>
#include <ios>

enum Direction { Forward = 0, Backward };

struct Args
{
	Direction conversionDir;
	std::string inputFileName;
	std::string outputFileName;
	unsigned char key;
};

Direction GetDirection(char* directionString)
{
	std::string fw("crypt");
	std::string bw("decrypt");
	std::istringstream directionStream(directionString);
	std::string direction;
	directionStream >> direction;
	if (direction == fw) return Forward;
	if (direction == bw) return Backward;
	throw
		std::invalid_argument("Unknown conversion type used (must be \"crypt\" or \"decrypt\"");
}

unsigned char GetKey(char* keyString)
{
	std::istringstream keyStream(keyString);
	unsigned short longKey;
	keyStream >> longKey;
	
	if (keyStream.fail() || (longKey > 0xFF))
	{
		std::cout << longKey << std::endl;
		throw
			std::invalid_argument("key is to be number from 0 to 255");
	}

	return ((unsigned char) longKey);
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw
			std::invalid_argument("Invalid arguments count\n"
		        "Usage: crypt.exe <\"crypt\" | \"dectrypt\"> <input file name> <output file name> <key>");
	}
	Args args;
	args.conversionDir = GetDirection(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = GetKey(argv[4]);
	return args;
}

void PrintArgs(const Args& args)
{
	std::cout << "Args entered: " << (bool)args.conversionDir << " "
		<< args.inputFileName << " " << args.outputFileName << " "
		<< args.key << std::endl;
}

unsigned char ChiperByte(unsigned char dataByte) // здесь собственно шифрование
{
	return (dataByte % 2 == 0) ? 'a' : 'b';
}

void ConvertByteStreams(std::ifstream& input, std::ofstream& output)
{
	// Копируем содержимое входного файла в выходной
	char byte;
	unsigned char newByte;
	while (input.get(byte))
	{
		newByte = ChiperByte((unsigned char)byte);
		if (!output.put(newByte))
		{
			break;
		}
		
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		// Проверка правильности аргументов командной строки

		PrintArgs(args);

		// Открываем входной файл
		std::ifstream input;
		input.open(args.inputFileName);
		if (!input.is_open())
		{
			throw
				std::ifstream::failure("Failed to open input file");
		}

		// Открываем выходной файл
		std::ofstream output;
		output.open(args.outputFileName);
		if (!output.is_open())
		{
			std::cout << "Failed to open '" << args.outputFileName << "' for writing\n";
			return 1;
		}

		ConvertByteStreams(input, output);

		if (input.bad())
		{
			std::cout << "Failed to read data from input file\n";
			return 1;
		}

		if (!output.flush())
		{
			std::cout << "Failed to write data to output file\n";
			return 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}

/*
static unsigned short bits[8] = { 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };
static int offset[8] = { 4, 3, 3, 11, 11, 11, 11, 10 };

void PrintBinary(unsigned char number)
{
	std::cout << std::bitset<8>(number) << std::endl;
}

size_t GetOnesNumber(unsigned char byte)
{
	size_t onesNumber = 0;

	for (size_t i = 0; i < 8; ++i)
	{
		onesNumber += (byte & bits[i]) >> i;
	}
	return onesNumber;
}

unsigned char MixBits(unsigned char initial)
{
	unsigned char result = 0;
	unsigned short prepared = initial * 0x100;
	for (size_t i = 0; i < 8; ++i)
	{
		result |= (prepared & bits[i]) >> offset[i];
	}
	return result;
}

*/

