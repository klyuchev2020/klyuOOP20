#pragma once

#include "stdafx.h"

class CError
{
public:
	struct BadToken
	{
		std::string mess;
		int errnum;
		BadToken(const std::string& message, int errorNumber);
	};

	struct ParserError
	{
		std::string mess;
		int errnum;
		ParserError(const std::string& message, int errorNumber);
	};

	struct ArithmeticError
	{
		std::string mess;
		int errnum;
		ArithmeticError(const std::string& message, int errorNumber);
	};
};
