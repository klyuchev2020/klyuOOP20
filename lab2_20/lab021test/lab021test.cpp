#include "../lab021/stdafx.h"
#include "../lab021/TransformVector.h"

TEST_CASE("Transformation of empty vector is identity ")
{
	std::vector<float> v0 = { };
	std::vector<float> v0expRes = { };
	Modificate(v0);

	CHECK(v0 == v0expRes);
}

TEST_CASE("Transformation of positive vector is identity")
{
    std::vector<float> v1 = { 1, 2, 3, 4, 5, 6 };
	std::vector<float> v1expRes = { 1, 2, 3, 4, 5, 6 };
	Modificate(v1);

	CHECK(v1 == v1expRes);
}

TEST_CASE("Transformation of nonnegative vector with zeros is identity")
{
	std::vector<float> v1 = { 1, 0.0, 3, 4, 5, 0 };
	std::vector<float> v1expRes = { 1, 0.0, 3, 4, 5, 0 };
	Modificate(v1);

	CHECK(v1 == v1expRes);
}



TEST_CASE("Modification of negatives")
{
	std::vector<float> v2 = { -1.0, 3.0 };
	std::vector<float> v2expRes = { 3.0, 3.0 };
	Modificate(v2);

	CHECK(v2 == v2expRes);

	std::vector<float> v3 = { 4, -1, 3, -2, 0, -3 };
	std::vector<float> v3expRes = { 4, 12, 3, 24, 0, 36 };
	Modificate(v3);

	CHECK(v3 == v3expRes);

	std::vector<float> v4 = { 1, 2, 3, 4, 5, 6 };
	std::vector<float> v4expRes = { 1, 2, 3, 4, 5, 6 };
	Modificate(v4);

	CHECK(v4 == v4expRes);

	std::vector<float> v5 = { -2 };
	std::vector<float> v5expRes = { -8 };
	Modificate(v5);

	CHECK(v5 == v5expRes);

	std::vector<float> v6 = { -3.5, -1, -2.0, 3, 4, 6 };
	std::vector<float> v6expRes = { 73.5, 21, 42, 3, 4, 6 };
	Modificate(v6);

	CHECK(v6 == v6expRes);

}