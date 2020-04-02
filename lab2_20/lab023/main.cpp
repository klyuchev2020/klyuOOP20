// main.cpp: определ€ет точку входа дл€ консольного приложени€.
// —ловарь дл€ перевода слов и фраз с русского €зыка на английский

#include "stdafx.h"
#include "../lab023/Dictionary.h"

int main(int argc, char* argv[])
{
	// setlocale(LC_ALL, "Rus");

	std::cout << "Translates words and sentences from english into russian\n"
		<< "Input phrase to translate or ... to exit" << std::endl;

	std::string vocaFileName = (argc > 1) ? argv[1] : "Vocabulary1.vcb";
	Dictionary dictionary = { {}, {}, false };
	
	if (!GetDictionaryFromFile(vocaFileName, dictionary.direct))
	{
		return 1;
	};

	BuildRevDictionary(dictionary.reverse, dictionary.direct);

	if (Session(dictionary)) // сесси€ работы со словарем
	{
		SaveDictionary(dictionary.direct, vocaFileName);
	}

	std::cout << "Good bye!" << std::endl;

	return 0;
}