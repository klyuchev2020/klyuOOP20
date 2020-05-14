// lab051test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "../lab051/CRational.h"

TEST_CASE("Default constructor gives ratio 0/1")
{
	CRational zeroToOne;
	int num = zeroToOne.GetNumerator();
	int den = zeroToOne.GetDenominator();
	CHECK(num == 0);
	CHECK(den == 1);
}

TEST_CASE("Constructor with one argument m gives ratio m/1")
{
	CRational integerRatio(3);
	int num = integerRatio.GetNumerator();
	int den = integerRatio.GetDenominator();
	CHECK(num == 3);
	CHECK(den == 1);

	CRational anotherIntRatio = CRational(-5);
	num = anotherIntRatio.GetNumerator();
	den = anotherIntRatio.GetDenominator();
	CHECK(num == -5);
	CHECK(den == 1);

	CRational oneMoreZeroToOne(0);
	CHECK(oneMoreZeroToOne.GetNumerator() == 0);
	CHECK(oneMoreZeroToOne.GetDenominator() == 1);
}

TEST_CASE("Constructor with two relative prime arguments m and n gives ratio m/n when n is nonzero")
{
	CRational irreducible(10, 21);
	int num = irreducible.GetNumerator();
	int den = irreducible.GetDenominator();
	CHECK(num == 10);
	CHECK(den == 21);

	CRational irredNegativeDenom(9, -35);
	num = irredNegativeDenom.GetNumerator();
	den = irredNegativeDenom.GetDenominator();
	CHECK(num == -9);
	CHECK(den == 35);

	CRational irredNegativeDenom2(-7, -35); // здесь не взаимно простые
	num = irredNegativeDenom2.GetNumerator();
	den = irredNegativeDenom2.GetDenominator();
	CHECK(num == 1);
	CHECK(den == 5);

	CHECK_THROWS_AS(CRational(5, 0), std::invalid_argument);
}

TEST_CASE("Normalize to irreducible fraction")
{
	CRational redbFrac(136, 248);
	int num = redbFrac.GetNumerator();
	int den = redbFrac.GetDenominator();
	CHECK(num == 17);
	CHECK(den == 31);

	CRational redbFrac2(-2000, 3525);
	num = redbFrac2.GetNumerator();
	den = redbFrac2.GetDenominator();
	CHECK(num == -80);
	CHECK(den == 141);

	CRational redbFrac3(0, 3525);
	num = redbFrac3.GetNumerator();
	den = redbFrac3.GetDenominator();
	CHECK(num == 0);
	CHECK(den == 1);

	CRational redbFrac4(-100, -76);
	num = redbFrac4.GetNumerator();
	den = redbFrac4.GetDenominator();
	CHECK(num == 25);
	CHECK(den == 19);
}

TEST_CASE("To double with error less then 0.00001")
{
	CRational ratio1(13, 99);

	double value1 = 0.13131313;
	double diff = std::abs(ratio1.ToDouble() - value1);
	CHECK(diff < 0.00001);
}

TEST_CASE("Equivalence is both numerator and denominator normalized coincidence") // ==
{
	CRational one1(3, 4);
	CRational other1(-3, -4);

	CHECK(one1 == other1);

	CRational one2(3, 4);
	CRational other2(12, 16);

	CHECK(one2 == other2);

	CRational one3(3, 4);
	CRational other3(4, 3);

	CHECK(!(one3 == other3));
}

TEST_CASE("Nequality is not right for nonnormalized ratiae") // !=
{
	CRational one1(3, -4);
	CRational other1(-3, 4);

	CHECK(!(one1 != other1));

	CRational one2(24, 15);
	CRational other2(8, 5);

	CHECK(!(one2 != other2));

	CRational one3(3, 5);
	CRational other3(4, 3);

	CHECK(one3 != other3);
}

TEST_CASE("Greater in three cases of realy < , == and >") // >
{
	CRational one1(-3, 5);
	CRational other1(-6, 13);

	CHECK(!(one1 > other1));

	CRational one2(24, 15);
	CRational other2(8, 5);

	CHECK(!(one2 > other2));

	CRational one3(-3, 5);
	CRational other3(-4, 3);

	CHECK(one3 > other3);
}

