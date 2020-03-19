#include "stdafx.h"
#include "HTMLdecode.h"

int main()
{
	std::cout << "Enter some strings with &quot; , &apos; , &lt; , &gt; , &amp; macroses to decode:\n";
	std::cout.flush();
	std::string codeString;

	while (std::getline(std::cin, codeString))
	{
		std::cout << Decode(codeString) << std::endl;
	}

	return 0;
}
