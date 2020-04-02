// lab024CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"

TEST_CASE("Proper nymber of primes for small bounds")
{

	size_t primesAmountFor0 = GeneratePrimeNumbersSet(0).size();

	CHECK(primesAmountFor0 == 0);

	size_t primesAmountFor1 = GeneratePrimeNumbersSet(1).size();

	CHECK(primesAmountFor1 == 0);

	size_t primesAmountFor2 = GeneratePrimeNumbersSet(2).size();

	CHECK(primesAmountFor2 == 1);
}

TEST_CASE("Proper primes numbers for upper bound 20, 100, 99999999, 100000000")
{
	size_t primesAmountFor20 = GeneratePrimeNumbersSet(20).size();

	CHECK(primesAmountFor20 == 8);

	size_t primesAmountFor100 = GeneratePrimeNumbersSet(100).size();

	CHECK(primesAmountFor100 == 25);

#ifndef _DEBUG
	{
		size_t primesAmountForEightNines = GeneratePrimeNumbersSet(99999999).size();

		CHECK(primesAmountForEightNines == 5761455);

		size_t primesAmountForHuge = GeneratePrimeNumbersSet(100000000).size();

		CHECK(primesAmountForHuge == 5761455);
	}
#endif
}



