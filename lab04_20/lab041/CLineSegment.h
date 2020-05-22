#pragma once

#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint const& startPoint, CPoint const& endPointY,
		const std::string& outlineColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	std::string GetOutlineColor() const;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	CPoint GetRadVector() const;

private:
	static std::string m_type;
	std::string m_outlineColor;
	CPoint m_startP;
	CPoint m_endP;
};
