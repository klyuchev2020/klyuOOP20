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

	Less<const char*> ccharcomp;
	if (ccharcomp("bab", "abc"))
	{
		std::cout << "less cchar" << std::endl;
	}
	else
	{
		std::cout << "greater or equal cchar" << std::endl;
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

	std::vector<const char*> testArrayCchar = { "myshka", "koshka", "zhuchka", "vnuchka", "babka", "dedka", "repka" };
	const char* maxCchar;
	if (FindMax(testArrayCchar, maxCchar, ccharcomp))
	{
		std::cout << "Maximal = " << maxCchar << std::endl;
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

	Less<Sportsman> hless;

	Sportsman tallMan;
	if (FindMax(champions, tallMan, hless))
	{
		std::cout << "Most tall sportsman is" << std::endl;
		std::cout << tallMan;
	}
	else
	{
		std::cout << "No sportsmen at all!" << std::endl;
	}
		
	return 0;
}
