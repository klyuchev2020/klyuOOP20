#include "stdafx.h"
#include "CCircle.h"

const std::string m_type = "Circle";
static const double PI = 3.141592653;

CCircle::CCircle(CPoint const& center, double radius,
	const std::uint32_t outlineColor, const std::uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_center(center)
{
	m_radius = (radius > 0) ? radius : 0.0;
}

double CCircle::GetArea() const
{
	return PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2.0 * PI * m_radius;
}

std::uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;

	strm << "\tShape type is Circle" << std::endl
		 << "\tOutline color is " << m_outlineColor << std::endl
		 << "\tFill color is " << m_fillColor << std::endl
		 << "\tcenter is at point (" << m_center.GetX() << ", " << m_center.GetY() << ")" << std::endl
		 << "\tradius is " << m_radius << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tArea = " << GetArea() << std::endl;

	return strm.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);	
}