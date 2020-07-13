#include "stdafx.h"
#include "CRectangle.h"

const std::string m_type = "Rectangle";

CRectangle::CRectangle(CPoint const& leftTop, double width, double height,
	const std::uint32_t outlineColor, const std::uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_leftTop(leftTop)
{
	m_width = (width > 0) ? width : 0.0;
	m_height = (height > 0) ? height : 0.0;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2.0 * (m_width + m_height);
}

std::uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	double xRB = m_leftTop.GetX() + m_width;
	double yRB = m_leftTop.GetY() + m_height;

	return CPoint(xRB, yRB);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;

	strm << "\tShape type is Rectangle" << std::endl
		 << "\tOutline color is " << m_outlineColor << std::endl
		 << "\tFill color is " << m_fillColor << std::endl
		 << "\tLeft top vertex is (" << m_leftTop.GetX() << ", " << m_leftTop.GetY() << ")" << std::endl
		 << "\twidth is " << m_width << std::endl
		 << "\theight is " << m_height << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tArea = " << GetArea() << std::endl;

	return strm.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint lt = m_leftTop;
	CPoint rb = GetRightBottom();
	CPoint lb = CPoint(lt.GetX(), rb.GetY());
	CPoint rt = CPoint(rb.GetX(), lt.GetY());
	std::vector<CPoint> vertices = { lt, lb, rb, rt };
	canvas.FillPolygon(vertices, m_fillColor);
	canvas.DrawLine(lt, lb, m_outlineColor);
	canvas.DrawLine(lb, rb, m_outlineColor);
	canvas.DrawLine(rb, rt, m_outlineColor);
	canvas.DrawLine(rt, lt, m_outlineColor);
}