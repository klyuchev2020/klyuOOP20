#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"

std::vector<bool> SieveResult(unsigned int bound) // просеивает позиции по методу решета Ёратосфена,
{ // оставл€€ 1 на позици€х простых чисел
	std::vector<bool> result(bound + 1, 1);
	result[0] = 0;
	if (bound > 0)
	{
		result[1] = 0;
		size_t lastPrime = 2;
		while (lastPrime * lastPrime <= bound)
		{
			for (size_t i = lastPrime * lastPrime; i <= bound; i += lastPrime)
			{
				result[i] = false;
			}
			std::vector<bool>::iterator startFindNextPrime = result.begin() + lastPrime + 1;
			std::vector<bool>::iterator itPrimes = std::find(startFindNextPrime, result.end(), true);
			lastPrime += std::distance(startFindNextPrime, itPrimes) + 1;
		}
	}
	return result;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	std::vector<bool> primesPositions = SieveResult(upperBound);
	std::set<int> result;
	int number = 0;
	for (int i = 0; i < primesPositions.size(); ++i)
	{
		if (primesPositions[i])
		{
			result.insert(result.end(), number);
		}
		++number;
	}
	return result;
}
