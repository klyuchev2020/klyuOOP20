// lab032.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "stdafx.h"
#include "CTStream.h"
#include "CVars.h"
#include "CParser.h"
#include "CError.h"

double FibonacciFromBinet(size_t n)
{
	double base1 = (std::pow(5, 0.5) + 1) / 2;
	double base2 = (std::pow(5, 0.5) - 1) / 2;
	double sign = (n % 2 == 0) ? 1.0 : -1.0;
	return (std::pow(base1, n) - sign * std::pow(base2, n)) / std::pow(5, 0.5);
}

void GetFibonacciWise(std::ostream& os, int init0, int init1, size_t lastN)
{
	os << "var x0\n";
	os << "var x1\n";
	os << "fn f0 = x0\n";
	os << "fn f1 = x1\n";
	for (size_t i = 2; i <= lastN; ++i)
	{
		os << "fn f" << i << " = f" << i - 1 << " + f" << i - 2 << "\n";
	}
	os << "let x0 = " << init0 << "\n";
	os << "let x1 = " << init1 << "\n";
	os << "print f" << lastN - 1 << "\n";
	os << "print f" << lastN << "\n";
}


int main()
{
	std::ofstream fib("fib30.txt");
	GetFibonacciWise(fib, 0, 1, 30);
	fib.close();

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout << "f29 = " << FibonacciFromBinet(29) << std::endl;
	std::cout << "f30 = " << FibonacciFromBinet(30) << std::endl;

	std::ifstream ifib("fib30.txt");

	CParser parser(ifib);	

	while (!parser.StreamIsEmpty())
	{
		try
		{
			parser.ParseInstruction(std::cout);
			
		}
		catch (CError::BadToken bt)
		{
			std::cout << bt.mess << std::endl;
			parser.SkipStream();
		}
		catch (CError::ParserError pe)
		{
			std::cout << pe.mess << std::endl;
			parser.SkipStream();
		}
		catch (CError::ArithmeticError ae)
		{
			std::cout << ae.mess << std::endl;
			parser.SkipStream();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	return 0;
}
