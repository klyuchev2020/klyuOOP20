#pragma once

#include "CPoint.h"
#include "IShape.h"
#include "ICanvasDrawable.h"

class CLineSegment : public IShape, public ICanvasDrawable
{
public:
	CLineSegment(CPoint const& startPoint, CPoint const& endPoint,
		const std::uint32_t outlineColor = 0xFFFFFFFF);
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	std::uint32_t GetOutlineColor() const;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	CPoint GetRadVector() const;
	void Draw(ICanvas& canvas) const;

private:
	static std::string m_type;
	std::uint32_t m_outlineColor;
	CPoint m_startP;
	CPoint m_endP;
};
