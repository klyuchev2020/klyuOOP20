#pragma once

#include "ICanvas.h"

class ICanvasDrawable // то, что можно нарисовать на холсте
{
public:
	virtual ~ICanvasDrawable(){};
	virtual void Draw(ICanvas& canvas) = 0;
};