TEST_CASE("Greater or equal in three cases of realy < , == and >") // >=
{
	CRational one1(-3, 5);
	CRational other1(-6, 13);

	CHECK(!(one1 >= other1));

	CRational one2(24, 15);
	CRational other2(8, 5);

	CHECK(one2 >= other2);

	CRational one3(-3, 5);
	CRational other3(-4, 3);

	CHECK(one3 >= other3);
}

TEST_CASE("Less in three cases of realy < , == and >") // <
{
	CRational one1(3, 8);
	CRational other1(4, 5);

	CHECK(one1 < other1);

	CRational one2(-3, 7);
	CRational other2(9, -21);

	CHECK(!(one2 < other2));

	CRational one3(2, 7);
	CRational other3(-4, 3);

	CHECK(!(one3 < other3));
}

TEST_CASE("Less or equal in three cases of realy < , == and >") // <=
{
	CRational one1(3, 8);
	CRational other1(4, 5);

	CHECK(one1 <= other1);

	CRational one2(-3, 7);
	CRational other2(9, -21);

	CHECK(one2 <= other2);

	CRational one3(12, 7);
	CRational other3(4, 3);

	CHECK(!(one3 <= other3));
}

TEST_CASE("Unary plus gives ratio itself, unary minus changes numerator signum") // un_op+, un_op-
{
	CRational initial(90, -145);
	CHECK(initial.GetNumerator() == -18);
	CHECK(initial.GetDenominator() == 29);

	CRational plusInitial = +initial;
	CHECK(plusInitial.GetNumerator() == -18);
	CHECK(plusInitial.GetDenominator() == 29);

	CRational minusInitial = -initial;
	CHECK(minusInitial.GetNumerator() == 18);
	CHECK(minusInitial.GetDenominator() == 29);

	CRational zero(0, 6);
	CHECK((-zero).GetNumerator() == 0);
	CHECK((-zero).GetDenominator() == 1);
}

TEST_CASE("Adding ratio leads to normalize result, argument can be equal to initial ratio") // op+=
{
	CRational left(1, 3);
	CRational right(1, 6);
	left += right;
	CHECK(left.GetNumerator() == 1);
	CHECK(left.GetDenominator() == 2);

	right += right;
	CHECK(right == CRational(1, 3));

	CRational left2(3, 2);
	CRational right2(-1, 6);
	left2 += right2;
	CHECK(left2.GetNumerator() == 4);
	CHECK(left2.GetDenominator() == 3);
}

TEST_CASE("Adding integer by same operator must be successfull")
{
	CRational left(3, 5);
	int right = -2;
	left += right;
	CHECK(left.GetNumerator() == -7);
	CHECK(left.GetDenominator() == 5);
}

TEST_CASE("Subtracting ratio leads to normalize result") // op-=
{
	CRational left(3, 4);
	CRational right(5, 12);
	left -= right;
	CHECK(left.GetNumerator() == 1);
	CHECK(left.GetDenominator() == 3);

	right -= right;
	CHECK(right == CRational(0, 1));

	CRational left2(2, 15);
	CRational right2(-4, 15);
	left2 -= right2;
	CHECK(left2.GetNumerator() == 2);
	CHECK(left2.GetDenominator() == 5);

	CRational left3(-4, 7);
	CRational right3(-4, 7);
	left3 -= right3;
	CHECK(left3.GetNumerator() == 0);
	CHECK(left3.GetDenominator() == 1);
}

TEST_CASE("Subtracting integer by same operator must be successfull")
{
	CRational left(14, 5);
	int right = -4;
	left -= right;
	CHECK(left.GetNumerator() == 34);
	CHECK(left.GetDenominator() == 5);
}

TEST_CASE("Subtracting of two rationals is right even with integer on one of places")
{
	CRational minuend1(2, 3);
	CRational subtrahend1(4, 5);
	CRational expDifference1(-2, 15);

	CHECK(minuend1 - subtrahend1 == expDifference1);

	CRational minuend2(2, 3);
	int subtrahend2 = 4;
	CRational expDifference2(-10, 3);

	CHECK(minuend2 - subtrahend2 == expDifference2);

	int minuend3 = 5;
	CRational subtrahend3(7, 2);
	CRational expDifference3(3, 2);

	CHECK(minuend3 - subtrahend3 == expDifference3);
}

