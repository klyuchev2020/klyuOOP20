#include "stdafx.h"
#include "CTriangle.h"
#include "CLineSegment.h"

const std::string m_type = "Triangle";

CTriangle::CTriangle(CPoint const& vert1, CPoint const& vert2, CPoint const& vert3,
	const std::uint32_t outlineColor, const std::uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_vert1(vert1)
	, m_vert2(vert2)
	, m_vert3(vert3)
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_vert1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vert2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vert3;
}

std::uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

double CTriangle::GetPerimeter() const
{
	return CalcDistance(m_vert1, m_vert2) + CalcDistance(m_vert2, m_vert3) + CalcDistance(m_vert3, m_vert1);
}

double CTriangle::GetArea() const
{
	CLineSegment side2(m_vert1, m_vert2);
	CLineSegment side3(m_vert1, m_vert3);
	CPoint side2Rad = side2.GetRadVector();
	CPoint side3Rad = side3.GetRadVector();

	return 0.5 * abs(side2Rad.GetX() * side3Rad.GetY() - side2Rad.GetY() * side3Rad.GetX());
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;

	strm << "\tShape type is Triangle" << std::endl
		 << "\tOutline color is " << m_outlineColor << std::endl
		 << "\tFill color is " << m_fillColor << std::endl
		 << "\tVertex 1 is (" << m_vert1.GetX() << ", " << m_vert1.GetY() << ")" << std::endl
		 << "\tVertex 2 is (" << m_vert2.GetX() << ", " << m_vert2.GetY() << ")" << std::endl
		 << "\tVertex 3 is (" << m_vert3.GetX() << ", " << m_vert3.GetY() << ")" << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tArea = " << GetArea() << std::endl;

	return strm.str();
}


void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> vertices = { m_vert1, m_vert2, m_vert3 };
	canvas.FillPolygon(vertices, m_fillColor);
	canvas.DrawLine(m_vert1, m_vert2, m_outlineColor);
	canvas.DrawLine(m_vert2, m_vert3, m_outlineColor);
	canvas.DrawLine(m_vert3, m_vert1, m_outlineColor);
}
