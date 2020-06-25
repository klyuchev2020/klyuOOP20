#include "CTStream.h"
#include "CError.h"

CTStream::CTStream(std::istream& is)
	: m_tstream(is)
	, m_buffer(Token(Tkind::Symbol, std::string(1, '~')))
	, m_buffull(false)
{
}

void CTStream::PutBack(Token tok)
{
	if (m_buffull)
	{
		std::cout << "No place to put token back" << std::endl;
		return;
	}
	m_buffer = tok;
	m_buffull = true;
}

Token CTStream::GetToken()
{
	if (m_buffull)
	{
		m_buffull = false;
		return m_buffer;
	}

	char ch;
	if (!(m_tstream >> ch))
	{
		return Token(Tkind::End); 
	}
	
	switch (ch)
	{
	case '+':
	case '*':
	case '/':
	case '=':
		return Token(Tkind::Symbol, std::string(1, ch));
	case '-':
	{
		double val;
		if (m_tstream >> val)
		{
			return Token(Tkind::Number, -val);
		}
		else
		{
			m_tstream.clear();
			return Token(Tkind::Symbol, std::string(1, '-'));
		}
	}
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
		m_tstream.unget();
		double val;
		m_tstream >> val;
		if (!std::cin.fail())
		{
			return Token(Tkind::Number, val);
		}
	}
	default:
		if (isalpha(ch))
		{
			std::string nameStr;
			nameStr += ch;
			while (m_tstream.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
			{
				nameStr += ch;
			}
			m_tstream.unget();
			
			if (nameStr == "var" || nameStr == "let" || nameStr == "fn"
				|| nameStr == "print" || nameStr == "printvars" || nameStr == "printfns")
				return Token(Tkind::Keyword, nameStr);
			return Token(Tkind::Identor, nameStr);
		}
		
		throw CError::BadToken("Bad token", 10);
	}
}

std::string GetTokenType(const Token& t)
{
	switch (t.kind)
	{
	case Tkind::Symbol:
		return "Symbol";
	case Tkind::Number:
		return "Number";
	case Tkind::Identor:
		return "Identor";
	case Tkind::Keyword:
		return "Keyword";
	default:
		return "Unknown token";
	}
}

void CTStream::Skip()
{
	m_tstream.clear();
	char ch;
	while (m_tstream.get(ch))
	{
		if (ch == '\n')
		{
			break;
		}
	}
	
}

void PrintTokenTest(const Token& t)
{
	if (t.kind == Tkind::Number)
	{
		std::cout << "Token image:" << t.value;
	}
	else
	{
		std::cout << "Token image: " << t.name;
	}
	std::cout << "  [ kind = " << GetTokenType(t) << ", value = " << t.value << ", name = " << t.name << " ]" << std::endl;
}

bool CTStream::IsEmpty() const
{
	char ch;
	if (m_tstream >> ch)
	{
		m_tstream.putback(ch);
		return false;
	}
	else
	{
		return !m_buffull;
	}
}
