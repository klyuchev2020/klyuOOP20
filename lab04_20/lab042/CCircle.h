#pragma once

#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint const& center, double radius,
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::string GetOutlineColor() const; // цвет контура
	std::string GetFillcolor() const; // цвет заливки
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	static std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_center;
	double m_radius;
};