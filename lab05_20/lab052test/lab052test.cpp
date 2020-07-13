#include "stdafx.h"
#include "../lab052/CMyString.h"
#include "../lab052/CMystrIterator.h"


TEST_CASE("Length of empty string is equal to 0")
{
	CMyString empty;
	CHECK(empty.GetLength() == 0);
}

TEST_CASE("Destructor called when leaving block")
{
	int i = 1;
	{
		CMyString empty;
	}

	const char* cstring = "Hello";

	CHECK(cstring[4] == 'o');
	CHECK(cstring[5] == '\0');
	CHECK(strlen(cstring) == 5);
}

TEST_CASE("Proper length of string constructed via const char*")
{
	CMyString s("Hello");
	std::cout << "Ctor finished" << std::endl;
	CHECK(s.GetLength() == 5);
}

TEST_CASE("We can construct MyString from const char array")
{
	const char strangeHW[] = "Hello\0World";

	CMyString s(strangeHW, 4);
	CHECK(s.GetLength() == 4);
	CHECK(s.GetStringData()[1] == 'e');
	CHECK(s.GetStringData()[4] == '\0');

	CMyString sWith0(strangeHW, 10);
	CHECK(sWith0.GetLength() == 10);
	CHECK(sWith0.GetStringData()[2] == 'l');
	CHECK(sWith0.GetStringData()[5] == '\0');
	CHECK(*(sWith0.GetStringData() + 7) == 'o');
	CHECK(sWith0.GetStringData()[10] == '\0');

	CMyString empty("");
	CHECK(empty.GetLength() == 0);
	CHECK(empty.GetStringData()[0] == '\0');
}

TEST_CASE("Copiing ctor provides string of same consistancy")
{
	CMyString empty;
	CMyString copyOfEmpty(empty);

	CHECK(copyOfEmpty.GetLength() == empty.GetLength());
	CHECK(copyOfEmpty.GetStringData()[0] == empty.GetStringData()[0]);

	CMyString commonCString("How much is the fish?");
	CMyString commonCopy(commonCString);

	CHECK(commonCopy.GetLength() == 21);
	CHECK(commonCopy.GetStringData()[8] == ' ');
	CHECK(commonCopy.GetStringData()[21] == '\0');

	CMyString stringWithZeroes("How\0much\0\0is the fish\0\0\0", 24);
	CMyString copyWithZeroes(stringWithZeroes);

	CHECK(copyWithZeroes.GetLength() == 24);
	CHECK(copyWithZeroes.GetStringData()[2] == 'w');
	CHECK(copyWithZeroes.GetStringData()[9] == '\0');
	CHECK(copyWithZeroes.GetStringData()[18] == 'i');
	CHECK(copyWithZeroes.GetStringData()[22] == '\0');
}

TEST_CASE("Moving constructor behaves well")
{
	CMyString copyViaMoving(CMyString("Hello ") + CMyString("world!")); // Здесь может быть не перемещение

	CHECK(copyViaMoving.GetLength() == 12);
	CHECK(copyViaMoving.GetStringData()[10] == 'd');

	CMyString copyOfCopy(std::move(copyViaMoving));

	CHECK(copyOfCopy.GetLength() == 12);
	CHECK(copyOfCopy.GetStringData()[10] == 'd');
	CHECK(copyViaMoving.GetStringData() == nullptr);
}

TEST_CASE("Moving assignment works in case of direct moving")
{
	CMyString mystr("a\0b\0c\0d", 7);
	const char* sourceData = &mystr.GetStringData()[0];

	CMyString destMyStr("xyz");

	destMyStr = std::move(mystr);

	CHECK(destMyStr.GetLength() == 7);
	CHECK(std::string(destMyStr.GetStringData()) == std::string("a\0b\0c\0d"));
	CHECK(&destMyStr.GetStringData()[0] == sourceData);
	CHECK(mystr.GetStringData() == nullptr);
}

TEST_CASE("Can construct CMyString from stl-string")
{
	std::string empty;
	CMyString fromEmpty(empty);

	CHECK(fromEmpty.GetLength() == 0);
	CHECK(fromEmpty.GetStringData()[0] == '\0');

	std::string withZeroes({ 'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd' });

	CMyString fromWZ(withZeroes);

	CHECK(fromWZ.GetLength() == 11);
	CHECK(fromWZ.GetStringData()[5] == '\0');
	CHECK(fromWZ.GetStringData()[6] == 'W');
	CHECK(fromWZ.GetStringData()[11] == '\0');
}

TEST_CASE("Can clear MyString")
{
	CMyString nonEmpty("Hello!");

	CHECK(nonEmpty.GetLength() == 6);

	nonEmpty.Clear();

	CHECK(nonEmpty.GetLength() == 0);
	CHECK(nonEmpty.GetStringData() == nullptr);
}

