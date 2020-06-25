#pragma once

#include "stdafx.h"

struct Variable
{
	Variable(const std::string& n, const size_t lastMod);
	Variable(const std::string& n, const std::set<std::string>& fVars,
		const std::vector<std::string>& calc, const std::vector<std::string>& calcPfx, const size_t lastMod);

	std::string name;
	double value = std::nan("");
	size_t lastModified;
	std::set<std::string> freeVars; // имена свободных переменных, от которых зависит данная переменная (свободная или функция)
	std::vector<std::string> calculation; // для свободной переменной это просто имя переменной (иначе постфиксная запись вычисления)
	std::vector<std::string> calcPostfix; // постфиксная запись через свободные переменные
};

class CVars
{
public:
	bool IsDeclared(const std::string& n) const;

	bool DeclareFreeVar(const std::string& n, size_t lastMod);

	bool DeclareFunction(const std::string& n, const std::set<std::string>& fVars,
		const std::vector<std::string>& calc, const std::vector<std::string>& calcPfx, size_t lastMod);

	bool IsDefined(const std::string& varName) const;

	bool IsFreeVarName(const std::string& varName) const;

	bool IsFunctionName(const std::string& varName) const;

	double GetValue(const std::string& varName) const;

	size_t GetCalcTime(const std::string& varName) const;

	double SetVarValue(const std::string& varName, double val, size_t lastMod);

	double CalcFunctionValue(const std::string& varName, size_t lastMod);

	double CalcFuctionWithStack(const std::string& varName, size_t lastMod);

	void PrintFreeVars(std::ostream& os) const;

	void PrintFunctions(size_t currTik, std::ostream& os);

	const std::set<std::string>& GetFreeVars(const std::string& varName) const;

	const std::vector<std::string>& GetPostfix(const std::string& varName) const;

	std::set<std::string> SetFreeVars(const std::string& name, const std::vector<std::string>& calc);

	std::vector<std::string> SetCalcPostfix(const std::string& name, const std::vector<std::string>& calc);

	size_t GetLastModified(const std::string& varName) const;

	bool NeedRecalculated(const std::string& varName) const;

private:
	const Variable* GetVariable(const std::string& varName) const;
	Variable* ModVariable(const std::string& varName);
	std::map<std::string, Variable> m_vars;
};
