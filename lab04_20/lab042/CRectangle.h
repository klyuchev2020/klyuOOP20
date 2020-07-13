#pragma once

#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
	CRectangle(CPoint const& leftTop, double width, double height,
		const std::uint32_t outlineColor, const std::uint32_t fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::uint32_t GetOutlineColor() const; // цвет контура
	std::uint32_t GetFillColor() const; // цвет заливки
	CPoint GetLeftTop() const; // левая верхняя вершина
	CPoint GetRightBottom() const; // правая нижняя вершина
	double GetWidth() const; // ширина
	double GetHeight() const; // высота
	void Draw(ICanvas& canvas) const;

private:
	static std::string m_type;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

