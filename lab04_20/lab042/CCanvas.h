#pragma once

#include "ICanvas.h"
#include "ICanvasDrawable.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(unsigned int sizeX, unsigned int sizeY, const std::string& title);
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

private:
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<ICanvasDrawable>> m_prims;
};
