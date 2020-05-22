// lab024.cpp: определяет точку входа для консольного приложения.
// поиск простых чисел в пределах upperBound

#include "stdafx.h"
#include "GeneratePrimes.h"

int main(int argc, char* argv[])
{
	constexpr size_t maxBound = 100000000;
	constexpr size_t defaultBound = 10000;
	size_t upperBound = maxBound;
	size_t primesAmount = 0;

	if (argc > 1)
	{
		upperBound = ((isdigit(argv[1][0]) && (std::stoi(argv[1]) >= 0))) ? std::stoi(argv[1]) : defaultBound;
	}
	else
	{
		upperBound = defaultBound;
	}
	if (upperBound > maxBound)
	{
		upperBound = maxBound;
	}
	std::cout << "Finds set of prime numbers below " << upperBound << std::endl;

	clock_t time = clock();
	std::set<size_t> primes(GeneratePrimeNumbersSet(upperBound));
	time = clock() - time;
	std::cout << "\nCalculates " << ((float)time) / CLOCKS_PER_SEC << " seconds" << std::endl;

	std::cout << primes.size() << " primary numbers upto " << upperBound << " overall:" << std::endl;
	time = clock();
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;
	time = clock() - time;
	std::cout << "\nOutput in " << ((float)time) / CLOCKS_PER_SEC << " seconds" << std::endl;

	return 0;
}
