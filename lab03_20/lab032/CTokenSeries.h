#pragma once

#include "stdafx.h"

enum class tKind
{
	Symbol = 0,
    Number,
	Identor,
	Keyword,
};

struct Token
{
	tKind kind;
	double value;
	std::string name;

	Token()
		: kind(tKind::Number)
		, value(0.0)
		, name("")
	{

	}
	
	Token(tKind k)
		: kind(k)
		, value(std::nan(""))
		, name("")
	{
	}

	Token(tKind k, double val)
		: kind(k)
		, value(val)
		, name("")
	{
	}

	Token(tKind k, std::string n)
		: kind(k)
		, value(std::nan(""))
		, name(n)
	{
	}
};

Token GetToken(std::istream& is);
void PrintTokenTest(const Token& t);

class CTokenSeries
{
};
