#include "stdafx.h"
#include "../lab022/HTMLdecode.h"


static std::map<std::string, char> substSymbol = { { "&quot;", '\"' },
{ "&apos;", '\'' },
{ "&lt;"  , '<' },
{ "&gt;"  , '>' },
{ "&amp;" , '&' } };


char SubstCode(const std::string& codeString, size_t& pos)
{ // ищет подстановку на место амперсанда
	bool found = false;
	char substitution;
	for (auto it = substSymbol.begin(); it != substSymbol.end(); ++it)
	{
		if (codeString.compare(pos, (it->first).size(), it->first) == 0)
		{
			found = true;
			substitution = it->second;
			pos += (it->first).size();
			break;
		}
	}
	if (!found)
	{
		substitution = '&';
		pos++;
	}
	return substitution;
}


std::string Decode(const std::string& codeString)
{ // декодирует строку	
	std::string decodedString;
	size_t currPos = 0;
	
	while (currPos != std::string::npos)
	{
		size_t restBegin = currPos;
		currPos = codeString.find_first_of('&', restBegin);
		if (currPos != std::string::npos)
		{
			decodedString = (currPos > restBegin) ? decodedString + codeString.substr(restBegin, currPos - restBegin) : decodedString;
			decodedString += SubstCode(codeString, currPos);
		}
		else
		{
			decodedString += codeString.substr(restBegin);
		}
	}
	return decodedString;
}

