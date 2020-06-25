#include "CCanvas.h"
#include "CPoint.h"

const double PI = 3.14159263;

CCanvas::CCanvas(size_t sizeX, size_t sizeY, const std::string& title)
{
	sf::VideoMode videoMode(sizeX, sizeY);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window.create(videoMode, title, sf::Style::Default, settings);
}


void CCanvas::DrawLine(CPoint const& startPoint, CPoint const& endPoint,
	const std::string& outlineColor)
{
	float width = CalcDistance(startPoint, endPoint);
	float height = 1.0f;
	float angle = std::atan2(endPoint.GetY() - startPoint.GetY(), endPoint.GetX() - startPoint.GetX());
	sf::Vector2f size(width, height);
	sf::RectangleShape line(size);
	line.setPosition(sf::Vector2f(float(startPoint.GetX()), float(startPoint.GetY())));
	line.rotate(angle * 180/PI);
	line.setFillColor(sf::Color(0, 0xFF, 0xFF));
	m_window.draw(line);
}

void CCanvas::DrawCircle(CPoint const& centerPoint, double radius,
	const std::string& outlineColor)
{
	sf::CircleShape circle(radius, 200);
	circle.setPosition(float(centerPoint.GetX()), float(centerPoint.GetY()));
	circle.setFillColor(sf::Color(0, 0, 0));
	circle.setOutlineThickness(2.0f);
	circle.setOutlineColor(sf::Color(0xFF, 0xFF, 0xFF));
	
	m_window.draw(circle);
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points,
	const std::string& fillColor)
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
			polygon.setPoint(n, sf::Vector2f(float(points[n].GetX()), float(points[n].GetY())));
		}
		polygon.setFillColor(sf::Color::Red);
		m_window.draw(polygon);
	}

}

void CCanvas::FillCircle(CPoint const& centerPoint, double radius,
	const std::string& fillColor)
{
	sf::CircleShape circle(radius, 200);
	circle.setPosition(float(centerPoint.GetX()), float(centerPoint.GetY()));
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(2.0f);
	circle.setOutlineColor(sf::Color(0xFF, 0xFF, 0xFF));

	m_window.draw(circle);
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
		DrawLine(CPoint(10.0, 200.0), CPoint(100.0, 10.0), "");
		DrawCircle(CPoint(50.0, 150.0), 100.0, "");
		std::vector<CPoint> pts = { 
			CPoint(10.0f, 20.0f), 
			CPoint(100.0f, 150.0f), 
			CPoint(140.0f, 30.0f), 
			CPoint(120.0f, 50.0f) };
		FillPolygon(pts, "");
		FillCircle(CPoint(150.0, 250.0), 70.0, "");

	    m_window.display();
	}
}