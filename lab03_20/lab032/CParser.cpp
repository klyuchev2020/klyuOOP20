#include "CParser.h"
#include "CError.h"
#include "CTStream.h"

CParser::CParser(std::istream& is)
	: m_tstream(is)
{
}

void CParser::ParseInstruction(std::ostream& os)
{

	if (m_tstream.IsEmpty())
	{
		return;
	}

	Token t = m_tstream.GetToken();
	if (t.kind == Tkind::End)
	{
		return;
	}

	if (t.kind != Tkind::Keyword)
	{
		throw CError::ParserError("Unknown instruction!", 20);
	}
	else
	{
		if (t.name == "var")
		{
			ParseVarDecl(os);
		}
		else if (t.name == "let")
		{
			ParseAssignment(os);
		}
		else if (t.name == "fn")
		{
			ParseFuncDef(os);
		}
		else if (t.name == "print")
		{
			ParsePrintVar(os);
		}
		else if (t.name == "printvars")
		{
			ParsePrintVars(os);
		}
		else if (t.name == "printfns")
		{
			ParsePrintFuncs(m_tik, os);
		}
		else
		{
			throw CError::ParserError("Unknown instruction name!", 20);
		}
	}
	m_tik++;
}

void CheckIsIdentor(const Token& t)
{
	if (t.kind != Tkind::Identor)
	{
		throw CError::ParserError("Identificator expected!", 21);
	}
}

void CheckIdentorNotInUse(const CVars& vars, const Token& t)
{
	if (vars.IsDeclared(t.name))
	{
		throw CError::ParserError("Identificator is already in use", 22);
	}
}

void CParser::ParseVarDecl(std::ostream& os)
{
	Token t = m_tstream.GetToken();
	CheckIsIdentor(t);
	CheckIdentorNotInUse(m_vars, t);
	m_vars.DeclareFreeVar(t.name, m_tik);
}

void CheckIsEquationSymbol(Token t)
{
	if (t.kind != Tkind::Symbol || t.name != "=")
	{
		throw CError::ParserError("Equation symbol expected!", 23);
	}
}

void CheckIdentorIsInUse(const CVars& vars, const Token& t)
{
	if (!vars.IsDeclared(t.name))
	{
		throw CError::ParserError("Identificator is not yet declared", 24);
	}
}

void CParser::ParseAssignment(std::ostream& os)
{
	Token t = m_tstream.GetToken();
	CheckIsIdentor(t); // все функции на Check... здесь могут выбросить исключение
	std::string id1 = t.name;

	t = m_tstream.GetToken();
	CheckIsEquationSymbol(t);

	t = m_tstream.GetToken();
	if (t.kind == Tkind::Identor)
	{
		CheckIdentorIsInUse(m_vars, t);
		m_vars.DeclareFreeVar(id1, m_tik);
		m_vars.SetVarValue(id1, m_vars.GetValue(t.name), m_tik);
	}
	else if (t.kind == Tkind::Number)
	{
		m_vars.DeclareFreeVar(id1, m_tik);
		m_vars.SetVarValue(id1, t.value, m_tik);
	}
	else
	{
		throw CError::ParserError("Bad assignment", 25);
	}
}

void CParser::ParseFuncDef(std::ostream& os)
{
	Token t = m_tstream.GetToken();
	CheckIsIdentor(t);
	CheckIdentorNotInUse(m_vars, t);

	std::string fname = t.name;

	t = m_tstream.GetToken();
	CheckIsEquationSymbol(t);

	t = m_tstream.GetToken();
	CheckIsIdentor(t);
	CheckIdentorIsInUse(m_vars, t);
	std::string firstArg = t.name;

	t = m_tstream.GetToken();
	std::vector<std::string> calc;

	if (t.kind == Tkind::Keyword || t.kind == Tkind::End)
	{
		m_tstream.PutBack(t);
		calc.push_back(firstArg);
		
		m_vars.DeclareFunction(fname, m_vars.SetFreeVars(fname, calc), calc, 
			m_vars.SetCalcPostfix(fname, calc), 0);
		//m_vars.CalcFunctionValue(fname, m_tik);  рекурсивный вариант
		m_vars.CalcFuctionWithStack(fname, m_tik);
	}
	else if (t.kind == Tkind::Symbol)
	{
		std::string op;
		if (t.name != "=")
		{
			op = t.name;
		}
		else
		{
			throw CError::ParserError("Arithmetic operation expected", 26);
		}
		t = m_tstream.GetToken();
		CheckIsIdentor(t);
		CheckIdentorIsInUse(m_vars, t);
		std::string secondArg = t.name;
		calc.push_back(firstArg);
		calc.push_back(secondArg);
		calc.push_back(op);
		
		m_vars.DeclareFunction(fname, m_vars.SetFreeVars(fname, calc), calc,
			m_vars.SetCalcPostfix(fname, calc), 0);
		//m_vars.CalcFunctionValue(fname, m_tik);   рекурсивная
		m_vars.CalcFuctionWithStack(fname, m_tik);
	}
	else
	{
		throw CError::ParserError("Bad function definition", 27);
	}
	
}

void CParser::ParsePrintVar(std::ostream& os)
{
	Token t = m_tstream.GetToken();
	CheckIsIdentor(t);
	CheckIdentorIsInUse(m_vars, t);

	double value = (m_vars.IsFreeVarName(t.name)) ? m_vars.GetValue(t.name) : m_vars.CalcFuctionWithStack(t.name, m_tik);
	//: m_vars.CalcFunctionValue(t.name, m_tik); была рекурсивная 
		
	os.setf(std::ios_base::fixed, std::ios_base::floatfield);
	os.precision(2);
	os << t.name << ": " << value << std::endl;
}

void CParser::ParsePrintVars(std::ostream& os)
{
	m_vars.PrintFreeVars(os);
}

void CParser::ParsePrintFuncs(size_t currTik, std::ostream& os)
{
	m_vars.PrintFunctions(currTik, os);
}

bool CParser::StreamIsEmpty() const
{
	return m_tstream.IsEmpty();
}

void CParser::SkipStream()
{
	m_tstream.Skip();
}

size_t CParser::GetTik() const
{
	return m_tik;
}

const CVars* CParser::GetVars() const
{
	return &m_vars;
}