TEST_CASE("Substring composing is correct")
{
	CMyString empty;
	CMyString emptySub2 = empty.SubString(0, 2);

	CHECK(emptySub2.GetLength() == 0);

	CMyString emptySub0 = empty.SubString(0, 0);

	CHECK(emptySub0.GetLength() == 0);

	CMyString usualCString("Common string");

	CMyString usualSub30 = usualCString.SubString(3, 0);
	CHECK(usualSub30.GetLength() == 0);

	CMyString usualSub200 = usualCString.SubString(20, 0);
	CHECK(usualSub200.GetLength() == 0);

	CMyString usualSub37 = usualCString.SubString(3, 7);
	CHECK(usualSub37.GetLength() == 7);
	CHECK(std::string(usualSub37.GetStringData()) == std::string("mon str"));

	CMyString usualSub415 = usualCString.SubString(4, 15);
	CHECK(usualSub415.GetLength() == 9);
	CHECK(std::string(usualSub415.GetStringData()) == std::string("on string"));

	CMyString usualSub49 = usualCString.SubString(4, 9);
	CHECK(usualSub49.GetLength() == 9);
	CHECK(std::string(usualSub49.GetStringData()) == std::string("on string"));

	CMyString withZeroes("\0\0zeroes\0everywhere!1\0\0", 23);

	CMyString zeroesSub01 = withZeroes.SubString(0, 1);
	CHECK(zeroesSub01.GetLength() == 1);
	CHECK(std::string(zeroesSub01.GetStringData()) == std::string("\0"));

	CMyString zeroesSub1001 = withZeroes.SubString(100, 1);
	CHECK(zeroesSub1001.GetLength() == 0);

	CMyString zeroesSub517 = withZeroes.SubString(5, 17);
	CHECK(zeroesSub517.GetLength() == 17);
	CHECK(std::string(zeroesSub517.GetStringData()) == std::string("oes\0everywhere!1\0"));

	CMyString zeroesSub8117 = withZeroes.SubString(8, 117);
	CHECK(zeroesSub8117.GetLength() == 15);
	CHECK(std::string(zeroesSub8117.GetStringData()) == std::string("\0everywhere!1\0\0"));

	CMyString zeroesSubWhole = withZeroes.SubString(0, withZeroes.GetLength());
	CHECK(zeroesSubWhole.GetLength() == withZeroes.GetLength());
	CHECK(std::string(zeroesSubWhole.GetStringData()) == std::string(withZeroes.GetStringData()));
}

TEST_CASE("Assignment to other and to itself works right")
{
	CMyString left("Old");
	CMyString right("New\0CMyString", 12);
	left = right;

	CHECK(left.GetLength() == 12);
	CHECK(std::string(left.GetStringData()) == std::string("New\0CMyString"));
	CHECK(right.GetLength() == 12);
	CHECK(std::string(right.GetStringData()) == std::string("New\0CMyString"));
	CHECK(left.GetStringData()[3] == '\0');
	CHECK(left.GetStringData()[4] == 'C');

	right = right;
	CHECK(right.GetLength() == 12);
	CHECK(std::string(right.GetStringData()) == std::string(left.GetStringData()));

	CMyString empty;

	left = empty;
	CHECK(left.GetLength() == 0);
	CHECK(empty.GetLength() == 0);

	empty = empty;
	CHECK(empty.GetLength() == 0);
}

TEST_CASE("Can concat two CMyStrings")
{
	CMyString first("One Two ");
	CMyString second1("Three Four");

	CMyString res1 = first + second1;
	CHECK(res1.GetLength() == 18);
	CHECK(std::string(res1.GetStringData()) == "One Two Three Four");

	CMyString empty;
	CMyString res2 = first + empty;
	CHECK(res2.GetLength() == 8);
	CHECK(std::string(res2.GetStringData()) == "One Two ");

	CMyString fiveZeroes("\0\0\0\0\0", 5);
	auto res3 = first + fiveZeroes;
	CHECK(res3.GetLength() == 13);
	CHECK(std::string(res3.GetStringData()) == std::string("One Two \0\0\0\0\0"));
	CHECK(res3.GetStringData()[13] == '\0');
}

TEST_CASE("Can concat MyString and CString")
{
	CMyString first("Three\0\0\0zeroes", 14);
	const char* second1 = " and one zero at the end";
	CMyString res1 = first + second1;
	CHECK(res1.GetLength() == 38);
	CHECK(std::string(res1.GetStringData()) == std::string("Three\0\0\0zeroes and one zero at the end"));
	CHECK(res1.GetStringData()[38] == '\0');

	const char* empty = "";
	CMyString res2 = first + empty;
	CHECK(std::string(res2.GetStringData()) == std::string(first.GetStringData()));
}

