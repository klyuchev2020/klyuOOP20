#include "../lab052/CMyString.h"
#include "stdafx.h"

TEST_CASE("Length of empty string is equal to 1 (due to '\0')")
{
	CMyString empty;
	CHECK(empty.GetLength() == 1);
}
	

