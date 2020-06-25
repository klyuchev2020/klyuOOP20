#pragma once

#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(size_t sizeX, size_t sizeY, const std::string& title);
	void DrawLine(CPoint const& startPoint, CPoint const& endPoint,
		const std::string& outlineColor);
	void DrawCircle(CPoint const& centerPoint, double radius,
		const std::string& outlineColor);
	void FillPolygon(std::vector<CPoint> const& points,
		const std::string& fillColor);
	void FillCircle(CPoint const& centerPoint, double radius,
		const std::string& fillColor);
	void Display();

private:
	sf::RenderWindow m_window;
};
