#pragma once

#include "ICanvas.h"

class ICanvasDrawable // ��, ��� ����� ���������� �� ������
{
public:
	virtual ~ICanvasDrawable(){};
	virtual std::string ToString() const = 0; // �������� ������
	virtual void Draw(ICanvas& canvas) const = 0;
};
