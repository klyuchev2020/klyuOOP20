#include "stdafx.h"
#include "../lab061/Equation4.h"

TEST_CASE("Solve most plain equation: x^4 - 5x^2 + 4 = 0, roots must be -2, -1 , 1 , 2") // (coupling)
{
	size_t expNumRoots = 4;
	CoeffSeries4 Coe(1.0, 0, -5, 0, 4);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -2.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], -1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[2], 1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[3], 2.0));
}

TEST_CASE("Solve most plain equation: x^4 - 4x^3 +2x^2 + 4x - 3 = 0, roots must be -1, 1, 3") // (coupling, repeated 1)
{
	size_t expNumRoots = 3;
	CoeffSeries4 Coe(1.0, -4, 2, 4, -3);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], 1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[2], 3.0));
}

TEST_CASE("Solve equation: x^4 - 2x^3 - 3x^2 + 4x + 4 = 0, roots must be -1, 2") // (coupling, repeated -1 twice and 2 twice)
{
	size_t expNumRoots = 2;
	CoeffSeries4 Coe(1.0, -2, -3, 4, 4);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], 2.0));
}

TEST_CASE("Solve equation: 24x^4 + 4x^3 - 30x^2 - 21x - 4 = 0, roots must be -1/2, 4/3") // (coupling, repeated -1/2 three times and 4/3)
{
	size_t expNumRoots = 2;
	CoeffSeries4 Coe(24.0, 4, -30, -21, -4);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -0.5));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], 4.0 / 3));
}

TEST_CASE("Solve equation: 4x^4 - 9x^2 = 0, roots must be -3/2, 0, 3/2") // (coupling, simple roots -3/2; 3/2, twice repeated 0.0)
{
	size_t expNumRoots = 3;
	CoeffSeries4 Coe(4.0, 0, -9, 0, 0);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -1.5));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], 0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[2], 1.5));
}

TEST_CASE("Solve equation: 16x^4 - 160x^3 + 600x^2 - 1000x + 625 = 0, roots must be 2.5") // (biquadric, repeated 2.5 four times)
{
	size_t expNumRoots = 1;
	CoeffSeries4 Coe(16.0, -160, 600, -1000, 625);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], 2.5));
}

TEST_CASE("Solve equation: x^4 + 2x^2 - 3 = 0, roots must be -1.0, 1.0") // (biquadric, simple roots)
{
	size_t expNumRoots = 2;
	CoeffSeries4 Coe(1.0, 0, 2, 0, -3);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], -1.0));
	CHECK(ApproximatelyEqual(solve4Roots.roots[1], 1.0));
}

TEST_CASE("Solve equation: x^4 + x^2 = 0, root must be 0.0") // (special, repeated 0.0 twice)
{
	size_t expNumRoots = 1;
	CoeffSeries4 Coe(1.0, 0, 1, 0, 0);
	EquationRoot4 solve4Roots = Solve4(Coe);
	CHECK(solve4Roots.numRoots == expNumRoots);
	CHECK(ApproximatelyEqual(solve4Roots.roots[0], 0.0));
}

TEST_CASE("Equation 0x^4 + 1x^3 = 0 must lead to exception invalid argument for Solve4")
{
	try
	{
		CoeffSeries4 Coe(0.0, 1.0, 0, 0, 0);
		EquationRoot4 solve4Roots = Solve4(Coe);
		CHECK_THROWS_AS(Solve4(Coe), std::invalid_argument);
	}
	catch (std::exception const& e)
	{
		CHECK(e.what() == std::string("Leading coefficient must not be equal to zero!"));
	}
}

TEST_CASE("Equation x^4 + x^2 + 1 = 0 must lead to exception domain_error for Solve4")
{
	try
	{
		CoeffSeries4 Coe(1.0, 0, 0, 0, 100);
		EquationRoot4 solve4Roots = Solve4(Coe);
		CHECK_THROWS_AS(Solve4(Coe), std::domain_error);
	}
	catch (std::exception const& e)
	{
		CHECK(e.what() == std::string("Equation has no roots! (from biquadric case)"));
	}
}

TEST_CASE("Equation x^4 + 2x^3 + 3x^2 + 4x + 5 = 0 must lead to exception domain_error for Solve4")
{
	try
	{
		CoeffSeries4 Coe(1.0, 2, 3, 4, 5);
		EquationRoot4 solve4Roots = Solve4(Coe);
		CHECK_THROWS_AS(Solve4(Coe), std::domain_error);
	}
	catch (std::exception const& e)
	{
		CHECK(e.what() == std::string("Equation has no roots! (from special case)"));
	}
}

TEST_CASE("Equation x^4 - 2x^3 - 3x^2 - 2x + 20 = 0 must lead to exception domain_error for Solve4")
{
	try
	{
		CoeffSeries4 Coe(1.0, -2, -3, -2, 20);
		EquationRoot4 solve4Roots = Solve4(Coe);
		CHECK_THROWS_AS(Solve4(Coe), std::domain_error);
	}
	catch (std::exception const& e)
	{
		CHECK(e.what() == std::string("Equation has no roots! (from coupling case)"));
	}
}

// случаи выбрасывания исключений и все