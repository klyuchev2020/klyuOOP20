#include "CError.h"

CError::ParserError::ParserError(const std::string& message, int errorNumber)
	: mess(message)
	, errnum(errorNumber)
{
}

CError::BadToken::BadToken(const std::string& message, int errorNumber)
	: mess(message)
	, errnum(errorNumber)
{
}

CError::ArithmeticError::ArithmeticError(const std::string& message, int errorNumber)
	: mess(message)
	, errnum(errorNumber)
{
}
