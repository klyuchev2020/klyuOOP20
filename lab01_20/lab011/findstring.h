#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <optional>
#include <functional>

typedef std::function<bool(const std::string&, const std::string&)> CompareFunction;

struct Args
{
	std::string sourceFileName;
	std::string needle;
};

bool PrintNumbersOfLinesWithText(std::istream&, const std::string&, CompareFunction const&);
bool SubstringInStringIsFound(const std::string&, const std::string&);
std::optional<Args> ParseCommandLine(int, char* []);