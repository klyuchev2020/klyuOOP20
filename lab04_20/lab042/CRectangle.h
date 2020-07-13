#pragma once

#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
	CRectangle(CPoint const& leftTop, double width, double height,
		const std::uint32_t outlineColor, const std::uint32_t fillColor);
	double GetArea() const; // ������� ������
	double GetPerimeter() const; // �������� ������
	std::string ToString() const; // �������� ������
	std::uint32_t GetOutlineColor() const; // ���� �������
	std::uint32_t GetFillColor() const; // ���� �������
	CPoint GetLeftTop() const; // ����� ������� �������
	CPoint GetRightBottom() const; // ������ ������ �������
	double GetWidth() const; // ������
	double GetHeight() const; // ������
	void Draw(ICanvas& canvas) const;

private:
	static std::string m_type;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

