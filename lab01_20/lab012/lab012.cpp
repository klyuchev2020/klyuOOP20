// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <limits.h>
#include <iostream>

struct Args
{
	int sourceRadix;
	int destinationRadix;
	std::string sourceNotation;
};

std::string digitsUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int GetValueOfDigit(const char symbol, const int radix)
{
	int digUppValue = (int) digitsUpper.find(toupper(symbol));
		
	if ((digUppValue != std::string::npos) && (digUppValue < radix))
	{
		return digUppValue;
	}
	else 
	{
		throw
			std::invalid_argument("Illegal symbols in given number string!");
	}
}

char GetDigitOnValue(const int value, const int radix)
{
	if ((value < 0) || (value >= radix))
	{
		throw
			std::out_of_range("Not a digit occured!");
	}
	return digitsUpper[value];
}


bool IsExpectedResultInRange(int currResult, bool isNumberNegative, int nextDigitValue, int radix)
{
	const int boundOfRange = (isNumberNegative) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	const int quotient = boundOfRange / radix;
	if (std::abs(currResult) < std::abs(quotient))
	{
		return true;
	}
	const int restToBound = boundOfRange - quotient * radix;
    return ((currResult == std::abs(quotient)) && (nextDigitValue <= std::abs(restToBound)));
}

int StringToInt(const std::string& str, int radix)
{
	int result = 0;
	bool isNumberNegative = false;

	size_t pos = 0;

	if (str[0] == '-')
	{
		isNumberNegative = true;
		pos++;
	}
	
	while (pos < str.length())
	{
		char symbol = str[pos];
		int digValue = GetValueOfDigit(symbol, radix); // проверяем, каково значение очередного символа
		
		if (IsExpectedResultInRange(result, isNumberNegative, digValue, radix))
		{
			result = result * radix + digValue;
		}
		else
		{
			std::string message = std::string("Given number ") + str + std::string(" is out of integer range!");
			throw
				std::out_of_range(message); // переполнение
		}
		pos++;
	}

	return isNumberNegative ? -result : result;
}

bool RadixValueInRange(int radix)
{
	return (radix >= 2) && (radix <= 36);
}

std::string IntToString(int n, int radix)
{
	if (!RadixValueInRange(radix))
	{
		throw
		    std::out_of_range("Wrong radix value");
	}
	
	std::string numberImage;
	int signum = (n >= 0) ? 1 : -1;
	int numberRest = n;

	while (numberRest != 0)
	{
		int currDigit = std::abs(numberRest % radix);
		numberRest = (numberRest < 0) ? std::abs(numberRest + currDigit) / radix : std::abs(numberRest - currDigit) / radix;
		
		char nextSymbol = GetDigitOnValue(currDigit, radix);
		numberImage.push_back(nextSymbol);
	}
	if (n == 0)
	{
		numberImage.push_back('0');
	}
	if (n < 0)
	{
		numberImage.push_back('-');
	}
	
	std::reverse(numberImage.begin(), numberImage.end());

	return numberImage;
}


int GetRadix(const char* radixString, const char* whichRadix)
{
	const unsigned int radixValue = std::strtoul(radixString, nullptr, 10);
	if (RadixValueInRange(radixValue))
	{
		return radixValue;
	}
	else
	{
		std::string message = std::string("Invalid ") + std::string(whichRadix) + std::string(" radix notation! Given ") +
			std::string(radixString) + std::string(", number between 2 and 36 expected");
		throw
			std::invalid_argument(message);
	}
}

std::string ConvertNumericNotation(const std::string& sourceNotation, const int sourceRadix,
	const int destinationRadix)
{
	int givenNumber = StringToInt(sourceNotation, sourceRadix);
	
	return IntToString(givenNumber, destinationRadix);
}

Args ParseCommandLine(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw
			std::invalid_argument("The program must have three arguments: 1) pr"
				"esent radix; 2) new radix; 3) value to transform");
	}
	Args args;
	args.sourceRadix = GetRadix(argv[1], "source"); 
	args.destinationRadix = GetRadix(argv[2], "destination"); 
	args.sourceNotation = std::string(argv[3]); 
	
	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseCommandLine(argc, argv);

		std::string resultNumberString = ConvertNumericNotation(args.sourceNotation, args.sourceRadix, args.destinationRadix);
		std::cout << resultNumberString.c_str() << std::endl;

		return 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Wrong data: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Number is out of range: " << e.what() << std::endl;
		return 2;
	}
	catch (...)
	{
		std::cout << "Unexpected exception!" << std::endl;
		return 3;
	}
}