TEST_CASE("Can concat MyString and StlString")
{
	CMyString first("Three\0\0\0zeroes", 14);
	std::string second1(10, '!');
	CMyString res1 = first + second1;
	CHECK(res1.GetLength() == 24);
	CHECK(std::string(res1.GetStringData()) == std::string("Three\0\0\0zeroes!!!!!!!!!!"));
	CHECK(res1.GetStringData()[24] == '\0');

	std::string empty;
	CMyString res2 = first + empty;
	CHECK(std::string(res2.GetStringData()) == std::string(first.GetStringData()));
}

TEST_CASE("Can add CMyString")
{
	CMyString first("Before");
	CMyString second(" and after");

	first += second;
	CHECK(first.GetLength() == 16);
	CHECK(std::string(first.GetStringData()) == "Before and after");

	CMyString empty;
	empty += first;
	CHECK(empty.GetLength() == 16);
	CHECK(std::string(empty.GetStringData()) == "Before and after");
	CHECK(empty.GetStringData()[16] == '\0');
}

TEST_CASE("Compares two CMyStrings on equality")
{
	CMyString mystr1("Hello");
	CMyString mystr2("Hello ");

	CHECK(!(mystr1 == mystr2));

	CMyString mystr3("Hello");
	CMyString mystr4("Hell0");

	CHECK(!(mystr3 == mystr4));

	CMyString mystr5(" Hello");
	CMyString mystr6("Hello ");

	CHECK(!(mystr5 == mystr6));

	CMyString mystr7("Hello\0World", 11);
	CMyString mystr8("Hello");

	CHECK(!(mystr7 == mystr8));

	CMyString mystr9("One \0 \0\0 Two\0Three\0\0", 20);
	CMyString mystr10 = mystr9;

	CHECK(mystr9 == mystr10);

	CMyString empty1;
	CMyString empty2;

	CHECK(empty1 == empty2);
}

TEST_CASE("Can check two MyStrings on inequality")
{
	CMyString mystr1("Hello");
	CMyString mystr2("Hell0");

	CHECK(mystr1 != mystr2);

	CMyString mystr3("Hello");
	CMyString mystr4("Hello   ");

	CHECK(mystr3 != mystr4);

	CMyString mystr5("Hello\0World", 11);
	CMyString mystr6("Hello");

	CHECK(mystr5 != mystr6);

	CMyString empty1;
	CMyString empty2;

	CHECK(!(empty1 != empty2));
}

TEST_CASE("Can modify mystring via index access")
{
	CMyString mystr1("John Doe");
	mystr1[5] = 'H';

	CHECK(std::string(mystr1.GetStringData()) == "John Hoe");

	mystr1[1] = 0;
	CHECK(std::string(mystr1.GetStringData()) == std::string("J\0hn Hoe"));

	try
	{
		mystr1[10] = 'A';
	}
	catch (const std::out_of_range& e)
	{
		CHECK(e.what() == std::string("Index is out of range"));
	}
}

TEST_CASE("Can read mystring element via index access")
{
	CMyString mystr("Zero\0inside", 11);

	char ch = mystr[4];
	CHECK(ch == 0);
	CHECK(mystr[mystr[4]] == 'Z');

	for (size_t i = 0; i < mystr.GetLength(); ++i)
	{
		if (i + 1 < mystr.GetLength())
		{
			mystr[i] = mystr[i + 1];
		}
		else
		{
			mystr[i] = mystr[0];
		}
	}
	CHECK(std::string(mystr.GetStringData()) == std::string("ero\0insideZ"));
}

TEST_CASE("Able to lexicographical compare two MyStrings")
{
	CMyString empty1;
	CMyString empty2;

	CHECK(!(empty1 < empty2));
	CHECK(!(empty1 > empty2));
	CHECK(empty1 <= empty2);
	CHECK(empty2 <= empty1);
	CHECK(empty1 >= empty2);
	CHECK(empty2 >= empty1);

	CMyString threeZeroes("\0\0\0", 3);
	CHECK(empty1 < threeZeroes);
	CHECK(threeZeroes > empty1);
	CHECK(empty1 <= threeZeroes);
	CHECK(threeZeroes >= empty1);

	CMyString zeroA("\0A", 2);
	CHECK(threeZeroes < zeroA);
	CHECK(zeroA > threeZeroes);
	CHECK(threeZeroes <= zeroA);
	CHECK(zeroA >= threeZeroes);

	CMyString hello("Hello World");
	CMyString longHello("Hello World\0\0", 13);
	CHECK(hello < longHello);
	CHECK(longHello > hello);
	CHECK(hello <= longHello);
	CHECK(longHello >= hello);

	CMyString simpleAbra("abracadabra");
	CMyString transposedAbra("abracabadra");
	CHECK(transposedAbra < simpleAbra);
	CHECK(simpleAbra > transposedAbra);
	CHECK(transposedAbra <= simpleAbra);
	CHECK(simpleAbra >= transposedAbra);

	CMyString tenBigSymbols(std::string(10, 127));
	CMyString ratherHugeLetters = tenBigSymbols;
	ratherHugeLetters[8] = 'z';
	CHECK(ratherHugeLetters < tenBigSymbols);
	CHECK(tenBigSymbols > ratherHugeLetters);
	CHECK(ratherHugeLetters <= tenBigSymbols);
	CHECK(tenBigSymbols >= ratherHugeLetters);

	CMyString abc(std::string({ 'a', 'b', 0 }));
	CMyString sameAbc("ab\0", 3);
	CHECK(!(abc < sameAbc));
	CHECK(!(abc > sameAbc));
	CHECK(abc <= sameAbc);
	CHECK(sameAbc <= abc);
	CHECK(abc >= sameAbc);
	CHECK(sameAbc >= abc);
}

