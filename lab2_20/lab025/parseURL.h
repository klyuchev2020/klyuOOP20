#pragma once

#include "stdafx.h"
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool parseURL(const std::string& url, Protocol& protocol, int& port,
	std::string& host, std::string& document);