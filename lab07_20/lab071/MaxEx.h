#pragma once

#include "stdafx.h"
#include "Sportsman.h"

template <typename T>
class Less
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return (a < b); 
	}
};

template<>
class Less<const char*>
{
public:
	bool operator()(const char* a, const char* b) const
	{
		return strcmp(a, b) < 0;
	}
};

template <>
class Less<Sportsman>
{
public:
	bool operator()(const Sportsman& sman1, const Sportsman& sman2) const
	{
		return (sman1.height < sman2.height);
	}
};


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
			maxValueNumber = (less(maxValue, arr[i])) ? i : maxValueNumber; 
		}
		maxValue = arr[maxValueNumber];
		return true;
	}
}
