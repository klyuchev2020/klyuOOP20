#pragma once

#include "stdafx.h"
#include "Sportsman.h"

template <typename T, int index = -1>
class Less
{
public:
	bool operator()(const T& a, const T& b) const;
};

template <typename T, int index>
bool Less<T, index>::operator()(const T& a, const T& b) const
{
	return (a < b);	
}


template <int index>
class Less<Sportsman, index>
{
public:
	bool operator()(const Sportsman& sman1, const Sportsman& sman2) const;
};

bool Less<Sportsman, 1>::operator()(const Sportsman& sman1, const Sportsman& sman2) const
{
	return (sman1.height < sman2.height);
}

bool Less<Sportsman, 2>::operator()(const Sportsman& sman1, const Sportsman& sman2) const
{
	return (sman1.weight < sman2.weight);
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.size() == 0)
	{
		return false;
	}
	else
	{
		size_t maxValueNumber = 0;
		for (size_t i = 0; i < arr.size(); ++i)
		{
			maxValueNumber = (less(arr[maxValueNumber], arr[i])) ? i : maxValueNumber; 
		}
		maxValue = arr[maxValueNumber];
		return true;
	}
}
