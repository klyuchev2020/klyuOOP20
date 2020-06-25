// lab032test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "../lab032/CTStream.h"
#include "../lab032/CVars.h"
#include "../lab032/CParser.h"
#include "../lab032/CError.h"

bool ApprEqual(double a, double b)
{
	return std::abs(a - b) < 1e-8;
}

bool IsTokenClassified(const std::string& tokenImage, Tkind kind, double val, const std::string& name)
{
	std::istringstream image(tokenImage);
	CTStream tstream(image);
	Token t = tstream.GetToken();

	return (t.kind == kind && (t.value == val || isnan(val))  && t.name == name);
}

void MainCycleTest(std::istream& is, std::ostream& os, std::vector<int>& errNumbers)
{
	CParser parser(is);
	size_t n = 0;
	
	while (!parser.StreamIsEmpty())
	{
		try
		{
			parser.ParseInstruction(os);
		}
		catch (const CError::BadToken& bt)
		{
			std::cout << bt.mess << std::endl;
			errNumbers.push_back(bt.errnum);
			parser.SkipStream();
		}
		catch (const CError::ParserError& pe)
		{
			std::cout << pe.mess << std::endl;
			errNumbers.push_back(pe.errnum);
			parser.SkipStream();
		}
		catch (const CError::ArithmeticError& ae)
		{
			std::cout << ae.mess << std::endl;
			errNumbers.push_back(ae.errnum);
			parser.SkipStream();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		n++;
	}
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

TEST_CASE("Constructing variables goes well")
{
	Variable var1("v_1", 12);

	CHECK(var1.name == "v_1");
	CHECK(isnan(var1.value));
	CHECK(var1.lastModified == 12);
	CHECK(var1.calculation[0] == "v_1");

	std::set<std::string> fVars = { "v_11", "v_2" };
	std::vector<std::string> calc2 = { "v_11", "v_2", "+"};
	std::vector<std::string> calcPfx = { "v_11", "v_2", "+" };

	Variable fun1("f1", fVars, calc2, calcPfx, 10);

	CHECK(fun1.name == "f1");
	CHECK(isnan(fun1.value));
	CHECK(fun1.lastModified == 10);
	CHECK(fun1.calculation[0] == "v_11");
	CHECK(fun1.calculation[1] == "v_2");
	CHECK(fun1.calculation[2] == "+");
	CHECK(fun1.calculation.size() == 3);

}

TEST_CASE("Declaration and definition of variables goes well")
{
	CVars vars;

	CHECK(!vars.IsDeclared("anyVar"));

	CHECK(vars.DeclareFreeVar("anyVar", 5));

	CHECK(vars.IsDeclared("anyVar"));

	CHECK(!vars.DeclareFreeVar("anyVar", 7));
	CHECK(!vars.IsDefined("anyVar"));

	vars.SetVarValue("anyVar", 3.5, 1);
	CHECK(vars.IsDefined("anyVar"));
	CHECK(vars.IsFreeVarName("anyVar"));
	CHECK(vars.GetValue("anyVar") == 3.5);

	vars.SetVarValue("anyVar", -1.1e22, 2);
	CHECK(vars.GetValue("anyVar") == -1.1e22);
}

TEST_CASE("Functions of free variables calculation is correct")
{
	CVars vars;

	vars.DeclareFreeVar("v_1", 8);
	vars.DeclareFreeVar("v_2", 10);
	vars.SetVarValue("v_1", 1.5, 9);
	vars.SetVarValue("v_2", 2.8, 11);

	const std::vector<std::string> fdecl1 = { "v_1", "v_2", "+" };
	const std::set<std::string> fVars1 = {"v_1", "v_2"};
	vars.DeclareFunction("f1", fVars1, fdecl1, fdecl1, 6);
	CHECK(vars.CalcFunctionValue("f1", 7) == 4.3);

	const std::vector<std::string> fdecl2 = { "v_1", "v_2", "-" };
	vars.DeclareFunction("f2", fVars1, fdecl2, fdecl2, 4);
	CHECK(ApprEqual(vars.CalcFunctionValue("f2", 8), -1.3));

	const std::vector<std::string> fdecl3 = { "v_1", "v_2", "*" };
	vars.DeclareFunction("f3", fVars1, fdecl3, fdecl3, 3);
	CHECK(ApprEqual(vars.CalcFunctionValue("f3", 10), 4.2));

	const std::vector<std::string> fdecl4 = { "v_1", "v_2", "/" };
	vars.DeclareFunction("f4", fVars1, fdecl4, fdecl4, 2);
	CHECK(ApprEqual(vars.CalcFunctionValue("f4", 3), 1.5/2.8));
}

TEST_CASE("Functions of free variables, undefined args leads to undefined result")
{
	CVars vars;

	vars.DeclareFreeVar("var_1", 5);
	vars.DeclareFreeVar("vr_2", 17);
	vars.SetVarValue("var_1", -0.3, 1);
	
	const std::vector<std::string> fdecl5 = { "var_1", "vr_2", "+" };
	const std::set<std::string> fVars2 = {"var_1", "vr_2"};
	vars.DeclareFunction("f5", fVars2, fdecl5, fdecl5, 11);
	CHECK(isnan(vars.CalcFunctionValue("f5", 12)));

	const std::vector<std::string> fdecl6 = { "vr_2", "var_1", "*" };
	vars.DeclareFunction("f6", fVars2, fdecl6, fdecl6, 12);
	CHECK(isnan(vars.CalcFunctionValue("f6", 13)));

	vars.DeclareFreeVar("variable3", 5);

	const std::vector<std::string> fdecl7 = { "var_1", "variable3", "/" };
	const std::set<std::string> fVars3 = {"var_1", "variable3"};
	vars.DeclareFunction("f7", fVars3, fdecl7, fdecl7, 13);
	CHECK(isnan(vars.CalcFunctionValue("f7", 14)));
}


TEST_CASE("Calculation with one functional argument makes correct recursion")
{
	CVars vars;
	
	vars.DeclareFreeVar("v_1", 4);
	vars.DeclareFreeVar("v_2", 5);
	vars.DeclareFreeVar("v_3", 6);

	const std::vector<std::string> fdecl8 = { "v_1", "v_2", "+" };
	const std::set<std::string> fVars4 = { "v_1", "v_2" };
	vars.DeclareFunction("f8", fVars4, fdecl8, fdecl8, 7);

	const std::vector<std::string> fdecl9 = { "f8", "v_3", "*" };
	const std::vector<std::string> fdecl9Pfx = { "v_1", "v_2", "+", "v_3", "*" };
	const std::set<std::string> fVars5 = { "v_1", "v_2", "v_3" };
	vars.DeclareFunction("f9", fVars5, fdecl9, fdecl9Pfx, 8);

	vars.SetVarValue("v_1", 0.3, 9);
	vars.SetVarValue("v_2", -2.5, 10);	
	vars.SetVarValue("v_3", 2.4, 11);
	
	CHECK(ApprEqual(vars.CalcFunctionValue("f9", 12), (0.3 - 2.5)*2.4));
}

TEST_CASE("Parsing of only variable declaration works well")
{
	std::istringstream ism("var v_1\n print v_1\n");
	std::ostringstream osm;
	CParser parser(ism);

	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	CHECK(osm.str() == "v_1: nan\n");
}

TEST_CASE("End of token stream definition goes well")
{
	std::istringstream ism("var v2\n var v_1\n print v_1\n");
	std::ostringstream osm;
	CParser parser(ism);

	CHECK(!parser.StreamIsEmpty());
	parser.ParseInstruction(osm);
	CHECK(!parser.StreamIsEmpty());
	parser.ParseInstruction(osm);
	CHECK(!parser.StreamIsEmpty());
	parser.ParseInstruction(osm);
	CHECK(parser.StreamIsEmpty());
	
}

TEST_CASE("Nan state of variables and functions holds on in proper cases")
{
	std::istringstream ism("var x\n print x\n let y = -1.7\n fn func = x + y\n print func\n let x = 0.5\n print func");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);
		
	CHECK(osm.str() == "x: nan\nfunc: nan\nfunc: -1.20\n");
}

TEST_CASE("Free variables assignment correctly shares assignee value")
{
	std::istringstream ism("var v_1\n let v_2 = v_1\n printvars\n let v_2 = 100.500\n"
						   "printvars\n let v_1 = -1.7\n printvars\n let v_2 = v_1\n printvars\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);
	
	CHECK(osm.str() == "v_1: nan\nv_2: nan\nv_1: nan\nv_2: 100.50\nv_1: -1.70\nv_2: 100.50\nv_1: -1.70\nv_2: -1.70\n");

}


TEST_CASE("Correctly formed instructions with non-superposed functions works well")
{
	std::istringstream ism("var v_1\n let v_2 = 1.5\n let v_1 = -2.3\n fn fsum = v_1 + v_2\n"
		"fn fdiff = v_1 - v_2\n fn fmul = v_1 * v_2\n fn fdiv = v_1 / v_2\n printfns\n var v_3");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "fdiff: -3.80\nfdiv: -1.53\nfmul: -3.45\nfsum: -0.80\n");

}

TEST_CASE("Superposed functions calculates correctly in case of late definition")
{
	std::istringstream ism("var v1\n var v2\n fn f1 = v1 + v2\n fn f2 = f1 * v2\n"
						   "fn f3 = f1/f2\n fn f4 = f3 - f1\n printfns\n let v1 = 0.5\n let v2 = 10\n printfns\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;
	
	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "f1: nan\nf2: nan\nf3: nan\nf4: nan\nf1: 10.50\nf2: 105.00\nf3: 0.10\nf4: -10.40\n");
}


TEST_CASE("If function not recalculates if it's free args not changed their values") // такты вычислений нумеруются с 1
{
	std::istringstream ism("let v_1 = 1.5\n let v_2 = 2.6\n fn f1 = v_1 + v_2\n print f1\n let v_3 = 9.7\n"
	                       "print f1\n");
	std::ostringstream osm;
	CParser parser(ism);
	
	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	parser.ParseInstruction(osm);
	
	CHECK(parser.GetVars()->GetValue("f1") == 4.1);
	CHECK(parser.GetVars()->GetCalcTime("f1") == 3); // при вызове на такте 5 функция f1 НЕ вычислялась вновь
	
}

TEST_CASE("Correct definitions for times to recalculate function, non-superposed case")
{
	std::istringstream ism("let v1 = -1.5\n let v2 = 2.8\n fn f1 = v1*v2\n let v3 = 3.0\n fn f2 = v3 - v1\n"
						   "fn f3 = v2 + v1\n let v4 = v2\n fn f4 = v4 + v2\n let v4 = 1.5\n printfns\n");
	std::ostringstream osm;
	CParser parser(ism);

	for (size_t i = 0; i < 10; ++i)
	{
		parser.ParseInstruction(osm);
	}
	
	CHECK(parser.GetVars()->GetCalcTime("f1") == 3); // проверяем такты пересчета функций
	CHECK(parser.GetVars()->GetCalcTime("f2") == 5);
	CHECK(parser.GetVars()->GetCalcTime("f3") == 6);
	CHECK(parser.GetVars()->GetCalcTime("f4") == 10);
}

TEST_CASE("Correct definitions for times to recalculate function, superposed case")
{
	std::istringstream ism("let v1 = -1.5\n let v2 = 2.8\n fn f1 = v1/v2\n fn f2 = f1 + v1\n fn f3 = f2 - v2\n"
						   "fn f4 = v1*v1\n printfns\n let v2 = 100.0\n fn f5 = v2 + v2\n printfns\n");
	std::ostringstream osm;
	CParser parser(ism);

	for (size_t i = 0; i < 10; ++i)
	{
		parser.ParseInstruction(osm);
		if (i == 6)
		{
			CHECK(parser.GetVars()->GetCalcTime("f1") == 3); // проверяем такты пересчета функций
			CHECK(parser.GetVars()->GetCalcTime("f2") == 4);
			CHECK(parser.GetVars()->GetCalcTime("f3") == 5);
			CHECK(parser.GetVars()->GetCalcTime("f4") == 6);
		}
	}

	CHECK(parser.GetVars()->GetCalcTime("f1") == 10); // проверяем такты пересчета функций
	CHECK(parser.GetVars()->GetCalcTime("f2") == 10);
	CHECK(parser.GetVars()->GetCalcTime("f3") == 10);
	CHECK(parser.GetVars()->GetCalcTime("f4") == 6);
	CHECK(parser.GetVars()->GetCalcTime("f5") == 9);
}


TEST_CASE("BadToken exception really being caught")
{
	std::istringstream ism("var v1\n var !2v\n fn f1 = v1");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 10);
}


