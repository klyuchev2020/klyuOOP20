#pragma once

#include <map>
#include <string>

typedef std::multimap<std::string, std::string> dict;
enum State { WaitingForPhrase = 1, WaitingForTranslation, WaitingForAddTranslation };

struct Dictionary
{
	dict direct;
	dict reverse;
	bool changed;
};

struct WorkSession
{
	State waitFor;
	std::string inputPhrase;
	std::string prevPhrase;
};

void StoreVocabularToFile(const dict& vocabulary, std::ostream& vocaFile);
bool VocabularyInit(std::istream& vocaFile, dict& vocabulary);
bool GetDictionaryFromFile(const std::string& vocaFileName, dict& vocabulary);
std::vector<std::string> FindPhraseTranslations(const dict& vocabulary, const std::string& phrase);
void AddTranslation(dict& vocabulary, const std::string& phrase, const std::string& translation);
void BuildRevDictionary(dict& vocabularyRev, const dict& vocabulary);
void SaveDictionary(const dict& vocabulary, const std::string& vocaFileName, char doSave = 'n');
bool ProcessInputPhrase(WorkSession& wSession, Dictionary& dictionary);
bool Session(Dictionary& dictionary);
