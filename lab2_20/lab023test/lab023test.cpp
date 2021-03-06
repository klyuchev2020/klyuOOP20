// lab023CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab023/Dictionary.h"

bool FilesAreEqual(const std::string& fileName1, const std::string& fileName2) // побайтовое сравнение двух файлов
{
	std::ifstream file1;
	std::ifstream file2;

	file1.open(fileName1);
	file2.open(fileName2);
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


TEST_CASE("Opening unexisting dictionary attempt leads to condition for exit(1)")
{
	dict vocabular = {};
	CHECK(GetDictionaryFromFile("ProbablyNotExistingFile.txt", vocabular) == false);
}

TEST_CASE("Copiing existing dictionary files allows to add phrases to existing dictionaries")
{
	dict vocabular = {};
	GetDictionaryFromFile("testcases/initDictFile4testcopiing", vocabular);
	AddTranslation(vocabular, std::string("word2"), std::string("transl2"));
	SaveDictionary(vocabular, std::string("testcases/resultDictFile4testcopiingFact"), 'y');
	CHECK(FilesAreEqual("testcases/resultDictFile4testcopiingFact", "testcases/resultDictFile4testcopiingExp") == true);
}

TEST_CASE("Present translations are of proper number; absent translations shows zero size")
{
	dict vocabular = { {"cat", "кошка"} , {"dog", "собака"} , {"cat", "кот"} , {"fish", "рыба"} };
	std::vector<std::string> translationCat = FindPhraseTranslations(vocabular, std::string("cat"));
	CHECK(translationCat.size() == 2);
	CHECK(translationCat[0] == std::string("кошка"));
	CHECK(translationCat[1] == std::string("кот"));

	std::vector<std::string> translationRat = FindPhraseTranslations(vocabular, std::string("rat"));
	CHECK(translationRat.size() == 0);

	dict vocabularRev;
	BuildRevDictionary(vocabularRev, vocabular);
	std::vector<std::string> translationRyba = FindPhraseTranslations(vocabularRev, std::string("рыба"));
	CHECK(translationRyba.size() == 1);
	CHECK(translationRyba[0] == std::string("fish"));
}

TEST_CASE("New translations are saved after adding, old translations in dictionary too")
{
	dict vocabular = { { "ball", "шар" } , { "cube", "куб" } };

	AddTranslation(vocabular, std::string("pyramid"), std::string("пирамида"));
	AddTranslation(vocabular, std::string("ball"), std::string("мяч"));
	AddTranslation(vocabular, std::string("line"), std::string("строка"));
	AddTranslation(vocabular, std::string("ball"), std::string("балл"));
	AddTranslation(vocabular, std::string("line"), std::string("линия"));

	std::vector<std::string> translationBall = FindPhraseTranslations(vocabular, std::string("ball"));
	CHECK(translationBall.size() == 3);
	CHECK(translationBall[0] == std::string("шар"));
	CHECK(translationBall[1] == std::string("мяч"));
	CHECK(translationBall[2] == std::string("балл"));

	SaveDictionary(vocabular, std::string("testcases/resultDictAddingFact"), 'y');
	CHECK(FilesAreEqual("testcases/resultDictAddingFact", "testcases/resultDictAddingExp") == true);

}



