#pragma once

#include "stdafx.h"

static double undefined = std::nan("");

enum class Tkind
{
	Symbol = 0, // одиночный символ
    Number,     // число double
	Identor,    // идентификатор
	Keyword,    // ключевое слово калькулятора
};

struct Token
{
	Tkind kind;
	double value;
	std::string name;

	Token()
		: kind(Tkind::Number)
		, value(0.0)
		, name("")
	{

	}
	
	Token(Tkind k)
		: kind(k)
		, value(undefined)
		, name("")
	{
	}

	Token(Tkind k, double val)
		: kind(k)
		, value(val)
		, name("")
	{
	}

	Token(Tkind k, std::string n)
		: kind(k)
		, value(undefined)
		, name(n)
	{
	}
};

Token GetToken(std::istream& is);
void PrintTokenTest(const Token& t);

class CTokenSeries
{
};
