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
#include "ICanvasDrawable.h"
#include "CCanvas.h"

static const std::vector<std::string> shapeNames = { std::string("LineSegment"), std::string("Circle"), std::string("Triangle"), std::string("Rectangle") };

std::unique_ptr<ICanvasDrawable> SegmentInit(std::stringstream& segmentParams)
{
	double startPX = 0.0;
	double startPY = 0.0;
	double endPX = 0.0;
	double endPY = 0.0;
	std::uint32_t outlineC(0xFFFFFFFF);

	segmentParams >> startPX >> startPY >> endPX >> endPY >> std::hex >> outlineC;
	CPoint startP = CPoint(startPX, startPY);
	CPoint endP = CPoint(endPX, endPY);
	auto lsPtr = std::make_unique<CLineSegment>(startP, endP, outlineC);
	return std::move(lsPtr);
}

std::unique_ptr<ICanvasDrawable> CircleInit(std::stringstream& circleParams)
{
	double centerX = 0.0;
	double centerY = 0.0;
	double radius = 0.0;
	std::uint32_t outlineC(0xFFFFFFFF);
	std::uint32_t fillC(0xFFFFFFFF);

	circleParams >> centerX >> centerY >> radius >> std::hex >> outlineC >> std::hex >> fillC;
	CPoint center = CPoint(centerX, centerY);
	auto circPtr = std::make_unique<CCircle>(center, radius, outlineC, fillC);
	return std::move(circPtr);
}

std::unique_ptr<ICanvasDrawable> TriangleInit(std::stringstream& triangleParams)
{
	double vert1X = 0.0;
	double vert1Y = 0.0;
	double vert2X = 0.0;
	double vert2Y = 0.0;
	double vert3X = 0.0;
	double vert3Y = 0.0;
	std::uint32_t outlineC(0xFFFFFFFF);
	std::uint32_t fillC(0xFFFFFFFF);

	triangleParams >> vert1X >> vert1Y >> vert2X >> vert2Y >> vert3X >> vert3Y >> std::hex >> outlineC >> std::hex >> fillC;
	CPoint vert1 = CPoint(vert1X, vert1Y);
	CPoint vert2 = CPoint(vert2X, vert2Y);
	CPoint vert3 = CPoint(vert3X, vert3Y);
	auto trngPtr = std::make_unique<CTriangle>(vert1, vert2, vert3, outlineC, fillC);
	return std::move(trngPtr);
}

std::unique_ptr<ICanvasDrawable> RectangleInit(std::stringstream& rectangleParams)
{
	double leftTopX = 0.0;
	double leftTopY = 0.0;
	double width = 0.0;
	double height = 0.0;
	std::uint32_t outlineC(0xFFFFFFFF);
	std::uint32_t fillC(0xFFFFFFFF);

	rectangleParams >> leftTopX >> leftTopY >> width >> height >> std::hex >> outlineC >> std::hex >> fillC;
	CPoint leftTop = CPoint(leftTopX, leftTopY);
	auto rctgPtr = std::make_unique<CRectangle>(leftTop, width, height, outlineC, fillC);
	return std::move(rctgPtr);
}

std::unique_ptr<ICanvasDrawable> GetShape(std::string const& shapeDescription, std::vector<std::string> const& shapeNames)
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

std::unique_ptr<ICanvasDrawable> NextShapeInCollection(std::istream& istrm)
{
	std::string shapeDescription;
	getline(istrm, shapeDescription);

	return std::move(GetShape(shapeDescription, shapeNames));
}

void PrintHelp()
{
	std::cout << "Here we input shape collection.\n"
			  << "Each the shape description holds single line with format:\n"
			  << "For Segment Line: \"SegmentLine  first_point_x first_point_y second_point_x second_point_y outline_color\"\n"
			  << "For Circle:  \"Circle center_x center_y radius outline_color fill_color\"\n"
			  << "For Triangle: \"Triangle first_vertex_x first_vertex_y second_vertex_x second_vertex_y third_vertex_x third_vertex_y outline_color fill_color\"\n"
			  << "For Rectangle: \"Rectangle left_top_vertex_x left_top_vertex_y width height outline_color fill_color\"\n"
			  << std::endl;
}

int main()
{
	std::vector<std::unique_ptr<ICanvasDrawable>> shapesSequence;
	PrintHelp();

	size_t counter = 0;
	while (auto shape = NextShapeInCollection(std::cin))
	{
		shapesSequence.push_back(std::move(shape));
		counter++;
	}
	std::cout << counter << " figures overall" << std::endl;

	if (shapesSequence.size() != 0)
	{
		CCanvas canvas(500, 400, "test canvas");
		canvas.SetPicture(shapesSequence);
		canvas.Display();
	}
	else
	{
		std::cout << "There are no shapes at all!" << std::endl;
	}

	return 0;
}

