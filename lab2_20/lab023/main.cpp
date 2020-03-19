// main.cpp: определяет точку входа для консольного приложения.
// Словарь для перевода слов и фраз с русского языка на английский

#include "stdafx.h"
#include "../lab023/Dictionary.h"

int main(int argc, char* argv[])
{
	// setlocale(LC_ALL, "Rus");

	std::cout << "Translates words and sentences from english into russian\n"
		<< "Input phrase to translate or ... to exit" << std::endl;

	std::string vocaFileName = (argc > 1) ? argv[1] : "Vocabulary1.vcb";
	dict currVocabularDir = {}; // cловарь англ -> рус
	dict currVocabularRev = {}; // словарь рус -> англ

	GetDictionaryFromFile(vocaFileName, currVocabularDir);
	BuildRevDictionary(currVocabularRev, currVocabularDir);

	if (Session(currVocabularDir, currVocabularRev)) // сессия работы со словарем
	{
		SaveDictionary(currVocabularDir, vocaFileName);
	}

	std::cout << "Good bye!" << std::endl;

	return 0;
}