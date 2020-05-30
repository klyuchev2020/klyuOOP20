// lab032.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "CTStream.h"

int main()
{
	try
	{
		std::cout << "Calculator driver\n";
		CTStream tstream;
		Token token;

		while (std::cin)
		{
			token = tstream.GetToken();
			PrintTokenTest(token);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
