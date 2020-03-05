#pragma once

typedef std::function<bool(const std::string&, const std::string&)> CompareFunction;

struct Args
{
	std::string sourceFileName;
	std::string needle;
};

bool PrintNumbersOfLinesWithText(std::istream&, const std::string&, CompareFunction const&);
bool SubstringInStringIsFound(const std::string&, const std::string&);
std::optional<Args> ParseArgs(int, char**);