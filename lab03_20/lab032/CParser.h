#pragma once

#include "stdafx.h"
#include "CTStream.h"
#include "CVars.h"



class CParser
{
public:
	CParser(std::istream& is);

	void ParseInstruction(std::ostream& os = std::cout);
	void ParseVarDecl(std::ostream& os = std::cout);
	void ParseAssignment(std::ostream& os = std::cout);
	void ParseFuncDef(std::ostream& os = std::cout);
	void ParsePrintVar(std::ostream& os = std::cout);
	void ParsePrintVars(std::ostream& os = std::cout);
	void ParsePrintFuncs(size_t currTik, std::ostream& os = std::cout);
	bool StreamIsEmpty() const;
	void SkipStream();
	size_t GetTik() const;
	const CVars* GetVars() const;
				
private:
	CTStream m_tstream;
	CVars m_vars;
	size_t m_tik = 1;
};


