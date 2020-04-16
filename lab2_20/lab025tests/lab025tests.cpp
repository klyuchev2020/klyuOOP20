#include "stdafx.h"
#include "../lab025/parseURL.h"

TEST_CASE("Empty url string leads to false parseURL value")
{
	std::string url;
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Non url-formatted string leads to false parseURL value")
{
	std::string url{ R"(some dummy path)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Empty host string leads to false parseURL value")
{
	std::string url{ R"(http://)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
	CHECK(host.empty());
}

TEST_CASE("All-optioned correct url leads to true parseURL value")
{
	std::string url{
		R"(http://www.domain1.sub-dom.sub_subdom.mz:75/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 75);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with default http port leads to true parseURL value")
{
	std::string url{
		R"(http://www.domain1.sub-dom.sub_subdom.mz/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 80);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with default https port leads to true parseURL value")
{
	std::string url{
		R"(https://www.domain1.sub-dom.sub_subdom.mz/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTPS);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 443);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with default ftp port leads to true parseURL value")
{
	std::string url{
		R"(ftp://www.domain1.sub-dom.sub_subdom.mz/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::FTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 21);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with Upper-case symbols in protocol name leads to true parseURL value")
{
	std::string url{
		R"(hTtP://www.domain1.sub-dom.sub_subdom.mz/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 80);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with explicit minimal possible port number leads to true parseURL value")
{
	std::string url{
		R"(http://www.domain1.sub-dom.sub_subdom.mz:1/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 1);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with explicit maximal possible port number leads to true parseURL value")
{
	std::string url{
		R"(FTP://www.domain1.sub-dom.sub_subdom.mz:65535/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::FTP);
	CHECK(host == "www.domain1.sub-dom.sub_subdom.mz");
	CHECK(port == 65535);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url without document part leads to true parseURL value")
{
	std::string url{ R"(Https://agregator.com)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTPS);
	CHECK(host == "agregator.com");
	CHECK(port == 443);
	CHECK(document.empty());
}

TEST_CASE("Possible url1 gives true")
{
	std::string url{ R"(htTP://yandex.ru/doc-document1)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
}

TEST_CASE("Unknown protocol name leads to false value")
{
	std::string url{ R"(httq://www.yandex.ru)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Protocol-domain delimiter without colon leads to false value")
{
	std::string url{ R"(http//www.yandex.ru)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Protocol-domain delimiter with colon and only slash leads to false value")
{
	std::string url{ R"(http:/www.yandex.ru)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Protocol-domain delimiter with colon and three slashes leads to false value")
{
	std::string url{ R"(http:///www.yandex.ru)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Url with explicit port sign of letter leads to false parseURL value")
{
	std::string url{
		R"(http://www.domain1.com:a/document)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Url with explicit port number 0 leads to false parseURL value")
{
	std::string url{
		R"(http://www.domain1.com:0/document)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Url with explicit port number 65536 leads to false parseURL value")
{
	std::string url{
		R"(http://www.domain1.com:65536/document)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Double slash after domain part leads to true parseURL value")
{
	std::string url{
		R"(http://www.domain1.com//document)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
}

TEST_CASE("Domain name without point symbol leads to false parseURL value")
{
	std::string url{
		R"(http://domain/document)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("Correct url with cyrillic symbols in domain part leads to true parseURL value")
{
	std::string url{
		R"(http://www.СиПиПиРеференс-2020.pф/scripts/script.php?x=2&y=string)"
	};
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "www.СиПиПиРеференс-2020.pф");
	CHECK(port == 80);
	CHECK(document == "scripts/script.php?x=2&y=string");
}

TEST_CASE("Correct url with explicit port number without document part leads to true parseURL value")
{
	std::string url{ R"(http://сайт.рус:23)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "сайт.рус");
	CHECK(port == 23);
	CHECK(document.empty());
}

TEST_CASE("Correct url with explicit port number slashed without document part leads to true parseURL value")
{
	std::string url{ R"(http://сайт.рус:23/)" };
	std::string host;
	Protocol protocol;
	std::string document;
	int port;

	CHECK(parseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(host == "сайт.рус");
	CHECK(port == 23);
	CHECK(document.empty());
}


