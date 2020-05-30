// lab032test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "../lab032/CTStream.h"
#include "../lab032/CVariables.h"
#include "../lab032/CFunction.h"

bool IsTokenClassified(const std::string& tokenImage, Tkind kind, double val, const std::string& name)
{
	std::istringstream image(tokenImage);
	CTStream tstream(image);
	Token t = tstream.GetToken();

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

TEST_CASE("Variable declaration put var into varset with undefined value")
{
	CVariables vars;
	vars.DeclareVar("var1");

	CHECK(vars.IsVarDeclared("var1"));
	CHECK(!vars.IsVarDefined("var1"));
	CHECK(vars.DeclareVar("var1") == false); // повторное объявление возвращает false

	CHECK(isnan(vars.GetVarValue("var1")));

	vars.SetVarValue("var1", -.123);

	CHECK(vars.GetVarValue("var1") == -.123);
	CHECK(vars.PrintVar("var1") == "var1 : -0.12\n");

}

TEST_CASE("Variable assignment works well in case of predeclared variables")
{
	CVariables vars;
	vars.DeclareVar("var1");

	vars.SetVarValue("var1", 1.05e08);
	vars.DeclareVar("var_2");
	vars.SetVarValue("var_2", "var1");

	CHECK(vars.GetVarValue("var_2") == 1.05e08);

	vars.DeclareVar("v_ar3");
	vars.SetVarValue("var1", "v_ar3");

	CHECK(isnan(vars.GetVarValue("var1")));
}

TEST_CASE("Calculation for fuctions on one identor works correctly")
{
	CVariables vars;
	vars.DeclareVar("v_1");

	Token v_1token(Tkind::Identor, "v_1");
	CHECK(!vars.IsVarDefined("v_1"));

	std::vector<Token> f_1definition { v_1token, }; 

	CFunction f1("f_1", f_1definition);
	vars.SetVarValue("v_1", 100.0);

	CHECK(vars.IsVarDefined("v_1"));
	CHECK(f1.IsDefined());

}