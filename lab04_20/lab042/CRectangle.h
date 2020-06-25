#pragma once

#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint const& leftTop, double width, double height,
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::string GetOutlineColor() const; // цвет контура
	std::string GetFillcolor() const; // цвет заливки
	CPoint GetLeftTop() const; // левая верхняя вершина
	CPoint GetRightBottom() const; // правая нижняя вершина
	double GetWidth() const; // ширина
	double GetHeight() const; // высота
private:
	static std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

