#include "ofApp.h"

#define STARTSOUND "startSound"
#define ONEMINUTEWARNING "oneMinuteWarning"
#define TIMESUP "endSound"
#define WAYOVER "leaveNowSound"
#define WAYWAYOVER "reallyLeaveNowSound"

/*
 timer is starting
 one minute left
 your time is up
 please wrap it up quickly, you've gone overtime
 ok, time to give someone else a chance!
 */

void SessionWarningSystem::addWarning(string name){
	SessionWarning warning;
	warning.name = name;
	warnings[name] = warning;
}
void SessionWarningSystem::resetAll(){
	for(auto& kv:warnings){
		kv.second.triggered = false;
	}
}
void SessionWarningSystem::triggerWarning(string name){
	auto& warning=  warnings[name];
	if(!warning.triggered){
		warning.triggered = true;
		// load sound and play it!
		warningPlayer.load(warning.name+ ".wav");
		warningPlayer.play();
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    gui.add(resetTimer.setup("Reset Timer", false));
    gui.add(timerIsPaused.setup("Pause Timer", false));
    gui.add(totalMin.setup("Total Min", 5,1,15));
	
    
    timerBegin = ofGetElapsedTimef();
    
    totalTime = totalMin*60;
    
    randomColorVal2 = 255;
    randomColorVal = 255;
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.load("verdana.ttf", 200, true, true);
    font.setLetterSpacing(1.037);
    
	fontTime.load("verdana.ttf",600,true,true);
	fontTime.setLetterSpacing(1.);
	
    totalTimePaused = 0;
    instanceTimePaused = 0;
    
	
	// setup warnings:
	warnings.addWarning(STARTSOUND);
	warnings.addWarning(ONEMINUTEWARNING);
	warnings.addWarning(TIMESUP);
	warnings.addWarning(WAYOVER);
	warnings.addWarning(WAYWAYOVER);
	
    ofSetFullscreen(true);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    totalTime = totalMin*60;
    
    if(timerIsPaused){
        pauseTimeEnd = ofGetElapsedTimef();
        instanceTimePaused = pauseTimeEnd - pauseTimeStart;
    }else{
        if((totalTimePaused+instanceTimePaused)>totalTimePaused){
            totalTimePaused = totalTimePaused + instanceTimePaused;
            instanceTimePaused = 0;
        }
        presentationTime = ofGetElapsedTimef()-totalTimePaused-timerBegin;
        countDownDist = ofMap(presentationTime,0,totalTime,0,ofGetWidth());
        pauseTimeStart = ofGetElapsedTimef();
    }
    
    if(resetTimer){
        resetTimer=false;
        timerBegin = ofGetElapsedTimef();
        totalTimePaused = 0;
        instanceTimePaused = 0;
		
		// reset warning flags:
		warnings.resetAll();
        
        
        
        presentationTime = ofGetElapsedTimef()-totalTimePaused-timerBegin;
        countDownDist = ofMap(presentationTime,0,totalTime,0,ofGetWidth());
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    
     ofFill();
     ofSetColor(0,255,0);
     ofDrawRectangle(countDownDist,0,ofGetWidth()-countDownDist, ofGetHeight());
     ofSetColor(255);
    
	
	if(!timerIsPaused && presentationTime<totalTime){
		int invTime = totalTime-presentationTime;
		int min =invTime/60;
		int sec = fmod(invTime,60);
		string time = to_string(min) +":"+ (sec<10?"0":"") +to_string(sec);
		auto box =fontTime.getStringBoundingBox(time, 0,0);
		fontTime.drawString(time, (ofGetWidth()/2)-(box.width)/2, ofGetHeight()/2 + box.height*.5);
	}
    //Flat 1min warning
    if(presentationTime>(totalTime-60) && presentationTime<(totalTime-59.5)){
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
		// this will trigger the one minute warning one time
		warnings.triggerWarning(ONEMINUTEWARNING);
    }
    //flash when overtime
    if(presentationTime>totalTime){
        if(ofGetFrameNum()%20==0){
            randomColorVal = ofRandom(255);
            randomColorVal2 = ofRandom(255);
        }
        ofSetColor(randomColorVal,255,randomColorVal2);
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
        
        ofSetColor(255,randomColorVal2,randomColorVal);
		float scaleMult = sin(ofGetElapsedTimef())*.1 + 1.;
        font.drawString("Time is\n   UP", (ofGetWidth()/2)-(font.getStringBoundingBox("Time is\n   UP", 0,0).width * scaleMult)/2, ofGetHeight()/2);
		
		// trigger any warnings that need to be depending on current conditions
		warnings.triggerWarning(TIMESUP);
		if(presentationTime>totalTime+30.){
			warnings.triggerWarning(WAYOVER);
		}
		if (presentationTime>totalTime+60.){
			warnings.triggerWarning(WAYWAYOVER);
		}
    }
    
    if(timerIsPaused){
        ofSetColor(255,randomColorVal2,randomColorVal);
		font.drawString("PAUSE", (ofGetWidth()/2)-(font.getStringBoundingBox("PAUSE", 0,0).width)/2, ofGetHeight()/2);
	}else{
		if(presentationTime>2) warnings.triggerWarning(STARTSOUND);
    }
    
    //Draw minute lines
    ofSetColor(255);
    ofSetLineWidth(3);
    for(int i= 0; i<totalMin; i++){
        
        float distance = (float)ofGetWidth()/totalMin;
        ofDrawLine(i*distance, 0, i*distance, ofGetHeight());
    }
    
    ofDrawBitmapStringHighlight("Total Elapsed Presentation time: \n" +
                                 ofToString( (int)(presentationTime)/60) +"m " +ofToString(fmod(presentationTime,60),1) + "s",
                                 ofGetWidth()-300,20);

    //ofDrawBitmapStringHighlight("total Pause Time: " +ofToString(totalTimePaused), ofGetWidth()-200,140);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='p'){
        timerIsPaused = !timerIsPaused;
        
    }else if(key=='r'){
        resetTimer = true;
    }else if(key=='f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
