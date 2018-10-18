#pragma once
#include "ofMain.h"
#include "Word.h"
#include "ofxXmlSettings.h"

class TextProcessor {
private:
	bool checkIfOnlyCharacters(string wort);
	Word* searchForCodewordCharacterInSpokenWords();
	void deleteCodewordCharacters();

	ofxXmlSettings settings;
	set<string> codeWord;
	vector<string> codeBuchstaben;
	int codeWordLength = 0;
	set <Word> allWords;
	std::set<std::string> wordsAsStrings;
	vector<string> gefundeneBuchstaben;

public:
	TextProcessor();
	~TextProcessor();

	void addSettings(ofxXmlSettings s);
	void setCodeword(string input);
	int getCodeWordLength() const;
	Word* processMessage(string sentence);

	void setCodeWordLength(int length);
};