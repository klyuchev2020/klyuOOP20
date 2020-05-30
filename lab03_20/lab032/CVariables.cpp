#pragma once

#include "CParser.h"
#include "CVariables.h"

bool CParser::CVariables::DeclareVar(const std::string& name)
{
	if (IsVarDeclared(name))
	{
		std::cout << "Variable " << name << " is already declared" << std::endl;
		return false;
	}
	else
	{
		m_vars[name] = undefined;
	}
	return true;
}

double CParser::CVariables::SetVarValue(const std::string& name, const double value)
{
	if (!IsVarDeclared(name))
	{
		std::cout << "Variable " << name << " is not declared" << std::endl;
	}
	else
	{
		m_vars.at(name) = value;
		return value;
	}

	return undefined;
}

double CParser::CVariables::SetVarValue(const std::string& nameTo, const std::string& nameFrom)
{
	if (!IsVarDeclared(nameTo))
	{
		std::cout << "Variable " << nameTo << " is not declared" << std::endl;
	}
	else if (!IsVarDeclared(nameFrom))
	{
		std::cout << "Variable " << nameFrom << " is not declared" << std::endl;
	}
	else
	{
		return m_vars.at(nameTo) = m_vars.at(nameFrom);
	}

	return undefined;
}

double CParser::CVariables::GetVarValue(const std::string& name) const
{
	if (!IsVarDeclared(name))
	{
		std::cout << "Variable " << name << " is not declared" << std::endl;
	}
	else if (IsVarDefined(name))
	{
		return m_vars.at(name);
	}
	return undefined;
}

std::string CParser::CVariables::PrintVar(const std::string& name) const
{
	std::ostringstream outString;
	if (!IsVarDeclared(name))
	{
		outString << "Variable " << name << " is not declared" << std::endl;
	}
	else
	{
		outString << name << " : " << std::setprecision(2) << m_vars.at(name) << std::endl;
	}
	return outString.str();
}

void CParser::CVariables::PrintVars() const
{
}

bool CParser::CVariables::IsVarDeclared(const std::string& name) const
{
	return m_vars.find(name) != m_vars.end();
}

bool CParser::CVariables::IsVarDefined(const std::string& name) const
{
	return !isnan(m_vars.at(name));
}
