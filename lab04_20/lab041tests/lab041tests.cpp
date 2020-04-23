#include "stdafx.h"
#include "../lab041/CCircle.h"
#include "../lab041/CLineSegment.h"
#include "../lab041/CPoint.h"
#include "../lab041/CRectangle.h"
#include "../lab041/CTriangle.h"
#include "../lab041/IShape.h"
#include "../lab041/ISolidShape.h"

TEST_CASE("Circle characterx are valid")
{
	CPoint center(1.5, 39.45);
	CCircle testCircle(center, 2.0, "00ff00", "ff0000");
	CPoint expCenter(1.5, 39.45);

	CHECK(testCircle.GetCenter().GetX() == expCenter.GetX());
	CHECK(testCircle.GetCenter().GetY() == expCenter.GetY());
	CHECK(ApproxEq(testCircle.GetCenter(), expCenter));
	CHECK(testCircle.GetRadius() == 2.0);
	CHECK(testCircle.GetOutlineColor() == std::string("00ff00"));
	CHECK(testCircle.GetFillcolor() == std::string("ff0000"));

	double expPerimeter = 2 * 3.1415926 * 2.0;
	double diff = std::abs(testCircle.GetPerimeter() - expPerimeter);
	CHECK(diff < 0.000001);

	double expArea = 3.1415926 * 2.0 * 2.0;
	diff = std::abs(testCircle.GetArea() - expArea);
	CHECK(diff < 0.000001);

	std::string expCircleDescription = std::string("\tShape type is Circle\n") + std::string("\tOutline color is 00ff00\n") + std::string("\tFill color is ff0000\n") + std::string("\tcenter is at point (1.5, 39.45)\n") + std::string("\tradius is 2\n") + std::string("\tPerimeter = 12.5664\n") + std::string("\tArea = 12.5664\n");

	CHECK(testCircle.ToString() == expCircleDescription);
}

TEST_CASE("Rectangle characterx are valid")
{
	CPoint vraiLeftTop(2.0, 12.11);
	CRectangle testRectangle(vraiLeftTop, 12.5, 25.6, "abcdef", "fedcba");

	CPoint expLeftTop(2.0, 12.11);
	CHECK(testRectangle.GetLeftTop().GetX() == expLeftTop.GetX());
	CHECK(testRectangle.GetLeftTop().GetY() == expLeftTop.GetY());
	CHECK(ApproxEq(testRectangle.GetLeftTop(), expLeftTop));

	CPoint expRightBottom(14.5, 37.71);
	CHECK(testRectangle.GetRightBottom().GetX() == expRightBottom.GetX());
	CHECK(testRectangle.GetRightBottom().GetY() == expRightBottom.GetY());
	CHECK(ApproxEq(testRectangle.GetRightBottom(), expRightBottom));

	CHECK(testRectangle.GetWidth() == 12.5);
	CHECK(testRectangle.GetHeight() == 25.6);

	CHECK(testRectangle.GetOutlineColor() == std::string("abcdef"));
	CHECK(testRectangle.GetFillcolor() == std::string("fedcba"));

	double expPerimeter = 2 * (12.5 + 25.6);
	double diff = std::abs(testRectangle.GetPerimeter() - expPerimeter);
	CHECK(diff < 0.000001);

	double expArea = 12.5 * 25.6;
	diff = std::abs(testRectangle.GetArea() - expArea);
	CHECK(diff < 0.000001);

	std::string expRectangleDescription = std::string("\tShape type is Rectangle\n") + std::string("\tOutline color is abcdef\n") + std::string("\tFill color is fedcba\n") + std::string("\tLeft top vertex is (2, 12.11)\n") + std::string("\twidth is 12.5\n") + std::string("\theight is 25.6\n") + std::string("\tPerimeter = 76.2\n") + std::string("\tArea = 320\n");

	CHECK(testRectangle.ToString() == expRectangleDescription);
}

