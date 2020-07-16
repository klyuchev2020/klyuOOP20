#include "stdafx.h"
#include "../lab042/IShape.h"
#include "../lab042/ISolidShape.h"
#include "../lab042/ICanvas.h"
#include "../lab042/ICanvasDrawable.h"
#include "../lab042/CPoint.h"
#include "../lab042/CLineSegment.h"
#include "../lab042/CCircle.h"
#include "../lab042/CTriangle.h"
#include "../lab042/CRectangle.h"
#include "CCanvasLogger.h"


TEST_CASE("Can compare two PrimitiveLogs both rectangles")
{
	PrimType t1 = PrimType::SFMLRectangle;
	const std::vector<float> fInits1 = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f };
	const std::vector<float> ptsX1;
	const std::vector<float> ptsY1;
	const std::vector<std::uint32_t> colors1 = { 0x89ABCDEF, 0xAABBCCDD };
	
	PrimitiveLog rectLog1(t1, fInits1, ptsX1, ptsY1, colors1);

	PrimType t2 = PrimType::SFMLRectangle;
	const std::vector<float> fInits2 = { 10.0001f, 20.000078f, 29.999989f, 40.000013f, 500.0f, 59.99995f, 70.00003f };
	const std::vector<float> ptsX2;
	const std::vector<float> ptsY2;
	const std::vector<std::uint32_t> colors2 = { 0x89ABCDEF, 0xAABBCCDD };

	PrimitiveLog rectLog2(t2, fInits2, ptsX2, ptsY2, colors2);
	CHECK(rectLog1 == rectLog2);

	PrimType t3 = PrimType::SFMLRectangle;
	const std::vector<float> fInits3 = { 10.0021f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f };
	const std::vector<float> ptsX3;
	const std::vector<float> ptsY3;
	const std::vector<std::uint32_t> colors3 = { 0x89ABCDEF, 0xAABBCCDD };

	PrimitiveLog rectLog3(t3, fInits3, ptsX3, ptsY3, colors3);
	CHECK(!(rectLog1 == rectLog3));

	PrimitiveLog rectLog4 = rectLog1;
	CHECK(rectLog4 == rectLog1);

	rectLog4.positionY = 19.995f;
	CHECK(!(rectLog4 == rectLog1));

	rectLog4 = rectLog1;
	rectLog4.width = 30.002f;
	CHECK(!(rectLog4 == rectLog1));

	rectLog4 = rectLog1;
	rectLog4.height = 39.9985f;
	CHECK(!(rectLog4 == rectLog1));

	rectLog4 = rectLog1;
	rectLog4.thickness = 600.0f;
	CHECK(rectLog4 == rectLog1);

	rectLog4 = rectLog1;
	rectLog4.rotation = 70.0011f;
	CHECK(!(rectLog4 == rectLog1));

	rectLog4 = rectLog1;
	rectLog4.pointsX.push_back(5.0f);
	rectLog4.pointsY.push_back(-15.0f);
	CHECK(rectLog4 == rectLog1);

	rectLog4 = rectLog1;
	rectLog4.outlineColor = 0x89ABCDE0;
	CHECK(rectLog4 == rectLog1);

	rectLog4 = rectLog1;
	rectLog4.fillColor = 0xAABBCCD0;
	CHECK(!(rectLog4 == rectLog1));

}

