#pragma once

#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint const& vert1, CPoint const& vert2, CPoint const& vert3,
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::string GetOutlineColor() const; // цвет контура
	std::string GetFillcolor() const; // цвет заливки
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	static std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_vert1;
	CPoint m_vert2;
	CPoint m_vert3;
};