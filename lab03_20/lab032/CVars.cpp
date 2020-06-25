#include "CVars.h"
#include "CError.h"
#include "CTStream.h"

Variable::Variable(const std::string& n, const size_t lastMod) // конструктор для свободной переменной
	: name(n)
	, value(undefined)
	, lastModified(lastMod)
{
	freeVars.insert(n);
	calculation.push_back(n);
	calcPostfix.push_back(n);
}

Variable::Variable(const std::string& n, const std::set<std::string>& fVars,
	const std::vector<std::string>& calc, const std::vector<std::string>& calcPfx, const size_t lastMod) // конструктор для функции
	: name(n)
	, value(undefined)
	, freeVars(fVars)
	, calculation(calc)
	, calcPostfix(calcPfx)
	, lastModified(lastMod)
{
}

const std::set<std::string>& CVars::GetFreeVars(const std::string& varName) const
{
	return GetVariable(varName)->freeVars;
}

std::set<std::string> CVars::SetFreeVars(const std::string& name, const std::vector<std::string>& calc) // сразу после определения функции (когда calc.size() == 1 или 3)
{
	if (calc.size() == 1)
	{
		return GetFreeVars(calc[0]);
	}
	else if (calc.size() == 3)
	{
		std::set<std::string> fVars(GetFreeVars(calc[0]));
		fVars.insert(GetFreeVars(calc[1]).begin(), GetFreeVars(calc[1]).end());
		return fVars;
	}
	else
	{
		throw CError::ParserError("Wrong function definition", 28);
	}
}

const std::vector<std::string>& CVars::GetPostfix(const std::string& varName) const
{
	return GetVariable(varName)->calcPostfix;
}

std::vector<std::string> CVars::SetCalcPostfix(const std::string& name, const std::vector<std::string>& calc)
{
	if (calc.size() == 1)
	{
		return GetPostfix(calc[0]);
	}
	else if (calc.size() == 3)
	{
		std::vector<std::string> calcPfx(GetPostfix(calc[0]));
		calcPfx.insert(calcPfx.end(), GetPostfix(calc[1]).begin(), GetPostfix(calc[1]).end());
		calcPfx.push_back(calc[2]);
			
		return calcPfx;
	}
	else
	{
		throw CError::ParserError("Wrong function definition", 28);
	}
}

const Variable* CVars::GetVariable(const std::string& varName) const
{
	if (IsDeclared(varName))
	{
		return &(m_vars.find(varName)->second);
	}
	else
	{
		return nullptr;
	}
}

Variable* CVars::ModVariable(const std::string& varName)
{
	if (IsDeclared(varName))
	{
		return &(m_vars.find(varName)->second);
	}
	else
	{
		return nullptr;
	}
}

bool CVars::IsDeclared(const std::string& n) const
{
	return m_vars.find(n) != m_vars.end();
}

bool CVars::DeclareFreeVar(const std::string& n, size_t lastMod)
{
	if (!IsDeclared(n))
	{
		Variable declaredVar(n, lastMod);
		auto res = m_vars.insert(std::pair<std::string, Variable>(n, declaredVar));
		return res.second;
	}
	return false;
}

bool CVars::DeclareFunction(const std::string& n, const std::set<std::string>& fVars,
	const std::vector<std::string>& calc, const std::vector<std::string>& calcPfx, size_t lastMod)
{
	if (!IsDeclared(n))
	{
		Variable declaredVar(n, fVars, calc, calcPfx, 0);
		auto res = m_vars.insert(std::pair<std::string, Variable>(n, declaredVar));
		return res.second;
	}
	return false;
}

bool CVars::IsDefined(const std::string& varName) const
{
	return !isnan(GetVariable(varName)->value);
}

bool CVars::IsFreeVarName(const std::string& varName) const
{
	return ((GetVariable(varName)->calculation).size() == 1) && ((GetVariable(varName)->calculation)[0] == varName);
}

bool CVars::IsFunctionName(const std::string& varName) const
{
	return IsDeclared(varName) && !(IsFreeVarName(varName));
}

double CVars::GetValue(const std::string& varName) const
{
	return GetVariable(varName)->value;
}

size_t CVars::GetCalcTime(const std::string& varName) const
{
	return GetVariable(varName)->lastModified;
}

double CVars::SetVarValue(const std::string& varName, double val, size_t lastMod)
{
	ModVariable(varName)->lastModified = lastMod;
	return ModVariable(varName)->value = val;
}

