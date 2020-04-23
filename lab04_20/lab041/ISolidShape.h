#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape(){};
	virtual std::string GetFillcolor() const = 0;
	virtual std::string GetOutlineColor() const = 0;
};
