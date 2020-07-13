#pragma once

#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CCircle : public ISolidShape, public ICanvasDrawable
{
public:
	CCircle(CPoint const& center, double radius,
		const std::uint32_t outlineColor, const std::uint32_t fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::uint32_t GetOutlineColor() const; // цвет контура
	std::uint32_t GetFillColor() const; // цвет заливки
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const;

private:
	static std::string m_type;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
	CPoint m_center;
	double m_radius;
};