TEST_CASE("Unknown instruction exception really being caught")
{
	std::istringstream ism("var v1\n bar v2\n fn f1 = v1");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 20);
}


TEST_CASE("Identor expected exception really being caught")
{
	std::istringstream ism("var v1\n var 12.09\n let v3 = -2.1\n fn f = v1 + v3\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 21);
}

TEST_CASE("Identor already in use exception really being caught")
{
	std::istringstream ism("var v1\n let v1 = -1.5e-4\n let v2 = 1\n fn v1 = v2\n let v2 = -2.5\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 22);
}

TEST_CASE("Equation symbol expected exception really being caught")
{
	std::istringstream ism("var v1\n let v2 v1\n let v1 = -2.1\n print v1\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "v1: -2.10\n");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 23);
}

TEST_CASE("Identor not yet declared exception really being caught")
{
	std::istringstream ism("var v1\n let v2 = 1.56\n fn f1 = v4 + v1\n fn f = v1 + v3\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 2);
	CHECK(errorNumbers[0] == 24);
	CHECK(errorNumbers[1] == 24);
}

TEST_CASE("Bad assignment exception really being caught")
{
	std::istringstream ism("var v1\n let v2 = 1.56\n let f1 = *\n fn v3 = v1 * v2\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 25);
	
}

TEST_CASE("Arithmetic operation expected exception really being caught")
{
	std::istringstream ism("var v1\n let v2 = 1.56\n fn f1 = v1 = v2\n fn f2 = v1 * v2\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 26);
}

TEST_CASE("Bad function definition exception really being caught")
{
	std::istringstream ism("var v1\n let v2 = 1.56\n fn f1 = v1 v2\n fn f2 = v1 * v2\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 27);
}

TEST_CASE("Zero division exception really being caught")
{
	std::istringstream ism("let v1 = 2.4\n let v2 = -2.4\n fn f1 = v1 + v2\n fn f2 = v1/f1\n print f2\n let v4 = 1.4\n");
	std::ostringstream osm;
	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "f2: nan\n");
	CHECK(errorNumbers.size() == 1);
	CHECK(errorNumbers[0] == 30);
	
}

TEST_CASE("Example with Heron formulae works well")
{
	std::ifstream ism("HeronTest.txt");
	std::ostringstream osm;

	std::vector<int> errorNumbers;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "a: 3.00\nb: 4.00\nc: 5.00\ntwo: 2.00\nprodOfFour: 36.00\n");
	CHECK(errorNumbers.size() == 0);

}

double FibonacciFromBinet(size_t n)
{
	double base1 = (std::pow(5, 0.5) + 1) / 2;
	double base2 = (std::pow(5, 0.5) - 1) / 2;
	double sign = (n % 2 == 0) ? 1.0 : -1.0;
	return (std::pow(base1, n) - sign * std::pow(base2, n)) / std::pow(5, 0.5);
}

void GetFibonacciWise(std::ostream& os, int init0, int init1, size_t lastN)
{
	os << "var x0\n";
	os << "var x1\n";
	os << "fn f0 = x0\n";
	os << "fn f1 = x1\n";
	for (size_t i = 2; i <= lastN; ++i)
	{
		os << "fn f" << i << " = f" << i - 1 << " + f" << i - 2 << "\n";
	}
	os << "let x0 = " << init0 << "\n";
	os << "let x1 = " << init1 << "\n";
	os << "print f" << lastN - 1 << "\n";
	os << "print f" << lastN << "\n";
}


TEST_CASE("Example with classical Fibonacci sequence works well") // fisrt 20 numbers 
{
	std::ifstream ism("fib20Test.txt");
	std::ostringstream osm;

	std::vector<int> errorNumbers;
	std::cout << FibonacciFromBinet(19) << std::endl;
	std::cout << FibonacciFromBinet(20) << std::endl;

	MainCycleTest(ism, osm, errorNumbers);

	CHECK(osm.str() == "f19: 4181.00\nf20: 6765.00\n");
	CHECK(errorNumbers.size() == 0);
}