size_t CVars::GetLastModified(const std::string& varName) const
{
	size_t last = 0;
	auto freeVars = GetFreeVars(varName);
	for (auto it = freeVars.begin(); it != freeVars.end(); ++it)
	{
		if (GetVariable(*it)->lastModified > last)
		{
			last = GetVariable(*it)->lastModified;
		}
	}

	return last;
}


bool CVars::NeedRecalculated(const std::string& varName) const
{
	return (GetLastModified(varName) > GetCalcTime(varName));
}

double CVars::CalcFunctionValue(const std::string& varName, size_t lastMod)
{
	size_t prevModified = GetCalcTime(varName);
	if (!NeedRecalculated(varName))
	{
		return GetValue(varName);
	}
	ModVariable(varName)->lastModified = lastMod;

	size_t calcSize = (GetVariable(varName)->calculation).size();
	if (calcSize == 1)
	{
		std::string evalName = (GetVariable(varName)->calculation)[0];
		return SetVarValue(varName, GetVariable(evalName)->value, lastMod);
	}
	if (calcSize == 3)
	{
		std::string arg1 = (GetVariable(varName)->calculation)[0];
		std::string arg2 = (GetVariable(varName)->calculation)[1];
		std::string oprt = (GetVariable(varName)->calculation)[2];

		double val1 = CalcFunctionValue(arg1, lastMod);
		double val2 = CalcFunctionValue(arg2, lastMod);

		if (isnan(val1) || isnan(val2))
			return undefined;

		if (oprt == "+")
		{
			return SetVarValue(varName, val1 + val2, lastMod);
		}
		else if (oprt == "-")
		{
			return SetVarValue(varName, val1 - val2, lastMod);
		}
		else if (oprt == "*")
		{
			return SetVarValue(varName, val1 * val2, lastMod);
		}
		else if (oprt == "/")
		{
			if (val2 == 0.0)
			{
				ModVariable(varName)->lastModified = prevModified;
				throw CError::ArithmeticError("Zero division!", 30);
			}
			else
			{
				return SetVarValue(varName, val1 / val2, lastMod);
			}
		}
	}

	return undefined;
}

double OpResult(const std::string& op, double first, double second)
{
	if (op == "+")
	{
		return first + second;
	}
	else if (op == "-")
	{
		return first - second;
	}
	else if (op == "*")
	{
		return first * second;
	}
	else if (op == "/")
	{
		if (second != 0.0)
		{
			return first / second;
		}
		else
		{
			throw CError::ArithmeticError("Zero division!", 30);
		}
	}
	else
	{
		return std::nan("");
	}
}

double CVars::CalcFuctionWithStack(const std::string& varName, size_t lastMod)
{
	size_t prevModified = GetCalcTime(varName);
	if (!NeedRecalculated(varName))
	{
		return GetValue(varName);
	}
	ModVariable(varName)->lastModified = lastMod;

	std::vector<std::string> content = GetPostfix(varName);
	std::vector<double> stc;

	for (size_t i = 0; i < content.size(); ++i)
	{
		std::string curr(content[i]);
		if ((curr == "+") || (curr == "-") || (curr == "*") || (curr == "/"))
		{
			double second = stc.back();
			stc.pop_back();
			double first = stc.back();
			stc.pop_back();
			stc.push_back(OpResult(curr, first, second));
		}
		else
		{
			double val = GetVariable(curr)->value;
			if (isnan(val))
			{
				return SetVarValue(varName, undefined, lastMod);
			}
			else
			{
				stc.push_back(val);
			}
		}
	}

	if (stc.size() == 1)
	{
		return SetVarValue(varName, stc[0], lastMod);
	}
	else
	{
		return undefined;
	}
}

void CVars::PrintFreeVars(std::ostream& os) const
{
	os.setf(std::ios_base::fixed, std::ios_base::floatfield);
	os.precision(2);

	for (auto it = m_vars.cbegin(); it != m_vars.cend(); ++it)
	{
		if (IsFreeVarName(it->first))
		{
			os << it->first << ": " << (it->second).value << std::endl;
		}
	}
}

void CVars::PrintFunctions(size_t currTik, std::ostream& os)
{
	os.setf(std::ios_base::fixed, std::ios_base::floatfield);
	os.precision(2);

	for (auto it = m_vars.cbegin(); it != m_vars.cend(); ++it)
	{
		if (IsFunctionName(it->first))
		{
			os << it->first << ": " << CalcFunctionValue(it->first, currTik) << std::endl;
		}
	}
}