TEST_CASE("Triangle characterx are valid")
{
	CPoint v1(0.0, 0.0);
	CPoint v2(0, 3.0);
	CPoint v3(4.0, 0);
	CTriangle testTriangle(v1, v2, v3, "aaa000", "a0a0a0");

	CPoint expVert1(0.0, 0.0);
	CHECK(testTriangle.GetVertex1().GetX() == expVert1.GetX());
	CHECK(testTriangle.GetVertex1().GetY() == expVert1.GetY());
	CHECK(ApproxEq(testTriangle.GetVertex1(), expVert1));

	CPoint expVert2(0.0, 3.0);
	CHECK(testTriangle.GetVertex2().GetX() == expVert2.GetX());
	CHECK(testTriangle.GetVertex2().GetY() == expVert2.GetY());
	CHECK(ApproxEq(testTriangle.GetVertex2(), expVert2));

	CPoint expVert3(4.0, 0.0);
	CHECK(testTriangle.GetVertex3().GetX() == expVert3.GetX());
	CHECK(testTriangle.GetVertex3().GetY() == expVert3.GetY());
	CHECK(ApproxEq(testTriangle.GetVertex3(), expVert3));

	CHECK(testTriangle.GetOutlineColor() == std::string("aaa000"));
	CHECK(testTriangle.GetFillcolor() == std::string("a0a0a0"));

	double expPerimeter = 12.0;
	double diff = std::abs(testTriangle.GetPerimeter() - expPerimeter);
	CHECK(diff < 0.000001);

	double expArea = 6.0;
	diff = std::abs(testTriangle.GetArea() - expArea);
	CHECK(diff < 0.000001);

	std::string expTriangleDescription = std::string("\tShape type is Triangle\n") + std::string("\tOutline color is aaa000\n") + std::string("\tFill color is a0a0a0\n") + std::string("\tVertex 1 is (0, 0)\n") + std::string("\tVertex 2 is (0, 3)\n") + std::string("\tVertex 3 is (4, 0)\n") + std::string("\tPerimeter = 12\n") + std::string("\tArea = 6\n");

	CHECK(testTriangle.ToString() == expTriangleDescription);
}

TEST_CASE("Line segment characterx are valid")
{
	CPoint sP(1.5, 2.5);
	CPoint eP(4.5, 6.5);
	CLineSegment testLS(sP, eP, "ffffff");

	CPoint expStartPoint(1.5, 2.5);
	CHECK(testLS.GetStartPoint().GetX() == expStartPoint.GetX());
	CHECK(testLS.GetStartPoint().GetY() == expStartPoint.GetY());
	CHECK(ApproxEq(testLS.GetStartPoint(), expStartPoint));

	CPoint expEndPoint(4.5, 6.5);
	CHECK(testLS.GetEndPoint().GetX() == expEndPoint.GetX());
	CHECK(testLS.GetEndPoint().GetY() == expEndPoint.GetY());
	CHECK(ApproxEq(testLS.GetEndPoint(), expEndPoint));

	CPoint expRadVector(3.0, 4.0);
	CHECK(testLS.GetRadVector().GetX() == expRadVector.GetX());
	CHECK(testLS.GetRadVector().GetY() == expRadVector.GetY());
	CHECK(ApproxEq(testLS.GetRadVector(), expRadVector));

	CHECK(testLS.GetOutlineColor() == std::string("ffffff"));

	double expPerimeter = 5.0;
	double diff = std::abs(testLS.GetPerimeter() - expPerimeter);
	CHECK(diff < 0.000001);

	double expArea = 0.0;
	diff = std::abs(testLS.GetArea() - expArea);
	CHECK(diff < 0.000001);

	std::string expLSDescription = std::string("\tShape type is Line segment\n") + std::string("\tColor is ffffff\n") + std::string("\tEndpoint 1 is (1.5, 2.5)\n") + std::string("\tEndpoint 2 is (4.5, 6.5)\n") + std::string("\tPerimeter = 5\n") + std::string("\tArea = 0\n");

	CHECK(testLS.ToString() == expLSDescription);
}
