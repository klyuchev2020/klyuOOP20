#pragma once

#include "stdafx.h"

static double undefined = std::nan("");

enum class Tkind
{
	Symbol = 0, // одиночный символ
    Number,     // число double
	Identor,    // идентификатор
	Keyword,    // ключевое слово калькулятора
	End,        // конец данных
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

	Token(Tkind k, const std::string& n)
		: kind(k)
		, value(undefined)
		, name(n)
	{
	}

	Token(Tkind k, double val, const std::string& n)
		: kind(k)
		, value(val)
		, name(n)
	{
	}
};


void PrintTokenTest(const Token& t);

class CTStream
{
public:
	CTStream(std::istream& is = std::cin);

	Token GetToken();
	void PutBack(Token tok);
	void Skip();
	bool IsEmpty() const;

private:
	std::istream& m_tstream;
	Token m_buffer;
	bool m_buffull;
};
