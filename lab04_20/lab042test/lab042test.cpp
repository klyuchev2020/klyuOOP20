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
#include "../lab042/CCanvas.h"

TEST_CASE("fakeit detected")
{
	fakeit::Mock<ICanvas> mockC;
	
	ICanvas& c = mockC.get();

	fakeit::When(Method(mockC, DrawLine)).Do([](const CPoint& p1, const CPoint& p2, std::uint32_t){ std::cout << p1.GetX() << std::endl; });
	

	// Production code:
	c.DrawLine(CPoint(1.0, 2.0), CPoint(3.0, 5.0), 0xFFFFFFFF);
	//c.DrawCircle(CPoint(20.0, 20.0), 90.0, 0x00FF00FF);

	
	// Verify foo was invoked at least once. (The four lines do exactly the same)
	CHECK(fakeit::Verify(Method(mockC, DrawLine)));
	
}









