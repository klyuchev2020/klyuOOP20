#pragma once

#include "stdafx.h"
#include "CTStream.h"
#include "CParser.h"


class CParser::CVariables
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
