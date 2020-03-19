#include "stdafx.h"
#include "../lab022/HTMLDecode.h"

static std::map<std::string, char> substSymbol = { { "&quot;", '\"' },    // отображение замены
													{ "&apos;", '\'' },
													{ "&lt;"  , '<' },
													{ "&gt;"  , '>' },
													{ "&amp;" , '&' } };

TEST_CASE("HTMLDecode for strings: empty, nonmodified")
{

	std::string inputStr0 = "";
	std::string str0expRes = "";
	
	CHECK(Decode(inputStr0) == str0expRes);

	std::string inputStr1 = "s&qouta&&gtsrt dhh   &  fd &";
	std::string str1expRes = "s&qouta&&gtsrt dhh   &  fd &";
	
	CHECK(Decode(inputStr1) == str1expRes);
}


TEST_CASE("HTMLDecode for strings: decodings")
{

	std::string inputStr2 = "s&quot;a&&quot;gtsrt dhh   &  fd &";
	std::string str2expRes = "s\"a&\"gtsrt dhh   &  fd &";
	
	CHECK(Decode(inputStr2) == str2expRes);

	std::string inputStr3 = "&&&lt;xyz&gt;&amp;&amp;&&abcd  e f &apos";
	std::string str3expRes = "&&<xyz>&&&&abcd  e f &apos";
	
	CHECK(Decode(inputStr3) == str3expRes);

	std::string inputStr4 = "&lt;3&apos; Hello &gt;&& &amp !&apos;";
	std::string str4expRes = "<3\' Hello >&& &amp !\'";
	
	CHECK(Decode(inputStr4) == str4expRes);

}

TEST_CASE("HTMLDecode for strings: ampersands")
{

	std::string inputStr5 = "&&&&amp;&&&amp;&&amp;&amp;";
	std::string str5expRes = "&&&&&&&&&&";
	
	CHECK(Decode(inputStr5) == str5expRes);

	std::string inputStr6 = "&amp";
	std::string str6expRes = "&amp";
	
	CHECK(Decode(inputStr6) == str6expRes);

}