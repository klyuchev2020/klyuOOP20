#include "CCanvasLogger.h"

static const float epsilon = 1e-3f;
static const float PI = 3.14159263f;

bool ApproxEqual(float one, float other)
{
	return std::abs(one - other) < epsilon;
}

bool ApproxEqualCoordWise(const std::vector<float>& vec1, const std::vector<float>& vec2)
{
	if (vec1.size() != vec2.size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < vec1.size(); ++i)
		{
			if (!ApproxEqual(vec1[i], vec2[i]))
			{
				return false;
			}
		}
		return true;
	}
}

PrimitiveLog::PrimitiveLog(const PrimType& pt, const std::vector<float>& fInitials,
	const std::vector<float>& ptsX, const std::vector<float>& ptsY, const std::vector<std::uint32_t>& colors)
	: type(pt)
	, pointsX(ptsX)
	, pointsY(ptsY)
{
	if (fInitials.size() != 7 || colors.size() != 2)
	{
		throw std::invalid_argument("Wrong log elements number");
	}
	positionX = fInitials[0];
	positionY = fInitials[1];
	width = fInitials[2];
	height = fInitials[3];
	radius = fInitials[4];
	thickness = fInitials[5];
	rotation = fInitials[6];
	outlineColor = colors[0];
	fillColor = colors[1];
}

bool operator==(const PrimitiveLog& log1, const PrimitiveLog& log2)
{
	switch (log1.type)
	{
	case PrimType::SFMLRectangle:
		return (log2.type == PrimType::SFMLRectangle) && ApproxEqual(log1.positionX, log2.positionX)
			&& ApproxEqual(log1.positionY, log2.positionY) && ApproxEqual(log1.width, log2.width)
			&& ApproxEqual(log1.height, log2.height) && ApproxEqual(log1.rotation, log2.rotation) 
			&& (log1.fillColor == log2.fillColor);
	case PrimType::SFMLCircle:
		return (log2.type == PrimType::SFMLCircle) && ApproxEqual(log1.positionX, log2.positionX)
			&& ApproxEqual(log1.positionY, log2.positionY) && ApproxEqual(log1.radius, log2.radius)
			&& ApproxEqual(log1.thickness, log2.thickness) && (log1.fillColor == log2.fillColor) 
			&& (log1.outlineColor == log2.outlineColor);
	case PrimType::SFMLConvex:
		return (log2.type == PrimType::SFMLConvex) && ApproxEqualCoordWise(log1.pointsX, log2.pointsX)
			&& ApproxEqualCoordWise(log1.pointsY, log2.pointsY) && (log1.fillColor == log2.fillColor);
	default:
		std::cout << "Unknown ptimitive type" << std::endl;
		return false;
	}
}

void CCanvasLogger::DrawLine(CPoint const& startPoint, CPoint const& endPoint,
	const std::uint32_t outlineColor)
{
	PrimType pt = PrimType::SFMLRectangle;

	std::vector<float> fInits(7, 0.0f);
	fInits[0] = static_cast<float>(startPoint.GetX());
	fInits[1] = static_cast<float>(startPoint.GetY());
	fInits[2] = static_cast<float>(CalcDistance(startPoint, endPoint));
	fInits[3] = 1.0f;
	const float angle = static_cast<float>(std::atan2(endPoint.GetY() - startPoint.GetY(), endPoint.GetX() - startPoint.GetX()));
	fInits[6] = angle * 180 / PI;

	std::vector<float> ptsX;
	std::vector<float> ptsY;

	std::vector<std::uint32_t> colors;
	colors.push_back(0);
	colors.push_back(outlineColor);

	PrimitiveLog log(pt, fInits, ptsX, ptsY, colors);

	m_primLogs.push_back(log);
}

void CCanvasLogger::DrawCircle(CPoint const& centerPoint, double radius,
	const std::uint32_t outlineColor)
{
	PrimType pt = PrimType::SFMLCircle;

	std::vector<float> fInits(7, 0.0f);
	fInits[0] = static_cast<float>(centerPoint.GetX() - radius);
	fInits[1] = static_cast<float>(centerPoint.GetY() - radius);
	fInits[4] = static_cast<float>(radius);
	fInits[5] = 2.0f;
	
	std::vector<float> ptsX;
	std::vector<float> ptsY;

	std::vector<std::uint32_t> colors;
	colors.push_back(outlineColor);
	colors.push_back(0x000000FF);

	PrimitiveLog log(pt, fInits, ptsX, ptsY, colors);

	m_primLogs.push_back(log);
}

void CCanvasLogger::FillPolygon(std::vector<CPoint> const& points,
	const std::uint32_t fillColor)
{
	PrimType pt = PrimType::SFMLConvex;

	std::vector<float> fInits(7, 0.0f);
	std::vector<float> ptsX;
	std::vector<float> ptsY;

	size_t pointsNumber = points.size();

	if (pointsNumber < 3)
	{
		return;
	}
	else
	{
		for (size_t n = 0; n < pointsNumber; ++n)
		{
			ptsX.push_back(static_cast<float>(points[n].GetX()));
			ptsY.push_back(static_cast<float>(points[n].GetY()));
		}
	}
	
	std::vector<std::uint32_t> colors;
	colors.push_back(0);
	colors.push_back(fillColor);

	PrimitiveLog log(pt, fInits, ptsX, ptsY, colors);

	m_primLogs.push_back(log);
}

void CCanvasLogger::FillCircle(CPoint const& centerPoint, double radius,
	const std::uint32_t fillColor)
{
	PrimType pt = PrimType::SFMLCircle;

	std::vector<float> fInits(7, 0.0f);
	fInits[0] = static_cast<float>(centerPoint.GetX() - radius);
	fInits[1] = static_cast<float>(centerPoint.GetY() - radius);
	fInits[4] = static_cast<float>(radius);
	fInits[5] = 0.0f;

	std::vector<float> ptsX;
	std::vector<float> ptsY;

	std::vector<std::uint32_t> colors;
	colors.push_back(fillColor);
	colors.push_back(fillColor);

	PrimitiveLog log(pt, fInits, ptsX, ptsY, colors);

	m_primLogs.push_back(log);
}

void CCanvasLogger::SetPicture(std::vector<std::unique_ptr<ICanvasDrawable>>& prims)
{
	for (size_t i = 0; i < prims.size(); ++i)
	{
		m_prims.push_back(std::move(prims[i]));
	}
}

void CCanvasLogger::Display()
{
	for (const auto& primitive : m_prims)
	{
		primitive->Draw(*this);
	}
}

const PrimitiveLog& CCanvasLogger::GetLog(size_t n) const
{
	return m_primLogs[n];
}