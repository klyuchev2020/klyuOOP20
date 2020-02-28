// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <limits.h>
#include <iostream>

#define TESTING_MODE 1 // выпилить TESTING_MODE

enum errorType { NoError = 0, WrongSourceRadix, WrongDestiRadix, IllegalSymbol, OutOfRange };

std::string digSetUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int GetValueOfDigit(const char symbol, const std::string& digitsUpper, errorType& wasError)
{
	int digUppValue = (int) digitsUpper.find(toupper(symbol));
		
	if (digUppValue != std::string::npos)
	{
		return digUppValue;
	}
	else 
	{
		wasError = IllegalSymbol;
		return -1;
	}
}

char GetDigitOnValue(const int value, const int radix, const std::string& digitsUpper)
{
	return ((value >= 0) && (value < radix)) ? digitsUpper[value] : '#';
}


bool WillBeResultInRange(int currResult, bool isNegative, int digValue, int radix)
{
	const int bound = (isNegative) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	const int quotient = bound / radix;
	const int rest = bound - quotient * radix;

	return ((std::abs(currResult) < std::abs(quotient)) || ((currResult == std::abs(quotient)) && (digValue <= std::abs(rest))));
}

int StringToInt(const std::string& str, int radix, errorType& wasError)
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
		int digValue = GetValueOfDigit(symbol, digitsUpper, wasError); // проверяем, каково значение очередного символа
		if (wasError == IllegalSymbol)
		{
			break;
		}
		if (WillBeResultInRange(result, isNegative, digValue, radix))
		{
			result = result * radix + digValue;
		}
		else
		{
			wasError = OutOfRange; // переполнение
			break;
		}
		pos++;
	}

	return isNegative ? -result : result;
}

std::string IntToString(int n, int radix)
{
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string numberImage;
	int signum = (n >= 0) ? 1 : -1;
	int numberRest = n;

	while (numberRest != 0)
	{
		int currDigit = (signum * numberRest) % radix;
		numberRest = (numberRest - signum * currDigit) / radix;

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
		std::cout << "The program must have three arguments: 1) present radix; 2) new radix; 3) value to transform" 
			<< std::endl;
	}
	return (argcount < 4);
}

int WhatRadix(const char* radixString, errorType& wasError, const errorType whatError)
{
	const unsigned int radixValue = std::strtoul(radixString, nullptr, 10);
	const int radix = ((radixValue >= 2) && (radixValue <= 36)) ? radixValue : 0;

	if (!radix) wasError = whatError;

	return radix;
}

std::string getNewNumberRepresentation(const std::string& givenNumberString, const int sourceRadix,
	const int destiRadix, errorType& wasError)
{
	int numberToWrite = StringToInt(givenNumberString, sourceRadix, wasError);
	
	return (wasError == NoError) ? IntToString(numberToWrite, destiRadix) : "";
}

void PrintResults(const char* sourceRadixString, const char* destiRadixString,
	const char* givenNumberString, const std::string& resultNumberString, const errorType wasError)
{
	if (TESTING_MODE)
	{
		std::cout << resultNumberString.c_str() << std::endl;
		std::cout << wasError << std::endl;
	}
	else
	{
		std::cout << "Transform given integer value form one number system to other\n" << std::endl;
		std::cout << "Radices of value from 2 to 36. Digits from 10 to 35 are letters form A to Z\n" << std::endl;

		switch (wasError)
		{
		case WrongSourceRadix:
			std::cout << "Invalid source radix notation! Given " << sourceRadixString
				<< ", number between 2 and 36 expected" << std::endl;
			break;
		case WrongDestiRadix:
			std::cout << "Invalid destination radix notation! Given " << destiRadixString
				<< ", number between 2 and 36 expected" << std::endl;
			break;
		case IllegalSymbol:
			std::cout << "Illegal symbols in given number string!" << std::endl;
			break;
		case OutOfRange:
			std::cout << "Given number " << givenNumberString << " is out of integer range!" << std::endl;
			break;
		default:
			std::cout << givenNumberString << " in radix " << sourceRadixString << " will in radix "
				<< destiRadixString << " be " << resultNumberString.c_str() << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (NoEnoughArgs(argc)) return 1; // недостаточно аргументов

	errorType wasError = NoError;

	const int sourceRadix = WhatRadix(argv[1], wasError, WrongSourceRadix);
	const int destiRadix = WhatRadix(argv[2], wasError, WrongDestiRadix);
	const std::string givenNumberString = argv[3];

	std::string resultNumberString;

	if (wasError)  // неправильные основания систем счисления
	{
		PrintResults(argv[1], argv[2], argv[3], resultNumberString, wasError);
		return 2;
	}

	resultNumberString = getNewNumberRepresentation(givenNumberString, sourceRadix, destiRadix, wasError);

	if (wasError)  // невозможно корректно обработать данную строку, изображающую число
	{
		PrintResults(argv[1], argv[2], argv[3], resultNumberString, wasError);
		return 3;
	}

	PrintResults(argv[1], argv[2], argv[3], resultNumberString, wasError);
	return 0;
}

