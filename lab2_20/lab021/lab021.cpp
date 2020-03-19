#include "stdafx.h"
#include "TransformVector.h"


std::vector<float> LoadSeriesToVector(std::istream& input)
{
	std::vector<float> values;

	std::copy(std::istream_iterator<float>(input), std::istream_iterator<float>(), std::back_inserter(values));
	input.clear();

	return values;
}

void LoadVectorToSeries(const std::vector<float>& values, std::ostream& output)
{
	std::copy(values.begin(), values.end(), std::ostream_iterator<float>(output, " "));
}


void Modificate(std::vector<float>& values)
{
	if (values.size() != 0)
	{
		auto minMax = std::minmax_element(values.begin(), values.end());
		float multiplier = (*minMax.first) * (*minMax.second);
		std::for_each(values.begin(), values.end(), [multiplier](float& f) { f = (f < 0) ? multiplier * f : f; });
	}
}


