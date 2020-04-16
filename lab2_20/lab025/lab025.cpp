// lab025.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "parseURL.h"

int main()
{
	Protocol protocol;
	std::string url;
	std::string host;
	std::string document;
	int port;

	std::cout << "Enter the URL string or \"quit\" to exit\n> ";

	while (std::getline(std::cin, url) && url != "quit")
	{
		if (parseURL(url, protocol, port, host, document))
		{
			std::cout << "\n"
					  << url << std::endl;
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			std::cout << " DOC: " << document << "\n"
					  << std::endl;
			std::cout << "Enter the URL string \"quit\" to exit\n> ";
		}
		else
		{
			std::cout << "Given string\n"
					  << std::endl;
			std::cout << url << std::endl;
			std::cout << "\nis not well-arranged URL. "
						 "Try again or enter \"quit\" to exit\n> ";
		}
	}
	std::cout << "Good bye!" << std::endl;

	return 0;
}