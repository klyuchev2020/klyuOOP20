#pragma once

#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CTriangle : public ISolidShape, public ICanvasDrawable
{
public:
	CTriangle(CPoint const& vert1, CPoint const& vert2, CPoint const& vert3,
		const std::uint32_t outlineColor, const std::uint32_t fillColor);
	double GetArea() const; // ������� ������
	double GetPerimeter() const; // �������� ������
	std::string ToString() const; // �������� ������
	std::uint32_t GetOutlineColor() const; // ���� �������
	std::uint32_t GetFillColor() const; // ���� �������
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const;

private:
	static std::string m_type;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
	CPoint m_vert1;
	CPoint m_vert2;
	CPoint m_vert3;
};