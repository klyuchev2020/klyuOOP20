#pragma once

#include "ICanvas.h"

class ICanvasDrawable // то, что можно нарисовать на холсте
{
public:
	virtual ~ICanvasDrawable(){};
	virtual std::string ToString() const = 0; // описание фигуры
	virtual void Draw(ICanvas& canvas) const = 0;
};
