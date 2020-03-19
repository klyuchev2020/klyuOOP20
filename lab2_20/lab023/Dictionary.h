#pragma once

#include <map>
#include <string>
#include <vector>

typedef std::multimap<std::string, std::string> dict;
enum state { WaitingForPhrase = 1, WaitingForTranslation, WaitingForAddTranslation };

void StoreVocabular(const dict& vocabular, std::ostream& vocaFile);
bool LoadVocabular(std::istream& vocaFile, dict& vocabular);
bool GetDictionaryFromFile(const std::string& vocaFileName, dict& vocabular);
std::vector<std::string> FindTranslations(dict& vocabular, const std::string& phrase);
void AddTranslation(dict& vocabular, const std::string& phrase, const std::string& translation);
void BuildRevDictionary(dict& vocabularRev, const dict& vocabular);
void SaveDictionary(dict& vocabular, const std::string& vocaFileName);
bool ProcessInputPhrase(const std::string& inputPhrase, std::string& prevPhrase,
	dict& vocabularDir, dict& vocabularRev, state& waitFor);
bool Session(dict& vocabularDir, dict& vocabularRev);
bool FilesAreEqual(const std::string& fileName1, const std::string& fileName2);