TEST_CASE("Can compare two Circles")
{
	PrimType t1 = PrimType::SFMLCircle;
	const std::vector<float> fInits1 = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f };
	const std::vector<float> ptsX1;
	const std::vector<float> ptsY1;
	const std::vector<std::uint32_t> colors1 = { 0x12345678, 0xFEDCBA98 };
	/*
	набор fInits1 содержит в указанном порядке: 
	positionX, positionY, width, height, radius, thickness, rotation
	*/
	PrimitiveLog circLog1(t1, fInits1, ptsX1, ptsY1, colors1);

	PrimType t2 = PrimType::SFMLCircle;
	const std::vector<float> fInits2 = { 10.00091f, 19.99998f, 100.0f, 400.0f, 50.00078f, 59.99997f, 1000.00003f };
	const std::vector<float> ptsX2 = { 49.0f, 23.9f };
	const std::vector<float> ptsY2 = { -89.0f, 32.0f };
	const std::vector<std::uint32_t> colors2 = { 0x12345678, 0xFEDCBA98 };

	PrimitiveLog circLog2(t2, fInits2, ptsX2, ptsY2, colors2);
	CHECK(circLog1 == circLog2);

	PrimitiveLog circLog3 = circLog1;
	circLog3.positionX = 10.0011f;
	CHECK(!(circLog3 == circLog1));

	circLog3 = circLog1;
	circLog3.positionY = 19.998f;
	CHECK(!(circLog3 == circLog1));

	circLog3 = circLog1;
	circLog3.width = 1000.8f;
	CHECK(circLog3 == circLog1);

	circLog3 = circLog1;
	circLog3.height = 2000.18f;
	CHECK(circLog3 == circLog1);

	circLog3 = circLog1;
	circLog3.radius = 50.00101f;
	CHECK(!(circLog3 == circLog1));

	circLog3 = circLog1;
	circLog3.thickness = 59.99899f;
	CHECK(!(circLog3 == circLog1));

	circLog3 = circLog1;
	circLog3.rotation = 123.456f;
	CHECK(circLog3 == circLog1);

	circLog3 = circLog1;
	circLog3.pointsX.push_back(1.5f);
	circLog3.pointsY.push_back(-34.7f);
    CHECK(circLog3 == circLog1);

	circLog3 = circLog1;
	circLog3.outlineColor = 0x12345676;
	CHECK(!(circLog3 == circLog1));

	circLog3 = circLog1;
	circLog3.fillColor = 0xFEDCBA08;
	CHECK(!(circLog3 == circLog1));
}


TEST_CASE("Can compare two ConvexShapes")
{
	PrimType t1 = PrimType::SFMLConvex;
	const std::vector<float> fInits1 = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f };
	const std::vector<float> ptsX1 = { 12.0f, 34.0f, 56.0f };
	const std::vector<float> ptsY1 = { -11.0f, -22.0f, -33.0f };
	const std::vector<std::uint32_t> colors1 = { 0x12345678, 0xFEDCBA98 };
	/*
	набор fInits1 содержит в указанном порядке: 
	positionX, positionY, width, height, radius, thickness, rotation
	*/
	PrimitiveLog convexLog1(t1, fInits1, ptsX1, ptsY1, colors1);

	PrimType t2 = PrimType::SFMLConvex;
	const std::vector<float> fInits2 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	const std::vector<float> ptsX2 = { 12.0009f, 33.9998f, 56.000045f };
	const std::vector<float> ptsY2 = { -10.9999f, -22.00095f, -32.9996f };
	const std::vector<std::uint32_t> colors2 = { 0x12345678, 0xFEDCBA98 };

	PrimitiveLog convexLog2(t2, fInits2, ptsX2, ptsY2, colors2);
	CHECK(convexLog1 == convexLog2);

	PrimitiveLog convexLog3 = convexLog1;
	convexLog3.pointsX.push_back(-1.0f);
	convexLog3.pointsY.push_back(3.0f);
	CHECK(!(convexLog3 == convexLog1));

	convexLog3 = convexLog1;
	convexLog3.pointsX[1] = 34.005f;
	CHECK(!(convexLog3 == convexLog1));

	convexLog3 = convexLog1;
	convexLog3.pointsY[0] = -10.998f;
	CHECK(!(convexLog3 == convexLog1));

	convexLog3 = convexLog1;
	convexLog3.outlineColor = 0;
	CHECK(convexLog3 == convexLog1);

	convexLog3 = convexLog1;
	convexLog3.fillColor = 0x0EDCBA98;
	CHECK(!(convexLog3 == convexLog1));
}

TEST_CASE("Can find out that primitives are of different types")
{
	PrimType trect = PrimType::SFMLRectangle;
	const std::vector<float> fInits = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f };
	const std::vector<float> ptsX;
	const std::vector<float> ptsY;
	const std::vector<std::uint32_t> colors = { 0x89ABCDEF, 0xAABBCCDD };

	PrimitiveLog rectLog(trect, fInits, ptsX, ptsY, colors);

	PrimType tcirc = PrimType::SFMLCircle;
	PrimType tconv = PrimType::SFMLConvex;

	PrimitiveLog circLog(tcirc, fInits, ptsX, ptsY, colors);
	PrimitiveLog convLog(tconv, fInits, ptsX, ptsY, colors);

	CHECK(!(rectLog == circLog));
	CHECK(!(circLog == convLog));
	CHECK(!(convLog == rectLog));
}

