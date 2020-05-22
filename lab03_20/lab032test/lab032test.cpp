// lab032test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "../lab032/CTokenSeries.h"

bool IsTokenClassified(const std::string& tokenImage, Tkind kind, double val, const std::string& name)
{
	std::istringstream image(tokenImage);
	Token t = GetToken(image);

	return (t.kind == kind && (t.value == val || isnan(val))  && t.name == name);
}

TEST_CASE("Zero test no concerned calculator works correctly")
{
	int i = std::string("zero test") == "zero" + std::string("test");
	CHECK(i == 0);
}

TEST_CASE("Correct tokens are classified well")
{
	CHECK(IsTokenClassified("+", Tkind::Symbol, undefined, "+"));
	CHECK(IsTokenClassified("54.023", Tkind::Number, 54.023, ""));
	CHECK(IsTokenClassified("printfns", Tkind::Keyword, undefined, "printfns"));
	CHECK(IsTokenClassified("r23_var_4u5", Tkind::Identor, undefined, "r23_var_4u5"));
	CHECK(IsTokenClassified("-.98", Tkind::Number, -.98, ""));
}