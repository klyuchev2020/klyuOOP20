#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape(){};
	virtual std::uint32_t GetFillColor() const = 0;
	virtual std::uint32_t GetOutlineColor() const = 0;
};
