#include "CCanvas.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

const double PI = 3.14159263;

CCanvas::CCanvas(unsigned int sizeX, unsigned int sizeY, const std::string& title)
{
	sf::VideoMode videoMode(sizeX, sizeY);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window.create(videoMode, title, sf::Style::Default, settings);
}


void CCanvas::DrawLine(CPoint const& startPoint, CPoint const& endPoint,
	const std::uint32_t outlineColor)
{
	const float width = static_cast<float>(CalcDistance(startPoint, endPoint));
	const float height = 1.0f;
	const float angle = static_cast<float>(std::atan2(endPoint.GetY() - startPoint.GetY(), endPoint.GetX() - startPoint.GetX()));

	sf::Vector2f size(width, height);
	sf::RectangleShape line(size);

	line.setPosition(sf::Vector2f(static_cast<float>(startPoint.GetX()), static_cast<float>(startPoint.GetY())));
	line.rotate(float(angle * 180/PI));
	line.setFillColor(sf::Color(outlineColor));
	
	m_window.draw(line);
}

void CCanvas::DrawCircle(CPoint const& centerPoint, double radius,
	const std::uint32_t outlineColor)
{
	sf::CircleShape circle(float(radius), 200);

	circle.setPosition(static_cast<float>(centerPoint.GetX() - radius), static_cast<float>(centerPoint.GetY() - radius));
	circle.setFillColor(sf::Color(0x000000FF));
	circle.setOutlineThickness(2.0f);
	circle.setOutlineColor(sf::Color(outlineColor));
	
	m_window.draw(circle);
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points,
	const std::uint32_t fillColor)
{
	size_t pointsNumber = points.size();

	if (pointsNumber < 3)
	{
		return;
	}
	else
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(pointsNumber);
		for (size_t n = 0; n < pointsNumber; ++n)
		{
			polygon.setPoint(n, sf::Vector2f(static_cast<float>(points[n].GetX()), static_cast<float>(points[n].GetY())));
		}
		polygon.setFillColor(sf::Color(fillColor));
		
		m_window.draw(polygon);
	}
}

void CCanvas::FillCircle(CPoint const& centerPoint, double radius,
	const std::uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius), 200);

	circle.setPosition(static_cast<float>(centerPoint.GetX() - radius), static_cast<float>(centerPoint.GetY() - radius));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineThickness(0.0f);
	circle.setOutlineColor(sf::Color(fillColor));

	m_window.draw(circle);
}

void CCanvas::SetPicture(std::vector<std::unique_ptr<ICanvasDrawable>>& prims)
{
	for (size_t i = 0; i < prims.size(); ++i)
	{
		m_prims.push_back(std::move(prims[i]));
	}
}

void CCanvas::Display()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}
		m_window.clear();
		for (const auto& primitive : m_prims)
		{
			primitive->Draw(*this);
		}
		m_window.display();
	}	
}
