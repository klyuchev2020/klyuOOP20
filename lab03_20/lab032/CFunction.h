#pragma once

#include "stdafx.h"
#include "CTStream.h"


class CFunction
{
public:
	CFunction(const std::string& name, const std::vector<Token>& fdef);

	double GetValue() const;
	void SetValue(double val);
	bool IsDefined() const;

	friend class CParser;

private:
	std::string m_fname;
	std::vector<Token> m_fdef;
	double m_fvalue = undefined;
};