TEST_CASE("Addition must work with rational or integer arguments")
{
	CRational smd1(2, 3);
	CRational smd2(3, 28);
	CRational res = smd1 + smd2;
	CHECK(res.GetNumerator() == 65);
	CHECK(res.GetDenominator() == 84);

	CRational smd11(2, 3);
	int smd21 = 8;
	res = smd11 + smd21;
	CHECK(res.GetNumerator() == 26);
	CHECK(res.GetDenominator() == 3);

	int smd12 = 5;
	CRational smd22(-3, 7);
	res = smd12 + smd22;
	CHECK(res.GetNumerator() == 32);
	CHECK(res.GetDenominator() == 7);
}

TEST_CASE("Multiplication on ratio leads to normalize result") // op*=
{
	CRational left(8, 125);
	CRational right(10, 44);
	left *= right;
	CHECK(left.GetNumerator() == 4);
	CHECK(left.GetDenominator() == 275);

	CRational left2(2, -15);
	CRational right2(-15, 2);
	left2 *= right2;
	CHECK(left2.GetNumerator() == 1);
	CHECK(left2.GetDenominator() == 1);

	right2 *= right2;
	CHECK(right2 == CRational(225, 4));

	CRational left3(5, -7);
	CRational right3(0, 7);
	left3 *= right3;
	CHECK(left3.GetNumerator() == 0);
	CHECK(left3.GetDenominator() == 1);
}

TEST_CASE("Multiplying on integer by same operator must be successfull")
{
	CRational left(14, 15);
	int right = -25;
	left *= right;
	CHECK(left.GetNumerator() == -70);
	CHECK(left.GetDenominator() == 3);
}

TEST_CASE("Multiplication must work correctly with rational or integer arguments on both left and right sides") //op*
{
	CRational mr1(12, 35);
	CRational mr2(49, 54);
	CRational res = mr1 * mr2;
	CHECK(res.GetNumerator() == 14);
	CHECK(res.GetDenominator() == 45);

	CRational mr11(3, 16);
	int mr21 = 12;
	res = mr11 * mr21;
	CHECK(res.GetNumerator() == 9);
	CHECK(res.GetDenominator() == 4);

	int mr12 = 15;
	CRational mr22(-3, 20);
	res = mr12 * mr22;
	CHECK(res.GetNumerator() == -9);
	CHECK(res.GetDenominator() == 4);
}

TEST_CASE("Division is right besides zero division") // op/=
{
	CRational left(18, 35);
	CRational right(-12, 7);
	left /= right;
	CHECK(left.GetNumerator() == -3);
	CHECK(left.GetDenominator() == 10);

	right /= right;
	CHECK(right == CRational(1, 1));

	CRational left2(1, 2);
	CRational right2(0, 1);

	CHECK_THROWS_AS(left2 /= right2, std::invalid_argument);
}

TEST_CASE("Division is possible if divisor is nonzero") // op /
{
	CRational ddend(21, 5);
	CRational dsor(7, 17);
	CRational quotient = ddend / dsor;
	CHECK(quotient == CRational(51, 5));

	CRational ddend2(0, 5);
	CRational dsor2(7, 17);
	CRational quotient2 = ddend2 / dsor2;
	CHECK(quotient2 == CRational(0));

	CRational ddend3(2, 5);
	CRational dsor3(0, 17);

	CHECK_THROWS_AS(ddend3 / dsor3, std::invalid_argument);
}

TEST_CASE("Output rational makes view of numerator/denominator")
{
	CRational first;
	CRational second(2);
	CRational third(23, 117);

	std::ostringstream testStrm;
	testStrm << third << " + " << second << " + " << first;

	CHECK(testStrm.str() == std::string("23/117 + 2 + 0"));
}

TEST_CASE("Input in format makes CRational as numerator-denominator pair")
{
	CRational fifteenSevenths;
	CRational wrongRatio;
	std::stringstream strm;
	strm << "15/7";
	strm >> fifteenSevenths;

	CHECK(fifteenSevenths == CRational(15, 7));
}
