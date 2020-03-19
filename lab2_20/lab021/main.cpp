#include "stdafx.h"
#include "TransformVector.h"

int main()
{
	std::cout << "Enter floats. Delimiter is space:\n";
	std::vector<float> values = LoadSeriesToVector(std::cin);

	if (values.size() == 0)
	{
		std::cout << "Empty data!\n";
	}
	else
	{
		Modificate(values);
		LoadVectorToSeries(values, std::cout);
		std::cout << "\nAll negatives here are multiplied on min * max\n";
	}

	return 0;
}
