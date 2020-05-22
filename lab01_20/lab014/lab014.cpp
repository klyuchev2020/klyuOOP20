// lab014.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// crypt -- шифрование и дешифрование бинарного файла

#include <bitset>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

constexpr size_t BYTE_SIZE = 256;
enum class Direction
{
	Encrypt = 0,
	Decrypt
};

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

Direction GetDirection(const char* directionString)
{
	std::string fw("crypt");
	std::string bw("decrypt");

	if (directionString == fw)
		return Direction::Encrypt;
	if (directionString == bw)
		return Direction::Decrypt;
	throw std::invalid_argument("Unknown conversion type used (must be \"crypt\" or \"decrypt\")");
}

char GetKey(const char* keyString)
{
	short longKey = std::stoi(keyString);

	if ((longKey >= BYTE_SIZE) || (longKey < 0))
	{
		throw std::invalid_argument("Parameter <key> is to be number from 0 to 255");
	}

	return static_cast<char>(longKey);
}

Args ParseCommandLine(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Invalid arguments count\n"
									"Usage: crypt.exe <\"crypt\" | \"dectrypt\"> <input file name> <output file name> <key>");
	}
	Args args;
	args.conversionDir = GetDirection(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = GetKey(argv[4]);
	return args;
}

char MixBits(char initial, const int* offsetsTable)
{
	char mixedBits = 0;
	int prepared = initial * 0x100;

	for (size_t i = 0; i < 8; ++i)
	{
		mixedBits |= (prepared & singlebitMask[i]) >> offsetsTable[i];
	}

	return mixedBits;
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
		chiperMixedBytes[i] = MixBits(ch, chiperMixbitsOffset);
		dechiperMixedBytes[i] = MixBits(ch, dechiperMixbitsOffset);
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

void ConvertByteStream(std::istream& input, std::ostream& output, char key, const char* conversionTable)
{
	char dataByte;
	char newByte;
	while (input.get(dataByte))
	{
		newByte = conversionTable[dataByte - std::numeric_limits<char>::min()];
		if (!output.put(newByte))
		{
			break;
		}
	}
}

void AssignFstreams(std::ifstream& is, std::ofstream& os, const Args& args)
{
	is.open(args.inputFileName, std::ios::binary);
	if (!is.is_open())
	{
		throw std::ifstream::failure("Failed to open input file");
	}

	os.open(args.outputFileName, std::ios::binary);
	if (!os.is_open())
	{
		throw std::ofstream::failure("Failed to open output file");
	}
}

void Convert(std::ifstream& is, std::ofstream& os, const Args& args)
{
	FillConversionTables(args.key);

	const char* table = (args.conversionDir == Direction::Encrypt) ? chiperConversionTable : dechiperConversionTable;
	ConvertByteStream(is, os, args.key, table);
}

void CheckFinalFstreams(std::ifstream& is, std::ofstream& os)
{
	if (is.bad())
	{
		throw std::ifstream::failure("Failed to read input data");
	}

	if (!os.flush())
	{
		throw std::ofstream::failure("Failed to write converted data");
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseCommandLine(argc, argv);

		std::ifstream input;
		std::ofstream output;
		AssignFstreams(input, output, args);
		Convert(input, output, args);
		CheckFinalFstreams(input, output);

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