TEST_CASE("Can output into ostream")
{
	CMyString mystr("string\0\0with zeroes,\ncontrol symbols\t\0-real mystring\0\0\0", 56);
	std::ostringstream output;

	output << mystr;

	CHECK(output.str().size() == 56);
	CHECK(CMyString(output.str()) == mystr);
	CHECK(output.str()[7] == '\0');

	CMyString withBigCode("Ab\300");

	CHECK(withBigCode.GetLength() == 3);
	output.str("");
	output << withBigCode;
	CHECK(output.str()[0] == 'A');
	CHECK(output.str()[1] == 'b');
	CHECK(output.str()[2] == '\300');
}

TEST_CASE("Can enter simple mystrings")
{
	std::string mystrInit = "Hello World!\nString without zeros";
	std::istringstream mystrToInput(mystrInit);
	CMyString dest;
	mystrToInput >> dest;

	std::ostringstream output;

	output << dest;

	CHECK(output.str().size() == 33);
	CHECK(CMyString(output.str()) == CMyString(mystrInit));
}

TEST_CASE("Get non-modifying access string elements via iterators")
{
	CMyString someWithZero("Short\0string\0with\0zeroes\0on\0space\0positions", 43);
	CMystrConstIterator it = someWithZero.cbegin();

	CHECK(it == CMystrConstIterator(someWithZero.GetStringData()));
	CHECK(*it++ == 'S');
	CHECK(*it == 'h');
	CHECK(*++it == 'o');
	CHECK(*it-- == 'o');
	CHECK(*it == 'h');
	CHECK(*--it == 'S');
	it += someWithZero.GetLength();
	CHECK(it == someWithZero.cend());
	CHECK(*it == '\0');
	CHECK(*(it -= 5) == 't');

	size_t zerosNumber = 0;
	for (CMystrConstIterator iter = someWithZero.cbegin(); iter != someWithZero.cend(); ++iter)
	{
		if (*iter == '\0')
		{
			zerosNumber++;
		}
	}
	CHECK(zerosNumber == 6);

	CMystrConstIterator begin = someWithZero.cbegin();
	CMystrConstIterator end = someWithZero.cend();
	CHECK((begin += 22) == (end -= 21));

}

TEST_CASE("Can modify mystrings via iterators")
{
	CMyString mystr("\0\0\0aaaa\0\0zzzz\0cccc", 18);
	CMystrIterator it = mystr.begin();

	*it = '1';
	CHECK(mystr[0] == '1');
	for (size_t i = 3; i < 7; ++i)
	{
		*(mystr.begin() += i) = 'b';
	}
	CHECK(mystr.SubString(3, 4) == CMyString("bbbb"));

	CHECK(*++it == '\0');
	CHECK(*--it == '1');

	for (it = mystr.begin(); it != mystr.begin() + 4; it++)
	{
		*it = 'W';
	}
	CHECK(mystr == CMyString("WWWWbbb\0\0zzzz\0cccc", 18));
	*it-- = 'Y';
	*(it -= 3) = 'S';
	CHECK(mystr[0] == 'S');
	CHECK(mystr[4] == 'Y');
}

TEST_CASE("Can execute range-based for")
{
	CMyString someZeroes("abc\0defgh\0\0ijkl\0mn", 18);

	size_t counter = 0;
	for (const char& ch : someZeroes)
	{
		if (ch == '\0')
		{
			counter++;
		}
	}
	CHECK(counter == 4);
}

TEST_CASE("Can use certain stl-algorithms") // пока не может специализировать шаблон std:count
{
	CMyString someZeroes("abc\0defgh\0\0ijkl\0mn", 18);
	char needle = '\0';
	auto itZero = std::find(someZeroes.cbegin(), someZeroes.cend(), needle);
	CHECK(*itZero == '\0');
	
}