#include "CParser.h"
#include "CTStream.h"

CParser::CParser(std::istream& is)
	: m_tstream(is)
{
}

void CParser::ParseInstruction()
{

}

void CParser::ParseVarDecl()
{

}

void CParser::ParseAssignment()
{

}

void CParser::ParseFuncDef()
{

}

void CParser::ParsePrintVars()
{

}

void CParser::ParsePrintFuncs()
{

}

double CParser::CalcFunction(const std::string& fname)
{
	auto it = m_functions.find(fname);
	if (it != m_functions.end())
    {
		if (m_functions[fname].m_fdef.size() == 1)
		{
			m_functions[fname].m_fvalue = m_variables.GetVarValue(m_functions[fname].m_fdef[0].name);
		}

	}
	return 0.0;
}