#pragma once

#include "ofMain.h"

class Word {
private:
	string text;
	string buchstabe;
	string wortAnfang;
	string wortEnde;

public:
	Word(string s = "");
	Word(string anfang, string b, string ende);
	~Word();

	string getText() const;
	string getBuchstabe() const;
	string getWortAnfang() const;
	string getWortEnde() const;

	void setBuchstabe(string b);
	void setWortAnfang(string a);
	void setWortEnde(string e);
	void setStrings(string a, string b, string e);


	friend std::ostream& operator<<(std::ostream& out, const Word &word);
	friend bool operator==(const Word &word1, const Word &word2);
	friend bool operator<(const Word &word1, const Word &word2);
	friend bool operator>(const Word &word1, const Word &word2);
};