#include "stdafx.h"
#include "../lab023/Dictionary.h"


// true, если файл словаря найден и открыт
bool OpenVocabularyFile(const std::string& vocaFileName, std::ifstream& vocaFile)
{
	vocaFile.open(vocaFileName, std::ios::out);
	return vocaFile.is_open();
}

// сохраняет словарь в файл
void StoreVocabularToFile(const dict& vocabulary, std::ostream& vocaFile)
{
	for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
	{
		vocaFile << (*it).first << "\n" << (*it).second << "\n";
	}
}

// размещает словарь из файла в памяти в виде multimap
bool VocabularyInit(std::istream& vocaFile, dict& vocabulary)
{
	vocabulary = {};
	bool result = true;
	std::string phrase, transl;
	while (getline(vocaFile, phrase))
	{
		if (getline(vocaFile, transl))
		{
			vocabulary.emplace(phrase, transl);
		}
		else
		{
			result = false;
		}
	}
	return result;
}

bool GetDictionaryFromFile(const std::string& vocaFileName, dict& vocabulary)
{
	std::ifstream vocaFile;

	if (OpenVocabularyFile(vocaFileName, vocaFile))
	{
		if (!VocabularyInit(vocaFile, vocabulary))
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
bool PhraseExists(const dict& vocabulary, const std::string& phrase)
{
	return (vocabulary.upper_bound(phrase) != vocabulary.lower_bound(phrase));
}

// проверяет, существует ли уже данный перевод в словаре
bool ParticularTranslationForPhraseExists(const dict& vocabulary, 
	const std::string& phrase, const std::string& translation)
{
	bool result = false;
	for (auto it = vocabulary.lower_bound(phrase); it != vocabulary.upper_bound(phrase); ++it)
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
void AddTranslation(dict& vocabulary, const std::string& phrase, const std::string& translation)
{
	if (!ParticularTranslationForPhraseExists(vocabulary, phrase, translation))
	{
		vocabulary.emplace(phrase, translation);
	}
}

std::vector<std::string> FindPhraseTranslations(const dict& vocabulary, const std::string& phrase)
{
	std::vector<std::string> result;
	for (auto it = vocabulary.lower_bound(phrase); it != vocabulary.upper_bound(phrase); ++it)
	{
		result.push_back((*it).second);
	}
	return result;
}

// выводит переводы данного слова
void PrintPhraseTranslations(const dict& vocabulary, const std::string& phrase)
{
	std::vector<std::string> translations = FindPhraseTranslations(vocabulary, phrase);
	std::cout << std::endl;
	std::copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;
}


std::string ChangeNonHandler(const std::string& oldStr, const std::string& newStr)
{
	return ((newStr != "") && (newStr != "+")) ? newStr : oldStr;
}

State OnPhraseRequest(WorkSession& wSession, Dictionary& dictionary) // реакция на вводную фразу
{
	if (PhraseExists(dictionary.direct, wSession.inputPhrase))
	{
		std::cout << "Translation(s) for \"" << wSession.inputPhrase << "\": ";
		PrintPhraseTranslations(dictionary.direct, wSession.inputPhrase);
		std::cout << "If you want to add one more translation enter \"+\"" << std::endl;
		wSession.waitFor = WaitingForAddTranslation;
	}
	else if (PhraseExists(dictionary.reverse, wSession.inputPhrase))
	{
		std::cout << "Translation(s) for \"" << wSession.inputPhrase << "\": ";
		PrintPhraseTranslations(dictionary.reverse, wSession.inputPhrase);
		std::cout << "Enter phrase to translate" << std::endl;
		wSession.waitFor = WaitingForPhrase;
	}
	else
	{
		std::cout << "There is no \"" << wSession.inputPhrase << "\" in dictionary yet." << std::endl;
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		wSession.waitFor = WaitingForTranslation;
	}
	return wSession.waitFor;
}

State OnTranslationPrompt(WorkSession& wSession, Dictionary& dictionary)
{	// реакция на запрос перевода
	
	if (wSession.inputPhrase != "")
	{
		AddTranslation(dictionary.direct, wSession.prevPhrase, wSession.inputPhrase);
		AddTranslation(dictionary.reverse, wSession.inputPhrase, wSession.prevPhrase);
		std::cout << "Translation \"" << wSession.inputPhrase << "\" for \"" 
			<< wSession.prevPhrase << "\" is accepted" << std::endl;
		dictionary.changed = true;
	}
	std::cout << "Enter phrase to translate" << std::endl;
	wSession.waitFor = WaitingForPhrase;
	return wSession.waitFor;
}

State OnAddTranslationPrompt(WorkSession& wSession, Dictionary& dictionary)
{	// реакция на запрос добавочного перевода
	
	if (wSession.inputPhrase == "+")
	{
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		wSession.waitFor = WaitingForTranslation;
	}
	else if (wSession.inputPhrase == "")
	{
		std::cout << "Enter phrase to translate" << std::endl;
		wSession.waitFor = WaitingForPhrase;
	}
	else
	{
		wSession.waitFor = OnPhraseRequest(wSession, dictionary);
	}
	return wSession.waitFor;
}

// обрабатывает введенную фразу
bool ProcessInputPhrase(WorkSession& wSession, Dictionary& dictionary)
{
	bool vocaChanged = false;
	
	switch (wSession.waitFor)
	{
		case WaitingForPhrase:
		{
			wSession.waitFor = OnPhraseRequest(wSession, dictionary);
			break;
		}
		case WaitingForTranslation:
		{
			wSession.waitFor = OnTranslationPrompt(wSession, dictionary);
			break;
		}
		case WaitingForAddTranslation:
		{
			wSession.waitFor = OnAddTranslationPrompt(wSession, dictionary);
			break;
		}
		default:
			break;
	}
	wSession.prevPhrase = ChangeNonHandler(wSession.prevPhrase, wSession.inputPhrase);
	return vocaChanged;
}


bool Session(Dictionary& dictionary) // true -- словарь был дополнен
{
	WorkSession wSession = { WaitingForPhrase, std::string(), std::string() };
	dictionary.changed = false;

	while (true)
	{
		std::cout << "> ";
		getline(std::cin, wSession.inputPhrase);
		if (wSession.inputPhrase == "...") break;
		if (ProcessInputPhrase(wSession, dictionary))
		{
			dictionary.changed = true;
		}
	} 
		
	return dictionary.changed;
}

void SaveDictionary(const dict& vocabulary, const std::string& vocaFileName, char doSave)
{
	std::cout << "The dictionary was changed. Save changes? (y/Y)" << std::endl;
	std::cout << "> ";
	char save = doSave;
	if ((save != 'y') && (save != 'Y'))
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		save = std::cin.get();
	}
	if ((save == 'y') || (save == 'Y'))
	{
		std::ofstream newVocaFile;
		newVocaFile.open(vocaFileName, std::ios::trunc);
		StoreVocabularToFile(vocabulary, newVocaFile);
		std::cout << "Dictionary has saved in file " << vocaFileName << std::endl;
	}
}



void BuildRevDictionary(dict& vocabularyRev, const dict& vocabulary)
{
	for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
	{
		vocabularyRev.insert(std::pair<std::string, std::string>((*it).second, (*it).first));
	}
}



