// lab024.cpp: определяет точку входа для консольного приложения.
// поиск простых чисел в пределах upperBound

#include "stdafx.h"
#include "GeneratePrimes.h"

int main(int argc, char* argv[])
{
	constexpr unsigned int maxBound = 100000000;
	unsigned int upperBound = maxBound;
	unsigned int primesAmount = 0;
	if (argc > 1)
	{
		upperBound = ((isdigit(argv[1][0]) && (std::stoi(argv[1]) >= 0))) ? std::stoi(argv[1]) : maxBound;
	}
	if (upperBound > maxBound)
		upperBound = maxBound;
	std::cout << "Finds set of prime numbers below " << upperBound << std::endl;

	std::set<int> primes(GeneratePrimeNumbersSet(upperBound));
	std::cout << primes.size() << " primary numbers upto " << upperBound << " overall:" << std::endl;
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
	std::cout << std::endl;

	return 0;
}


