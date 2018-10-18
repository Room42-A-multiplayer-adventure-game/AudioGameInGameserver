#pragma once
#include "TextProcessor.h"

TextProcessor::TextProcessor() {}

TextProcessor::~TextProcessor() {}

void TextProcessor::addSettings(ofxXmlSettings s) {
	settings = s;
}

void TextProcessor::setCodeword(string input) {
	for (int i = 0; i < input.length(); i++) {
		codeBuchstaben.push_back(input.substr(i, 1));
	}
	codeWordLength = codeBuchstaben.size();
}

int TextProcessor::getCodeWordLength() const
{
	return codeWordLength;
}

Word* TextProcessor::processMessage(string sentence) {
	istringstream phrase(sentence);
	string word;
	//Satz in Wörter zerlegen und in set speichern
	while (getline(phrase, word, ' ')) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		//Überprüfen ob Wort länger als ein Buchstabe und ob es nur Buchstaben enthält, nur 3 Wörter pro Satz durchsuchen
		if (word.length() > 1 && checkIfOnlyCharacters(word)) {
			wordsAsStrings.insert(word.c_str());
		}
	}

	if (codeBuchstaben.size() < 1)
	{
		cout << "codeBuchstaben ist leer" << endl;
	}
	//wordsAsStrings.insert("testwort");

	//codeBuchstaben durchiterieren und nach Buchstaben
	//in gesprochenen Wörtern suchen
	Word* wordFound = searchForCodewordCharacterInSpokenWords();

	//die buchstaben die gefunden wurden, werden aus der codewortbuchstaben liste gelöscht
	deleteCodewordCharacters();

	//wörter liste leeren und von vorne anfangen mit neuen Wörtern
	wordsAsStrings.clear();

	return wordFound;
}

//überprüft die gesprochenen Wörter auf Buchstaben (sonderzeichen werden aussortiert)
bool TextProcessor::checkIfOnlyCharacters(string wortZumUberpruefen)
{
	bool isOnlyCharacters = true;
	for (int i = 0; i < wortZumUberpruefen.size(); i++) {
		if (i > 0) {
			if (!isalpha(wortZumUberpruefen[i]) && !isspace(wortZumUberpruefen[i])) {
				isOnlyCharacters = false;
				break;
			}
		}
		
	}
	return isOnlyCharacters;
}

Word* TextProcessor::searchForCodewordCharacterInSpokenWords() {
	int counter = 0;
	Word* word = new Word("");
	for (vector<string>::iterator i = codeBuchstaben.begin();
		i != codeBuchstaben.end(); i++) {
		string buchstabe = *i;
		string wort = "null";
		string wortEnthaeltBuchstaben = "null";
		//gesprochenen Wörter durchiterieren
		for (std::set<std::string>::iterator it = wordsAsStrings.begin();
			it != wordsAsStrings.end(); it++) {
			wort = *it; //j-tes Wort aus dem gesprochenem Satz
			if (wort.find_first_of(buchstabe) != std::string::npos && counter < settings.getValue("settings:codeLetterPerSentence", 1)) {
				//durchsucht das wort nach dem i-ten buchstaben aus dem CodeWort
				//sucht nach dem Buchstaben in dem Wort und zerlegt danach das Wort in Anfang+Buchstabe+Ende
				counter++;
				int index = wort.find_first_of(buchstabe);
				string wortBegin = wort.substr(0, index);
				string wortEnde = wort.substr(index + 1);
				std::cout << wort << std::endl;

				(*word).setStrings(wortBegin, buchstabe, wortEnde);
				allWords.insert(*word);

				//Wort das Buchstaben enthält
				wortEnthaeltBuchstaben = *it;
				//Buchstabe wird gefundenenBuchstaben hinzugefuegt
				gefundeneBuchstaben.push_back(buchstabe);

				break; //jeder Buchstabe wird nur einmal erkannt
			}
		}
		//wort aus der Liste entfernen -> nicht mehrere Buchstaben pro Wort
		wordsAsStrings.erase(wortEnthaeltBuchstaben);
	}
	return word;
}

void TextProcessor::deleteCodewordCharacters() {
	if (codeBuchstaben.end() != codeBuchstaben.begin()) { //nur wenn noch Codebuchstaben da sind
		for (vector<string>::iterator b = gefundeneBuchstaben.begin();
			b != gefundeneBuchstaben.end(); b++) {
			string gefunden = *b;
			cout << "gefundener Buchstabe " << gefunden << endl;

			for (vector<string>::iterator r = codeBuchstaben.begin();
				r != codeBuchstaben.end(); r++) {
				if (*r == gefunden) {
					codeBuchstaben.erase(r);
					break;
				}
			}
		}
	}
	gefundeneBuchstaben.clear();
}

void TextProcessor::setCodeWordLength(int length) {
	codeWordLength = length;
}