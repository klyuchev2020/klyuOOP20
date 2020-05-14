#include "CTokenSeries.h"

Token GetToken(std::istream& is)
{
	char ch;
	is >> ch;

	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '=':
		return Token(tKind::Symbol, std::string(1, ch));
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		is.unget();
		double val;
		is >> val;
		return Token(tKind::Number, val);
	}
	default:
		if (isalpha(ch))
		{
			std::string nameStr;
			nameStr += ch;
			while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
			{
				nameStr += ch;
			}
			is.unget();
			if (nameStr == "var" || nameStr == "let" || nameStr == "fn"
				|| nameStr == "print" || nameStr == "printvars" || nameStr == "printfns")
				return Token(tKind::Keyword, nameStr);
			return Token(tKind::Identor, nameStr);
		}
		throw std::invalid_argument("Bad token");
	}
}

void PrintTokenTest(const Token& t)
{
	if (t.kind == tKind::Number)
	{
		std::cout << "Token image:" << t.value;
	}
	else
	{
		std::cout << "Token image: " << t.name;
	}
	std::cout << "[ kind = " << int(t.kind) << ", value = " << t.value << ", name = " << t.name << std::endl;
}