#pragma once
#include "TextProcessor.h"
#include "ofxOsc.h"
#include "Netti.h"
#include "TippSystem.h"

class AudioGame {

public:
	AudioGame();
	~AudioGame();

	void init(Netti netti, TippSystem tippsystem);
	void startAudioRecording();
	void playAudioGame();
	void stopAudioRecording();

	void setAudioGameFinished();

	// for text processing
	TextProcessor textProcessor;

	// for OSC connection to input
	ofxOscReceiver audioReceiver;
	ofxOscSender audioSender;
	ofxOscSender audioSenderNetti;

	//for XML file
	ofxXmlSettings settings;

	bool inputIsRunning = false;
	bool audioGameWasPlayed = false;

	int countWords = 0;

	Netti netti;
	TippSystem tippSystem;
};