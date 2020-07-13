#pragma once

#include "stdafx.h"
#include "CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas(){};
	virtual void DrawLine(CPoint const& startPoint, CPoint const& endPoint,
		const std::uint32_t outlineColor) = 0;
	virtual void DrawCircle(CPoint const& centerPoint, double radius,
		const std::uint32_t outlineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> const& points, 
		const std::uint32_t fillColor) = 0;
	virtual void FillCircle(CPoint const& centerPoint, double radius,
		const std::uint32_t fillColor) = 0;
	
};
