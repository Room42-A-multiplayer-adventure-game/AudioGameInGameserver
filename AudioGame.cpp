#pragma once
#include "AudioGame.h"
#include "ofApp.h"
#include "ofxOsc.h"
#include "word.h"
#include "ofxXmlSettings.h"
#include <thread>

AudioGame::AudioGame() {
	
}

AudioGame::~AudioGame(){}

void AudioGame::init(Netti n, TippSystem t) {
	// load XML file
	settings.loadFile("../../assets/settings.xml");

	textProcessor.addSettings(settings);
	// for OSC connection with input
	audioReceiver.setup(settings.getValue("settings:audio_receiver_port", 11111));
	audioSender.setup(settings.getValue("settings:host", "localhost"), settings.getValue("settings:audio_sender_port", 22222));
	audioSenderNetti.setup(settings.getValue("settings:host", "localhost"), settings.getValue("settings:audio_senderNetti_port", 33333));


	// set codeword
	string codeword = ofToString(settings.getValue("settings:codeword", "none"));
	if ((codeword != "none") && (codeword != "")) {
		std::transform(codeword.begin(), codeword.end(), codeword.begin(), ::tolower);
		textProcessor.setCodeword(codeword);
	}
	else {
		string input = ""; //hier könnte man auch das Codewort hardcoden
		cout << "Please enter a Codeword:\n>";
		getline(cin, input);
		textProcessor.setCodeword(input);
	}

	netti = n;
	tippSystem = t;
}


void AudioGame::startAudioRecording() {
	// send message to input to start recording
	if (!inputIsRunning) {
		ofxOscMessage start;
		start.setAddress("/audioStatus");
		start.addStringArg("start");
		audioSender.sendMessage(start);
		inputIsRunning = true;

		std::thread gameThread(&AudioGame::playAudioGame, this);
		gameThread.join();
	}
}

void AudioGame::stopAudioRecording() {
		// no more audio recording necessary --> send message to stop
		ofxOscMessage stop;
		stop.setAddress("/audioStatus");
		stop.addStringArg("pause");
		audioSender.sendMessage(stop);
		inputIsRunning = false;

		audioGameWasPlayed = true;
}

void AudioGame::playAudioGame() {
	int currentTime = GetCurrentTime();
	while (inputIsRunning) {
		string sentence = "";

		// read OSC messages from input
		while (audioReceiver.hasWaitingMessages()) {
			ofxOscMessage msg;

			if (audioReceiver.getNextMessage(msg)) {
				sentence = msg.getArgAsString(0);

				cout << "Message: " << sentence << endl;

				Word* recognizedWord = textProcessor.processMessage(sentence);
				
				if (currentTime == settings.getValue("settings:audioSleep", 8000)) {
					tippSystem.audioTipp(0);
				}
				
				// aus word bubbles erzeugen
				if ((*recognizedWord).getText() != "") {
					countWords++;

					netti.sendWord((*recognizedWord).getWortAnfang(), (*recognizedWord).getBuchstabe(), (*recognizedWord).getWortEnde());
				}
			}
		}

		if (inputIsRunning && (countWords == textProcessor.getCodeWordLength())) {
			stopAudioRecording();
		}

		//test
		setAudioGameFinished();
	}
}

void AudioGame::setAudioGameFinished() {
	textProcessor.setCodeWordLength(9);
	countWords = 9;
}