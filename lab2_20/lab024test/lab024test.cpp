// lab024CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"


bool TheSameNaturalSet(std::istream& is, const std::set<size_t>& intSet)
{
	return std::equal(std::istream_iterator<size_t>(is), std::istream_iterator<size_t>(), intSet.begin());
}	

TEST_CASE("Proper number of primes for small bounds")
{

	size_t primesAmountFor0 = GeneratePrimeNumbersSet(0).size();

	CHECK(primesAmountFor0 == 0);

	size_t primesAmountFor1 = GeneratePrimeNumbersSet(1).size();

	CHECK(primesAmountFor1 == 0);

	size_t primesAmountFor2 = GeneratePrimeNumbersSet(2).size();

	CHECK(primesAmountFor2 == 1);
}

TEST_CASE("Prime numbers set has proper elements")
{
	std::istringstream first10primes("2 3 5 7 11 13 17 19 23 29");
	CHECK(TheSameNaturalSet(first10primes, GeneratePrimeNumbersSet(30)));
	
	std::istringstream first25primes("2 3 5 7 11 13 17 19 23 29 31 "
									 "37 41 43 47 53 59 61 67 71 73 "
									 "79 83 89 97");
	CHECK(TheSameNaturalSet(first25primes, GeneratePrimeNumbersSet(100)));

	std::istringstream primesUpToThousand("2	3	5	7	11	13	17	19	23	29 "
										  "31	37	41	43	47	53	59	61	67	71 "
										  "73	79	83	89	97	101	103	107	109	113 "
										  "127 131 137	139	149	151	157	163	167	173 "
										  "179	181	191	193	197	199	211	223	227	229 "
										  "233	239	241	251	257	263	269	271	277	281 "
										  "283	293	307	311	313	317	331	337	347	349 "
										  "353	359	367	373	379	383	389	397	401	409 "
										  "419	421	431	433	439	443	449	457	461	463 "
										  "467	479	487	491	499	503	509	521	523	541 "
										  "547	557	563	569	571	577	587	593	599	601 "
										  "607	613	617	619	631	641	643	647	653	659 "
										  "661	673	677	683	691	701	709	719	727	733 "
										  "739	743	751	757	761	769	773	787	797	809 "
										  "811	821	823	827	829	839	853	857	859	863 "
										  "877	881	883	887	907	911	919	929	937	941 "
										  "947	953	967	971	977	983	991	997");
	CHECK(TheSameNaturalSet(primesUpToThousand, GeneratePrimeNumbersSet(1000)));

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

		clock_t time = clock();
		size_t primesAmountForHuge = GeneratePrimeNumbersSet(100000000).size();
		time = clock() - time;
		float seconds = ((float)time) / CLOCKS_PER_SEC;
		
		CHECK(primesAmountForHuge == 5761455);
		CHECK(seconds < 10.0f); // на машине автора 6.77 c (Release x64)
		
	}
#endif
}

