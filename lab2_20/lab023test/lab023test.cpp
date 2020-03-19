#include "stdafx.h"
#include "../lab023/Dictionary.h"

bool FilesAreEqual(const std::string& fileName1, const std::string& fileName2) // побайтовое сравнение двух файлов
{
	std::ifstream file1(fileName1);
	std::ifstream file2(fileName2);

	if (!file1.is_open() || !file2.is_open())
	{
		return false;
	}
	else
	{
		while (!file1.eof() && !file2.eof())
		{
			if (file1.get() != file2.get()) return false;
		}
		return (file1.eof() && file2.eof()) ? true : false;
	}
}


TEST_CASE("Opening unexisting dictionary attempt")
{
	dict vocabular = {};
	CHECK(GetDictionaryFromFile("ProbablyNotExistingFile.txt", vocabular) == false);
}


TEST_CASE("Copiing existing dictionsry files")
{
	dict vocabular = {};
	GetDictionaryFromFile("testcases/initDictFile4testcopiing", vocabular);
	AddTranslation(vocabular, std::string("word2"), std::string("transl2"));
	SaveDictionary(vocabular, std::string("testcases/resultDictFile4testcopiingFact"));
	CHECK(FilesAreEqual("testcases/resultDictFile4testcopiingFact", "testcases/resultDictFile4testcopiingExp") == true);
}

TEST_CASE("Present and absent translations")
{
	dict vocabular = { {"cat", "кошка"} , {"dog", "собака"} , {"cat", "кот"} , {"fish", "рыба"} };
	std::vector<std::string> translationCat = FindTranslations(vocabular, std::string("cat"));
	CHECK(translationCat.size() == 2);
	CHECK(translationCat[0] == std::string("кошка"));
	CHECK(translationCat[1] == std::string("кот"));

	std::vector<std::string> translationRat = FindTranslations(vocabular, std::string("rat"));
	CHECK(translationRat.size() == 0);

	dict vocabularRev;
	BuildRevDictionary(vocabularRev, vocabular);
	std::vector<std::string> translationRyba = FindTranslations(vocabularRev, std::string("рыба"));
	CHECK(translationRyba.size() == 1);
	CHECK(translationRyba[0] == std::string("fish"));
}

TEST_CASE("Adding translations and reading old and new ones")
{
	dict vocabular = { { "ball", "шар" } , { "cube", "куб" } };

	AddTranslation(vocabular, std::string("pyramid"), std::string("пирамида"));
	AddTranslation(vocabular, std::string("ball"), std::string("мяч"));
	AddTranslation(vocabular, std::string("line"), std::string("строка"));
	AddTranslation(vocabular, std::string("ball"), std::string("балл"));
	AddTranslation(vocabular, std::string("line"), std::string("линия"));

	std::vector<std::string> translationBall = FindTranslations(vocabular, std::string("ball"));
	CHECK(translationBall.size() == 3);
	CHECK(translationBall[0] == std::string("шар"));
	CHECK(translationBall[1] == std::string("мяч"));
	CHECK(translationBall[2] == std::string("балл"));

	SaveDictionary(vocabular, std::string("testcases/resultDictAddingFact"));
	CHECK(FilesAreEqual("testcases/resultDictAddingFact", "testcases/resultDictAddingExp") == true);
}

