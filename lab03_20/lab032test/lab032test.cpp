// lab032test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "../lab032/CTokenSeries.h"

TEST_CASE("Zero test no concerned calculator works correctly")
{
	int i = std::string("zero test") == "zero" + std::string("test");
	CHECK(i == 0);
}

TEST_CASE("Correct tokens are classified well")
{
	std::istringstream symbol1("+");
	Token t1 = GetToken(symbol1);

	CHECK(t1.kind == tKind::Symbol);
	CHECK(isnan(t1.value));
	CHECK(t1.name == "+");

	std::istringstream number1("53.4775");
	Token t2 = GetToken(number1);

	CHECK(t2.kind == tKind::Number);
	CHECK(t2.value == 53.4775);
	CHECK(t2.name == "");

	std::istringstream keyword1("printfns");
	Token t3 = GetToken(keyword1);

	CHECK(t3.kind == tKind::Keyword);
	CHECK(isnan(t3.value));
	CHECK(t3.name == "printfns");

	std::istringstream identor1("r23_var");
	Token t4 = GetToken(identor1);

	CHECK(t4.kind == tKind::Identor);
	CHECK(isnan(t4.value));
	CHECK(t4.name == "r23_var");
}