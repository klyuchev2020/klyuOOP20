#include "stdafx.h"
#include "parseURL.h"

std::string StrToUpper(const std::string& sourceStr)
{
	std::string resultStr;
	for (size_t i = 0; i < sourceStr.size(); ++i)
	{
		resultStr.push_back(std::toupper(static_cast<unsigned char>(sourceStr[i])));
	}
	return resultStr;
}

bool DetectProtocol(Protocol& protocol, const std::string& protocolStr)
{
	std::string upperProStr = StrToUpper(protocolStr);
	if (upperProStr == "HTTP")
	{
		protocol = Protocol::HTTP;
		return true;
	}
	else if (upperProStr == "HTTPS")
	{
		protocol = Protocol::HTTPS;
		return true;
	}
	else if (upperProStr == "FTP")
	{
		protocol = Protocol::FTP;
		return true;
	}
	return false;
}

int GetDefaultPortNumber(const Protocol& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	}
	return 0;
}

bool ValidPortNumber(const int portNumber)
{
	return (portNumber >= 1) && (portNumber <= 65535);
}

void TrimPrefixSymbol(std::string& prefixedString)
{
	if (!prefixedString.empty())
	{
		prefixedString.erase(0, 1);
	}
}

bool SetPort(int& port, const std::string& portStr, const Protocol protocol)
{
	if (portStr.empty())
	{
		port = GetDefaultPortNumber(protocol);
		return true;
	}
	else
	{
		std::string portS = portStr;
		TrimPrefixSymbol(portS);
		int portValue = std::stoi(portS);
		if (ValidPortNumber(portValue))
		{
			port = portValue;
			return true;
		}
	}
	return false;
}

void SetDocument(std::string& document, const std::string& docStr)
{
	if (!docStr.empty())
	{
		document = docStr;
		TrimPrefixSymbol(document);
	}
}

bool parseURL(const std::string& url, Protocol& protocol, int& port,
	std::string& host, std::string& document)
{
	protocol = Protocol::HTTP;
	port = 0;
	host = "";
	document = "";

	if (url.empty())
	{
		return false;
	}

	std::regex urlRegex(R"mark(\s*(HTTP|HTTPS|FTP)://)mark"
						R"mark(((?:[-\wà-ÿÀ-ß]+\.[\wà-ÿÀ-ß])+[\wà-ÿÀ-ß]*)(:\d{1,5})?(/.*)?)mark",
		std::regex::icase);
	std::smatch urlMatch;

	if (!std::regex_match(url, urlMatch, urlRegex) || urlMatch.size() < 5)
	{
		return false;
	}
	else
	{
		DetectProtocol(protocol, urlMatch[1]);
		host = urlMatch[2];
		if (!SetPort(port, urlMatch[3], protocol))
		{
			return false;
		}
		SetDocument(document, urlMatch[4]);
	}
	return true;
}
