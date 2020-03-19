// lab014.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// crypt -- шифрование и дешифрование бинарного файла

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <limits>
#include <bitset>

constexpr size_t BYTE_SIZE = 256;
enum Direction { Chipering = 0, Dechipering };

static int singlebitMask[8] = { 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };
static int chiperMixbitsOffset[8] = { 6, 6, 6, 5, 5, 13, 13, 10 };
static int dechiperMixbitsOffset[8] = { 3, 3, 10, 10, 10, 6, 11, 11 };

struct Args
{
	Direction conversionDir;
	std::string inputFileName;
	std::string outputFileName;
	char key;
};

Direction GetDirection(char* directionString)
{
	std::string fw("crypt");
	std::string bw("decrypt");
	std::istringstream directionStream(directionString);
	std::string direction;
	directionStream >> direction;
	if (direction == fw) return Chipering;
	if (direction == bw) return Dechipering;
	throw
		std::invalid_argument("Unknown conversion type used (must be \"crypt\" or \"decrypt\")");
}

char GetKey(char* keyString)
{
	std::istringstream keyStream(keyString);
	short longKey;
	keyStream >> longKey;

	if (keyStream.fail() || (longKey >= BYTE_SIZE) || (longKey < 0))
	{
		throw
			std::invalid_argument("Last parameter <key> is to be number from 0 to 255");
	}
	if (longKey < 128)
	{
		return (char)longKey;
	}
	else
	{
		return (char)(longKey + 2 * std::numeric_limits<char>::min());
	}
}

Args ParseCommandLine(int argc, char* argv[])
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

char MixBits(char initial, Direction direction)
{
	char chiperMixedBits = 0;
	char dechiperMixedBits = 0;
	int prepared = initial * 0x100;
	
	for (size_t i = 0; i < 8; ++i)
	{
		chiperMixedBits |= (prepared & singlebitMask[i]) >> chiperMixbitsOffset[i];
		dechiperMixedBits |= (prepared & singlebitMask[i]) >> dechiperMixbitsOffset[i];
	}
	
	return (direction == Chipering) ? chiperMixedBits : dechiperMixedBits;
}

static char chiperMixedBytes[BYTE_SIZE];
static char dechiperMixedBytes[BYTE_SIZE];
static char chiperConversionTable[BYTE_SIZE];
static char dechiperConversionTable[BYTE_SIZE];

void SetMixedBytes()
{
	char ch = std::numeric_limits<char>::min();
	for (size_t i = 0; i < BYTE_SIZE; ++i)
	{
		chiperMixedBytes[i] = MixBits(ch, Chipering);
		dechiperMixedBytes[i] = MixBits(ch, Dechipering);
		ch++;
	}
}

char ChiperByteForward(char dataByte, char key) // здесь собственно шифрование
{
	return chiperMixedBytes[(dataByte ^ key) - (char)std::numeric_limits<char>::min()];
}

char ChiperByteBackward(char dataByte, char key) // здесь собственно шифрование
{
	return dechiperMixedBytes[dataByte - std::numeric_limits<char>::min()] ^ key;
}

void FillConversionTables(char key)
{
	SetMixedBytes();
	char ch = std::numeric_limits<char>::min();
	for (size_t i = 0; i < BYTE_SIZE; ++i)
	{
		chiperConversionTable[i] = ChiperByteForward(ch, key);
		dechiperConversionTable[i] = ChiperByteBackward(ch, key);
		ch++;
	}
}

void ChiperByteStream(std::istream& input, std::ostream& output, char key)
{
	char dataByte;
	char newByte;
	while (input.get(dataByte))
	{
		newByte = chiperConversionTable[dataByte - std::numeric_limits<char>::min()];
		if (!output.put(newByte))
		{
			break;
		}
	}
}

void DechiperByteStream(std::istream& input, std::ostream& output, char key)
{
	char dataByte;
	char newByte;
	while (input.get(dataByte))
	{
		newByte = dechiperConversionTable[dataByte - std::numeric_limits<char>::min()];
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
		Args args = ParseCommandLine(argc, argv);
		
		std::ifstream input;
		input.open(args.inputFileName, std::ios::binary);
		if (!input.is_open())
		{
			throw
				std::ifstream::failure("Failed to open input file");
		}

		std::ofstream output;
		output.open(args.outputFileName, std::ios::binary);
		if (!output.is_open())
		{
			throw
				std::ofstream::failure("Failed to open output file");
		}
					
		FillConversionTables(args.key);
				
		if (args.conversionDir == Chipering)
		{
			ChiperByteStream(input, output, args.key);
		}
		else
		{
			DechiperByteStream(input, output, args.key);
		}
					
		if (input.bad())
		{
			throw
				std::ifstream::failure("Failed to read input data");
			
		}

		if (!output.flush())
		{
			throw
				std::ofstream::failure("Failed to write converted data");
		}
		return 0;
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "Wrong data in command line. " << e.what() << std::endl;
		return 1;
	}
	catch (std::ios_base::failure const& e)
	{
		std::cout << "File operation error. " << e.what() << std::endl;
		return 2;
	}
	catch (...)
	{
		std::cout << "Unknown exception occured!" << std::endl;
		return 3;
	}
	
}



