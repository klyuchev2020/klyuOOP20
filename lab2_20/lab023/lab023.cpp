#include "stdafx.h"
#include "../lab023/Dictionary.h"


// true, если файл словаря найден и открыт
bool VocaFileOpened(const std::string& vocaFileName, std::ifstream& vocaFile)
{
	vocaFile.open(vocaFileName, std::ios::out);
	return vocaFile.is_open();
}

// сохраняет словарь в файл
void StoreVocabular(const dict& vocabular, std::ostream& vocaFile)
{
	for (auto it = vocabular.begin(); it != vocabular.end(); ++it)
	{
		vocaFile << (*it).first << "\n" << (*it).second << "\n";
	}
}

// выгружает словарь из файла в память в виде multimap
bool LoadVocabular(std::istream& vocaFile, dict& vocabular)
{
	bool result = true;
	std::string eng, rus;
	while (getline(vocaFile, eng))
	{
		if (getline(vocaFile, rus))
		{
			vocabular.emplace(eng, rus);
		}
		else
		{
			result = false;
		}
	}
	return result;
}

bool GetDictionaryFromFile(const std::string& vocaFileName, dict& vocabular)
{
	std::ifstream vocaFile;

	if (VocaFileOpened(vocaFileName, vocaFile))
	{
		if (!LoadVocabular(vocaFile, vocabular))
		{
			std::cout << "Warning! Wrong dictionary file" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Dictionary is not yet exists! We are to fill a new dictionary!" << std::endl;
		return false;
	}
	return true;
}

// проверяет, есть ли в словаре данное слово
bool PhraseExists(dict& vocabular, const std::string& phrase)
{
	return (vocabular.upper_bound(phrase) != vocabular.lower_bound(phrase));
}

// проверяет, существует ли уже данный перевод в словаре
bool TheTranslationExists(dict& vocabular, const std::string& phrase, const std::string& translation)
{
	bool result = false;
	for (auto it = vocabular.lower_bound(phrase); it != vocabular.upper_bound(phrase); ++it)
	{
		if (it->second == translation)
		{
			result = true;
			break;
		}
	}
	return result;
}

// добавляет перевод слова
void AddTranslation(dict& vocabular, const std::string& phrase, const std::string& translation)
{
	if (!TheTranslationExists(vocabular, phrase, translation))
	{
		vocabular.emplace(phrase, translation);
	}
}

std::vector<std::string> FindTranslations(dict& vocabular, const std::string& phrase)
{
	std::vector<std::string> result;
	for (auto it = vocabular.lower_bound(phrase); it != vocabular.upper_bound(phrase); ++it)
	{
		result.push_back((*it).second);
	}
	return result;
}

// выводит переводы данного слова
void PrintTranslations(dict& vocabular, const std::string& phrase)
{
	std::vector<std::string> translations = FindTranslations(vocabular, phrase);
	std::cout << std::endl;
	std::copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;
}


void SavePrevPhrase(std::string& prevPhrase, const std::string& inputPhrase)
{
	if ((inputPhrase != "") && (inputPhrase != "+"))
	{
		prevPhrase = inputPhrase;
	}
}

state OnPhraseRequest(const std::string& inputPhrase, dict& vocabularDir, dict& vocabularRev) // реакция на вводную фразу
{
	state waitFor;
	if (PhraseExists(vocabularDir, inputPhrase))
	{
		std::cout << "Translation(s) for \"" << inputPhrase << "\": ";
		PrintTranslations(vocabularDir, inputPhrase);
		std::cout << "If you want to add one more translation enter \"+\"" << std::endl;
		waitFor = WaitingForAddTranslation;
	}
	else if (PhraseExists(vocabularRev, inputPhrase))
	{
		std::cout << "Translation(s) for \"" << inputPhrase << "\": ";
		PrintTranslations(vocabularRev, inputPhrase);
		std::cout << "Enter phrase to translate" << std::endl;
		waitFor = WaitingForPhrase;
	}
	else
	{
		std::cout << "Where is no \"" << inputPhrase << "\" in dictionary yet." << std::endl;
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		waitFor = WaitingForTranslation;
	}
	return waitFor;
}

state OnTranslationPrompt(const std::string& prevPhrase, const std::string& inputPhrase,
	dict& vocabularDir, dict& vocabularRev, bool& vocaChanged)
{	// реакция на запрос перевода
	state waitFor;
	if (inputPhrase != "")
	{
		AddTranslation(vocabularDir, prevPhrase, inputPhrase);
		AddTranslation(vocabularRev, inputPhrase, prevPhrase);
		std::cout << "Translation \"" << inputPhrase << "\" for \"" << prevPhrase << "\" is accepted" << std::endl;
		vocaChanged = true;
	}
	std::cout << "Enter phrase to translate" << std::endl;
	waitFor = WaitingForPhrase;
	return waitFor;
}

state OnAddTranslationPrompt(const std::string& inputPhrase, dict& vocabularDir, dict& vocabularRev)
{	// реакция на запрос добавочного перевода
	state waitFor;
	if (inputPhrase == "+")
	{
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		waitFor = WaitingForTranslation;
	}
	else if (inputPhrase == "")
	{
		std::cout << "Enter phrase to translate" << std::endl;
		waitFor = WaitingForPhrase;
	}
	else
	{
		waitFor = OnPhraseRequest(inputPhrase, vocabularDir, vocabularRev);
	}
	return waitFor;
}

// обрабатывает введенную фразу
bool ProcessInputPhrase(const std::string& inputPhrase, std::string& prevPhrase,
	dict& vocabularDir, dict& vocabularRev, state& waitFor)
{
	bool vocaChanged = false;

	switch (waitFor)
	{
	case WaitingForPhrase:
	{
		waitFor = OnPhraseRequest(inputPhrase, vocabularDir, vocabularRev);
		break;
	}
	case WaitingForTranslation:
	{
		waitFor = OnTranslationPrompt(prevPhrase, inputPhrase, vocabularDir, vocabularRev, vocaChanged);
		break;
	}
	case WaitingForAddTranslation:
	{
		waitFor = OnAddTranslationPrompt(inputPhrase, vocabularDir, vocabularRev);
		break;
	}
	default:
		break;
	}
	SavePrevPhrase(prevPhrase, inputPhrase);
	return vocaChanged;
}


bool Session(dict& vocabularDir, dict& vocabularRev) // true -- словарь был дополнен
{
	std::string inputPhrase;
	std::string prevPhrase;
	bool vocaChanged = false;

	state waitFor = WaitingForPhrase;

	while (true)
	{
		std::cout << "> ";
		getline(std::cin, inputPhrase);
		if (inputPhrase == "...") break;
		if (ProcessInputPhrase(inputPhrase, prevPhrase, vocabularDir, vocabularRev, waitFor))
		{
			vocaChanged = true;
		}
	}

	return vocaChanged;
}

void SaveDictionary(dict& vocabular, const std::string& vocaFileName)
{
	std::cout << "The dictionary was changed. Save changes? (y/Y)" << std::endl;
	std::cout << "> ";
	char save = ' ';
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	save = std::cin.get();
	if ((save == 'y') || (save == 'Y'))
	{
		std::ofstream newVocaFile;
		newVocaFile.open(vocaFileName, std::ios::trunc);
		StoreVocabular(vocabular, newVocaFile);
		std::cout << "Dictionary was saved in file " << vocaFileName << std::endl;
	}
}



void BuildRevDictionary(dict& vocabularRev, const dict& vocabular)
{
	for (auto it = vocabular.begin(); it != vocabular.end(); ++it)
	{
		vocabularRev.insert(std::pair<std::string, std::string>((*it).second, (*it).first));
	}
}



