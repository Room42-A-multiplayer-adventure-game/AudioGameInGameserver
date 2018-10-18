#include "word.h"
#include "ofApp.h"
#include <iostream>

// ctor & dtor
//---------------------------------------------------------------------
Word::Word(string s) {
	text = s;
	wortAnfang = "";
	buchstabe = "";
	wortEnde = "";
}

Word::Word(string anfang, string b, string ende) {
	wortAnfang = anfang;
	buchstabe = b;
	wortEnde = ende;
	text = anfang + b + ende;
}

Word::~Word() {	}

// methods
//---------------------------------------------------------------------

string Word::getText() const {
	return text;
}

string Word::getBuchstabe() const {
	return buchstabe;
}

string Word::getWortAnfang() const {
	return wortAnfang;
}

string Word::getWortEnde() const {
	return wortEnde;
}

void Word::setBuchstabe(string b) {
	buchstabe = b;
}
void Word::setWortAnfang(string a) {
	wortAnfang = a;
}
void Word::setWortEnde(string e) {
	wortEnde = e;
}
void Word::setStrings(string a, string b, string e) {
	wortAnfang = a;
	buchstabe = b;
	wortEnde = e;
	text = a + b + e;
}


// overloaded operators
//---------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const Word &word) {
	out << word.text;
	return out;
}

bool operator==(const Word &word1, const Word &word2) {
	return (word1.text == word2.text);
}
bool operator<(const Word &word1, const Word &word2) {
	return (word1.text < word2.text);
}
bool operator>(const Word &word1, const Word &word2) {
	return (word1.text > word2.text);
}