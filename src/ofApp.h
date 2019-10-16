#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class SessionWarning{
public:
	bool triggered = false;
	string name = "";
};
class SessionWarningSystem{
public:
	map<string,SessionWarning>warnings;
	ofSoundPlayer warningPlayer;
	
	void resetAll();
	void triggerWarning(string name);
	void addWarning(string name);
};
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float countDownDist;
    float timerBegin;
    float totalTime;
    float presentationTime;
    
    float pauseTimeStart;
    float pauseTimeEnd;
    float instanceTimePaused;
    float totalTimePaused;
    
    int randomColorVal;
     int randomColorVal2;
    //bool pauseTimer;
    ofTrueTypeFont font;
	ofTrueTypeFont fontTime;
    
    ofxPanel gui;
    ofxIntSlider totalMin;
    ofxToggle timerIsPaused;
    ofxToggle resetTimer;
		
	
	SessionWarningSystem warnings;
	
};
