// lab032.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "CTokenSeries.h"

int main()
{
	try
	{
		std::cout << "Calculator driver\n";
		Token token;

		while (std::cin)
		{
			token = GetToken(std::cin);
			PrintTokenTest(token);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
