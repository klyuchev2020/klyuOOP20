#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

CPoint::CPoint(CPoint const& punkt)
	: m_x(punkt.m_x)
	, m_y(punkt.m_y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

double CalcDistance(CPoint const& a, CPoint const& b) // расстояние между точками меньше epsilon
{
	return std::pow(std::pow(a.GetX() - b.GetX(), 2.0) + std::pow(a.GetY() - b.GetY(), 2.0), 0.5);
}

bool ApproxEq(CPoint const& a, CPoint const& b) // расстояние между точками меньше epsilon
{
	return CalcDistance(a, b) < epsilon;
}