#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"

std::vector<bool> SieveResult(size_t bound) // просеивает позиции по методу решета Ёратосфена,
{ // оставл€€ true на позици€х простых чисел
	std::vector<bool> result(bound + 1, true);
	result[0] = false;
	if (bound > 0)
	{
		result[1] = false;
		size_t lastPrime = 2;
		while (lastPrime * lastPrime <= bound)
		{
			for (size_t i = lastPrime * lastPrime; i <= bound; i += lastPrime)
			{
				result[i] = false;
			}
			/*
			этот код находит следующее простое число. Ќо тогда и просеивание не нужно
			std::vector<bool>::iterator startFindNextPrime = result.begin() + lastPrime + 1;
			std::vector<bool>::iterator primePosition = std::find(startFindNextPrime, result.end(), true);
			lastPrime += std::distance(startFindNextPrime, primePosition) + 1;
			*/
			++lastPrime;
		}
	}
	return result;
}

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::vector<bool> primesPositions = SieveResult(upperBound);
	std::set<size_t> result;
	int number = 0;
	for (size_t i = 0; i < primesPositions.size(); ++i)
	{
		if (primesPositions[i])
		{
			result.insert(result.end(), number);
		}
		++number;
	}
	return result;
}
