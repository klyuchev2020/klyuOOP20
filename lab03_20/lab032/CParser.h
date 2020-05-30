#pragma once

#include "stdafx.h"
#include "CTStream.h"
#include "CVariables.h"
#include "CFunction.h"


class CParser
{
public:
	CParser(std::istream& is);

	void ParseInstruction();
	void ParseVarDecl();
	void ParseAssignment();
	void ParseFuncDef();
	void ParsePrintVars();
	void ParsePrintFuncs();
	double CalcFunction(const std::string& fname);
	
	class CVariables
	{
	public:
		bool DeclareVar(const std::string& name);
		double SetVarValue(const std::string& name, const double value);
		double SetVarValue(const std::string& nameTo, const std::string& nameFrom);
		double GetVarValue(const std::string& name) const;
		std::string PrintVar(const std::string& name) const;
		void PrintVars() const;
		bool IsVarDeclared(const std::string& name) const;
		bool IsVarDefined(const std::string& name) const;

	private:
		std::map<std::string, double> m_vars;
	};
		
private:

	CTStream m_tstream;
	CVariables m_variables;
	std::map<std::string, CFunction> m_functions;
};


