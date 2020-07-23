#pragma once

#include "stdafx.h"

struct Sportsman
{
	std::string name;
	float height;
	float weight;

	Sportsman()
		: name("Ben Johnson")
	{
	}

	Sportsman(const std::string& n, float h, float w)
		: name(n)
		, height((h < 0) ? 0.0f : h)
		, weight((w < 0) ? 0.0f : w)
	{
	}
};

std::ostream& operator<<(std::ostream& os, const Sportsman& smn)
{
	os << std::fixed;
	os << std::setprecision(2);
	os << "\nSportsman:" << std::endl;
	os << "  Name: " << smn.name.c_str() << std::endl;
	os << "height: " << smn.height << " m" << std::endl;
	os << "weight: " << smn.weight << " kg\n"
	   << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Sportsman& smn)
{
	std::cout << "Enter sportsman name and press enter (emtpy string for quit):" << std::endl;
	std::string name;
	is >> std::ws;
	std::getline(is, name);
	if (name.empty())
	{
		std::cout << "Sportsmen data input complete! Thank you!" << std::endl;
		is.setstate(std::ios_base::failbit);
		return is;
	}
	else
	{
		smn.name = name;
		std::cout << "Enter sportsman height and weight with space beetween:" << std::endl;
		is >> smn.height >> smn.weight;
		std::cout << "Thank you!" << std::endl;
		while (is.get() != '\n')
		{
			continue;
		}			
	}
	
	return is;
}