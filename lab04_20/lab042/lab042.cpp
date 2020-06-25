// lab042.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include "ISolidShape.h"
#include "CCanvas.h"

static const std::vector<std::string> shapeNames = { std::string("LineSegment"), std::string("Circle"), std::string("Triangle"), std::string("Rectangle") };

std::unique_ptr<IShape> SegmentInit(std::stringstream& segmentParams)
{
	double startPX = 0.0;
	double startPY = 0.0;
	double endPX = 0.0;
	double endPY = 0.0;
	std::string outlineC("ff0000");

	segmentParams >> startPX >> startPY >> endPX >> endPY >> outlineC;
	CPoint startP = CPoint(startPX, startPY);
	CPoint endP = CPoint(endPX, endPY);
	auto lsPtr = std::make_unique<CLineSegment>(startP, endP, outlineC);
	return std::move(lsPtr);
}

std::unique_ptr<IShape> CircleInit(std::stringstream& circleParams)
{
	double centerX = 0.0;
	double centerY = 0.0;
	double radius = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	circleParams >> centerX >> centerY >> radius >> outlineC >> fillC;
	CPoint center = CPoint(centerX, centerY);
	auto circPtr = std::make_unique<CCircle>(center, radius, outlineC, fillC);
	return std::move(circPtr);
}

std::unique_ptr<IShape> TriangleInit(std::stringstream& triangleParams)
{
	double vert1X = 0.0;
	double vert1Y = 0.0;
	double vert2X = 0.0;
	double vert2Y = 0.0;
	double vert3X = 0.0;
	double vert3Y = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	triangleParams >> vert1X >> vert1Y >> vert2X >> vert2Y >> vert3X >> vert3Y >> outlineC >> fillC;
	CPoint vert1 = CPoint(vert1X, vert1Y);
	CPoint vert2 = CPoint(vert2X, vert2Y);
	CPoint vert3 = CPoint(vert3X, vert3Y);
	auto trngPtr = std::make_unique<CTriangle>(vert1, vert2, vert3, outlineC, fillC);
	return std::move(trngPtr);
}

std::unique_ptr<IShape> RectangleInit(std::stringstream& rectangleParams)
{
	double leftTopX = 0.0;
	double leftTopY = 0.0;
	double width = 0.0;
	double height = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	rectangleParams >> leftTopX >> leftTopY >> width >> height >> outlineC >> fillC;
	CPoint leftTop = CPoint(leftTopX, leftTopY);
	auto rctgPtr = std::make_unique<CRectangle>(leftTop, width, height, outlineC, fillC);
	return std::move(rctgPtr);
}

std::unique_ptr<IShape> GetShape(std::string const& shapeDescription, std::vector<std::string> const& shapeNames)
{
	std::stringstream inputLine(shapeDescription);
	std::string sName;
	inputLine >> sName;

	auto it = std::find(shapeNames.begin(), shapeNames.end(), sName);
	if (it == shapeNames.end())
	{
		return nullptr;
	}

	if (*it == "LineSegment")
	{
		return SegmentInit(inputLine);
	}
	if (*it == "Circle")
	{
		return CircleInit(inputLine);
	}
	if (*it == "Triangle")
	{
		return TriangleInit(inputLine);
	}
	if (*it == "Rectangle")
	{
		return RectangleInit(inputLine);
	}
	return nullptr;
}

std::unique_ptr<IShape> NextShapeInCollection(std::istream& istrm)
{
	std::string shapeDescription;
	getline(istrm, shapeDescription);

	return std::move(GetShape(shapeDescription, shapeNames));
}

int main()
{
	CCanvas canvas(300, 400, "test canvas");
	canvas.Display();
}

