// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <limits.h>
#include <iostream>


std::string digSetUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int GetValueOfDigit(const char symbol, const std::string& digitsUpper)
{
	int digUppValue = (int) digitsUpper.find(toupper(symbol));
		
	if (digUppValue != std::string::npos)
	{
		return digUppValue;
	}
	else 
	{
		throw
			std::invalid_argument("Illegal symbols in given number string!");
	}
}

char GetDigitOnValue(const int value, const int radix, const std::string& digitsUpper)
{
	return ((value >= 0) && (value < radix)) ? digitsUpper[value] : '#';
}


bool IsExpectedResultInRange(int currResult, bool isNegative, int digValue, int radix)
{
	const int bound = (isNegative) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	const int quotient = bound / radix;
	const int rest = bound - quotient * radix;

	return ((std::abs(currResult) < std::abs(quotient)) || ((currResult == std::abs(quotient)) && (digValue <= std::abs(rest))));
}

int StringToInt(const std::string& str, int radix)
{
	std::string digitsUpper = digSetUpper.substr(0, radix);
	
	int result = 0;
	bool isNegative = false;

	size_t pos = 0;

	if (str[0] == '-')
	{
		isNegative = true;
		pos++;
	}
	
	while (pos < str.length())
	{
		char symbol = str[pos];
		int digValue = GetValueOfDigit(symbol, digitsUpper); // проверяем, каково значение очередного символа
		
		if (IsExpectedResultInRange(result, isNegative, digValue, radix))
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

	return isNegative ? -result : result;
}

bool RadixWell(int radix)
{
	return (radix >= 2) && (radix <= 36);
}

std::string IntToString(int n, int radix)
{
	if (!RadixWell(radix))
	{
		throw
		    std::out_of_range("Wrong radix value");
	}
	
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string numberImage;
	int signum = (n >= 0) ? 1 : -1;
	int numberRest = n;

	while (numberRest != 0)
	{
		int currDigit = std::abs(numberRest % radix);
		numberRest = (numberRest < 0) ? std::abs(numberRest + currDigit) / radix : std::abs(numberRest - currDigit) / radix;
		
		char nextSymbol = GetDigitOnValue(currDigit, radix, digitsUpper);
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


bool NoEnoughArgs(const int argcount)
{
	if (argcount < 4)
	{
		throw
			std::invalid_argument("The program must have three arguments: 1) pr"
				"esent radix; 2) new radix; 3) value to transform");
	}
	return (argcount < 4);
}

int GetRadix(const char* radixString, const char* whichRadix)
{
	const unsigned int radixValue = std::strtoul(radixString, nullptr, 10);
	if (RadixWell(radixValue))
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

std::string GetNewNumberRepresentation(const std::string& givenNumberString, const int sourceRadix,
	const int destiRadix)
{
	int numberToWrite = StringToInt(givenNumberString, sourceRadix);
	
	return IntToString(numberToWrite, destiRadix);
}

int main(int argc, char* argv[])
{
	try
	{
		if (NoEnoughArgs(argc)) return 1; // недостаточно аргументов
				
		const int sourceRadix = GetRadix(argv[1], "source");
		const int destiRadix = GetRadix(argv[2], "destination");
		const std::string givenNumberString(argv[3]);

		std::string resultNumberString = GetNewNumberRepresentation(givenNumberString, sourceRadix, destiRadix);

		std::cout << resultNumberString.c_str() << std::endl;

		return 0;
		
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Wrong data: " << e.what() << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Number is out of range: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected exception!" << std::endl;
	}
}

