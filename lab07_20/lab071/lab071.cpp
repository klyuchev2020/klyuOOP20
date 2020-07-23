#include "stdafx.h"
#include "MaxEx.h"
#include "Sportsman.h"

int main()
{
	Less<int> comp;

	if (comp(2, 3))
	{
		std::cout << "less" << std::endl;
	}
	else
	{
		std::cout << "greater or equal" << std::endl;
	}

	std::vector<int> testArray = { 23, 3, 45, 34, 2, 37, 2, 12, 21, 24 };
	int max;
	if (FindMax(testArray, max, comp))
	{
		std::cout << "Maximal = " << max << std::endl;
	}
	else
	{
		std::cout << "Array is empty" << std::endl;
	}

	std::vector<Sportsman> champions;
	Sportsman sman;

	while (std::cin >> sman)
	{
		champions.push_back(sman);				
	}

	std::copy(champions.begin(), champions.end(), std::ostream_iterator<Sportsman>(std::cout, "\n"));

	std::cin.clear();

	Less<Sportsman, 1> hless;

	Sportsman tallMan;
	if (FindMax(champions, tallMan, hless))
	{
		std::cout << "Most tall" << std::endl;
		std::cout << tallMan;
	}
	else
	{
		std::cout << "No sportsmen at all!" << std::endl;
	}
	
	Less<Sportsman, 2> wless;

	Sportsman fatMan;
	if (FindMax(champions, fatMan, wless))
	{
		std::cout << "Most fat" << std::endl;
		std::cout << fatMan;
	}
	else
	{
		std::cout << "No sportsmen at all!" << std::endl;
	}
		
	return 0;
}
