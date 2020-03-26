#include "stdafx.h"
#include "../lab022/HTMLdecode.h"

char GetSubstitutionOnPosition(const std::string& codeString, size_t& pos)
{ // ищет подстановку на место очередного символа
	static const std::vector<std::pair<std::string, char>> substSymbol = {
		{ "&quot;", '\"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' }
	};
	for (auto const& pair : substSymbol)
	{
		if (codeString.find(pair.first, pos) == pos)
		{
			pos += pair.first.size();
			return pair.second;
		}
	}
	return codeString.at(pos++);
}

std::string Decode(const std::string& stringToDecode)
{ // декодирует строку
	std::string decodedString;
	decodedString.reserve(stringToDecode.length());
	size_t currPos = 0;

	while (currPos < stringToDecode.length())
	{
		size_t restBegin = currPos;
		currPos = stringToDecode.find_first_of('&', restBegin);
		decodedString.append(stringToDecode, restBegin, currPos - restBegin);
		if (currPos != std::string::npos)
		{
			decodedString += GetSubstitutionOnPosition(stringToDecode, currPos);
		}
	}
	return decodedString;
}
