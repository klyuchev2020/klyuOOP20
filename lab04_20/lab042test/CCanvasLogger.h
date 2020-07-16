#pragma once

#include "../lab042/ICanvas.h"
#include "../lab042/ICanvasDrawable.h"
#include <SFML/Graphics.hpp>


enum class PrimType
{
	SFMLRectangle,
	SFMLCircle,
	SFMLConvex
};

struct PrimitiveLog
{
	PrimitiveLog(const PrimType& pt, const std::vector<float>& fInitials, 
		const std::vector<float>& ptsX, const std::vector<float>& ptsY, const std::vector<std::uint32_t>& colors);	
	PrimType type;
	float positionX;
	float positionY;
	float width;
	float height;
	float radius;
	float thickness;
	float rotation;
	std::vector<float> pointsX;
	std::vector<float> pointsY;
	std::uint32_t outlineColor;
	std::uint32_t fillColor;
};

bool operator==(const PrimitiveLog& log1, const PrimitiveLog& log2);


class CCanvasLogger : public ICanvas
{
public:
	void DrawLine(CPoint const& startPoint, CPoint const& endPoint,
		const std::uint32_t outlineColor = 0xFFFFFFFF);
	void DrawCircle(CPoint const& centerPoint, double radius,
		const std::uint32_t outlineColor = 0xFFFFFFFF);
	void FillPolygon(std::vector<CPoint> const& points,
		const std::uint32_t fillColor = 0xFFFFFFFF);
	void FillCircle(CPoint const& centerPoint, double radius,
		const std::uint32_t fillColor = 0xFFFFFFFF);
	void SetPicture(std::vector<std::unique_ptr<ICanvasDrawable>>& prims);
	void Display();
	const PrimitiveLog& GetLog(size_t n) const;

private:
	std::vector<PrimitiveLog> m_primLogs;
	std::vector<std::unique_ptr<ICanvasDrawable>> m_prims;
};