TEST_CASE("Can draw horizontal red line segment with sfml")
{
	fakeit::Mock<ICanvas> mockC;
	ICanvas& cnvs = mockC.get();
	
	CCanvasLogger logger;
	auto MockDrawLine = [&](CPoint const& startPoint, CPoint const& endPoint, const std::uint32_t outlineColor) 
	{
		logger.DrawLine(startPoint, endPoint, outlineColor);
	};

	fakeit::When(Method(mockC, DrawLine)).Do(MockDrawLine);
		
	const PrimType segType = PrimType::SFMLRectangle;
	const std::vector<float> segFInits = { 20.0f, 30.0f, 80.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	const std::vector<float> segPtsX;
	const std::vector<float> segPtsY;
	const std::vector<std::uint32_t> segColors = { 0, 0xFF0000FF };

	PrimitiveLog segExpected(segType, segFInits, segPtsX, segPtsY, segColors); // данные, которые требует SFML
	
	CPoint p1(20.0f, 30.0f);
	CPoint p2(100.0f, 30.0f);
	std::uint32_t pureRed = 0xFF0000FF;

	CLineSegment segment(p1, p2, pureRed);
	segment.Draw(cnvs);

	PrimitiveLog segmentLog(logger.GetLog(0));
	CHECK(segmentLog == segExpected); // SFML получил правильные данные для изображения через свой интерфейс
}

TEST_CASE("Can draw green line segment from (20,70) to (100, 40) with sfml")
{
	fakeit::Mock<ICanvas> mockC;
	ICanvas& cnvs = mockC.get();

	CCanvasLogger logger;
	auto MockDrawLine = [&](CPoint const& startPoint, CPoint const& endPoint, const std::uint32_t outlineColor) {
		logger.DrawLine(startPoint, endPoint, outlineColor);
	};

	fakeit::When(Method(mockC, DrawLine)).Do(MockDrawLine);

	// нарисуем зеленый отрезок с концами (20, 70) и (100, 40)
	// его длина sqrt(80^2 + 30^2) = sqrt(7300) = 85.4400
	// тангенс угла наклона -30/80 = -0.375, арктангенс равен -0.35877, в градусах 20.5560
	
	const PrimType segType = PrimType::SFMLRectangle;
	const std::vector<float> segFInits = { 20.0f, 70.0f, 85.4400f, 1.0f, 0.0f, 0.0f, -20.5560f };
	const std::vector<float> segPtsX;
	const std::vector<float> segPtsY;
	const std::vector<std::uint32_t> segColors = { 0, 0x00FF00FF };

	PrimitiveLog segExpected(segType, segFInits, segPtsX, segPtsY, segColors); // данные, которые требует SFML

	CPoint p1(20.0f, 70.0f);
	CPoint p2(100.0f, 40.0f);
	std::uint32_t pureGreen = 0x00FF00FF;

	CLineSegment segment(p1, p2, pureGreen);
	segment.Draw(cnvs);

	PrimitiveLog segmentLog(logger.GetLog(0));
	CHECK(segmentLog == segExpected); // SFML получил правильные данные для изображения через свой интерфейс
}

TEST_CASE("Can draw white circle with center (150, 260) and radius of 100 with sfml")
{
	fakeit::Mock<ICanvas> mockC;
	ICanvas& cnvs = mockC.get();

	CCanvasLogger logger;
	auto MockDrawCircle = [&](CPoint const& centerPoint, double radius, const std::uint32_t outlineColor) {
		logger.DrawCircle(centerPoint, radius, outlineColor);
	};
	auto MockFillCircle = [&](CPoint const& centerPoint, double radius, const std::uint32_t fillColor) {
		logger.FillCircle(centerPoint, radius, fillColor);
	};

	fakeit::When(Method(mockC, DrawCircle)).Do(MockDrawCircle);
	fakeit::When(Method(mockC, FillCircle)).Do(MockFillCircle);

	const PrimType circleType = PrimType::SFMLCircle;
	const std::vector<float> circ1FInits = { 50.0f, 160.0f, 0.0f, 0.0f, 100.0f, 2.0f, 0.0f };
	const std::vector<float> circ2FInits = { 50.0f, 160.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f };
	const std::vector<float> circPtsX;
	const std::vector<float> circPtsY;
	const std::vector<std::uint32_t> circ1Colors = { 0xFFFFFFFF, 0x000000FF };
	const std::vector<std::uint32_t> circ2Colors = { 0x000000FF, 0x000000FF };

	PrimitiveLog circ1Expected(circleType, circ1FInits, circPtsX, circPtsY, circ1Colors); // данные, которые требует SFML
	PrimitiveLog circ2Expected(circleType, circ2FInits, circPtsX, circPtsY, circ2Colors); // данные, которые требует SFML

	CPoint center(150.0f, 260.0f);
	double radius = 100.0;
	std::uint32_t white = 0xFFFFFFFF;
	std::uint32_t black = 0x000000FF;

	CCircle circle(center, radius, white, black);
	circle.Draw(cnvs);

	PrimitiveLog circ1Log(logger.GetLog(0));
	PrimitiveLog circ2Log(logger.GetLog(1));

	CHECK(circ1Log == circ1Expected); // SFML получил правильные данные для изображения через свой интерфейс
	CHECK(circ2Log == circ2Expected);
}

TEST_CASE("Can draw green rectangle with blue border having left top vertex (30, 50), width 150 and height 70")
{
	fakeit::Mock<ICanvas> mockC;
	ICanvas& cnvs = mockC.get();

	CCanvasLogger logger;
	auto MockDrawLine = [&](CPoint const& startPoint, CPoint const& endPoint, const std::uint32_t outlineColor) 
	{
		logger.DrawLine(startPoint, endPoint, outlineColor);
	};
	auto MockFillPolygon = [&](std::vector<CPoint> const& points,  const std::uint32_t fillColor) 
	{
		logger.FillPolygon(points, fillColor);
	};

	fakeit::When(Method(mockC, DrawLine)).AlwaysDo(MockDrawLine);
	fakeit::When(Method(mockC, FillPolygon)).Do(MockFillPolygon);

	const PrimType polygonType = PrimType::SFMLConvex;
	const std::vector<float> polyFInits(7, 0.0f);
	const std::vector<float> polyPtsX = { 30.0f, 30.0f, 180.0f, 180.0f };
	const std::vector<float> polyPtsY = { 50.0f, 120.0f, 120.0f, 50.0f };
	const std::vector<std::uint32_t> polyColors = { 0, 0x00FF00FF };
	
	PrimitiveLog polyExpected(polygonType, polyFInits, polyPtsX, polyPtsY, polyColors); // внутренность; данные, которые требует SFML

	const PrimType segType = PrimType::SFMLRectangle;
	const std::vector<float> seg1FInits = { 30.0f, 50.0f, 70.0f, 1.0f, 0.0f, 0.0f, 90.0f };
	const std::vector<float> seg2FInits = { 30.0f, 120.0f, 150.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	const std::vector<float> seg3FInits = { 180.0f, 120.0f, 70.0f, 1.0f, 0.0f, 0.0f, -90.0f };
	const std::vector<float> seg4FInits = { 180.0f, 50.0f, 150.0f, 1.0f, 0.0f, 0.0f, 180.0f };
	const std::vector<float> segPtsX;
	const std::vector<float> segPtsY;
	const std::vector<std::uint32_t> segColors = { 0, 0x0000FFFF };

	PrimitiveLog seg1Expected(segType, seg1FInits, segPtsX, segPtsY, segColors); // рамка; данные, которые требует SFML
	PrimitiveLog seg2Expected(segType, seg2FInits, segPtsX, segPtsY, segColors);
	PrimitiveLog seg3Expected(segType, seg3FInits, segPtsX, segPtsY, segColors);
	PrimitiveLog seg4Expected(segType, seg4FInits, segPtsX, segPtsY, segColors);

	CPoint leftTop(30.0f, 50.0f);
	double width = 150.0;
	double height = 70.0;
	std::uint32_t blue = 0x0000FFFF;
	std::uint32_t green = 0x00FF00FF;

	CRectangle rectangle(leftTop, width, height, blue, green);
	rectangle.Draw(cnvs);

	PrimitiveLog polyLog(logger.GetLog(0)); // внутренность
	PrimitiveLog leftLog(logger.GetLog(1));  // левая сторона
	PrimitiveLog bottomLog(logger.GetLog(2)); // нижняя сторона
	PrimitiveLog rightLog(logger.GetLog(3));  // правая сторона
	PrimitiveLog topLog(logger.GetLog(4));   // верхняя сторона

	CHECK(polyLog == polyExpected); // SFML получил правильные данные для изображения через свой интерфейс
	CHECK(leftLog == seg1Expected);
	CHECK(bottomLog == seg2Expected);
	CHECK(rightLog == seg3Expected);
	CHECK(topLog == seg4Expected);
}

TEST_CASE("Can draw white rectangle with green border having vertices (10, 140), (180, 100), (90, 20)")
{
	fakeit::Mock<ICanvas> mockC;
	ICanvas& cnvs = mockC.get();

	CCanvasLogger logger;
	auto MockDrawLine = [&](CPoint const& startPoint, CPoint const& endPoint, const std::uint32_t outlineColor) {
		logger.DrawLine(startPoint, endPoint, outlineColor);
	};
	auto MockFillPolygon = [&](std::vector<CPoint> const& points, const std::uint32_t fillColor) {
		logger.FillPolygon(points, fillColor);
	};

	fakeit::When(Method(mockC, DrawLine)).AlwaysDo(MockDrawLine);
	fakeit::When(Method(mockC, FillPolygon)).Do(MockFillPolygon);

	const PrimType polygonType = PrimType::SFMLConvex;
	const std::vector<float> polyFInits(7, 0.0f);
	const std::vector<float> polyPtsX = { 10.0f, 180.0f, 90.0f };
	const std::vector<float> polyPtsY = { 140.0f, 100.0f, 20.0f };
	const std::vector<std::uint32_t> polyColors = { 0, 0xFFFFFFFF };

	PrimitiveLog polyExpected(polygonType, polyFInits, polyPtsX, polyPtsY, polyColors); // внутренность; данные, которые требует SFML

	const PrimType segType = PrimType::SFMLRectangle;
	const std::vector<float> seg1FInits = { 10.0f, 140.0f, 174.6425f, 1.0f, 0.0f, 0.0f, -13.2405f };
	const std::vector<float> seg2FInits = { 180.0f, 100.0f, 120.4159f, 1.0f, 0.0f, 0.0f, -138.3665f };
	const std::vector<float> seg3FInits = { 90.0f, 20.0f, 144.22205f, 1.0f, 0.0f, 0.0f, 123.6901f };
	const std::vector<float> segPtsX;
	const std::vector<float> segPtsY;
	const std::vector<std::uint32_t> segColors = { 0, 0x00FF00FF };

	PrimitiveLog seg1Expected(segType, seg1FInits, segPtsX, segPtsY, segColors); // рамка; данные, которые требует SFML
	PrimitiveLog seg2Expected(segType, seg2FInits, segPtsX, segPtsY, segColors);
	PrimitiveLog seg3Expected(segType, seg3FInits, segPtsX, segPtsY, segColors);
	

	CPoint v1(10.0f, 140.0f);
	CPoint v2(180.0f, 100.0f);
	CPoint v3(90.0f, 20.0f);
	
	std::uint32_t green = 0x00FF00FF;
	std::uint32_t white = 0xFFFFFFFF;

	CTriangle triangle(v1, v2, v3, green, white);
	triangle.Draw(cnvs);

	PrimitiveLog polyLog(logger.GetLog(0)); // внутренность
	PrimitiveLog v1v2Log(logger.GetLog(1)); // сторона v1v2
	PrimitiveLog v2v3Log(logger.GetLog(2)); // сторона v2v3
	PrimitiveLog v3v1Log(logger.GetLog(3)); // сторона v3v1
	

	CHECK(polyLog == polyExpected); // SFML получил правильные данные для изображения через свой интерфейс
	CHECK(v1v2Log == seg1Expected);
	CHECK(v2v3Log == seg2Expected);
	CHECK(v3v1Log == seg3Expected);
}













