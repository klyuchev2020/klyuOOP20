#pragma once

class CPoint
{
public:
	CPoint() = default;
	CPoint(double x, double y);
	double GetX() const;
	double GetY() const;

private:
	double m_x = 0.0;
	double m_y = 0.0;
};

double CalcDistance(CPoint const& a, CPoint const& b);
bool ApproxEq(CPoint const& a, CPoint const& b); // расстояние между точками a и b меньше epsilon