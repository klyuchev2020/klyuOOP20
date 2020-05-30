#include "CFunction.h"
#include "CParser.h"

CFunction::CFunction(const std::string& name, const std::vector<Token>& fdef)
	: m_fname(name)
	, m_fdef(fdef)
{
}

double CFunction::GetValue() const
{
	return IsDefined() ? m_fvalue : undefined;
}


void CFunction::SetValue(double val)
{
	m_fvalue = undefined;
}



bool CFunction::IsDefined() const
{
	return !isnan(m_fvalue);
}
