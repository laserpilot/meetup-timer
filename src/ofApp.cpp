#include "ofApp.h"

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
    
    totalTimePaused = 0;
    instanceTimePaused = 0;
    
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
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    
     ofFill();
     ofSetColor(0,255,0);
     ofDrawRectangle(countDownDist,0,ofGetWidth()-countDownDist, ofGetHeight());
     ofSetColor(255);
    
    //Flat 1min warning
    if(presentationTime>(totalTime-60) && presentationTime<(totalTime-59.5)){
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
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
        font.drawString("Time is\n   UP", (ofGetWidth()/2)-(font.getStringBoundingBox("Time is\n   UP", 0,0).width)/2, ofGetHeight()/2);
    }
    
    if(timerIsPaused){
        ofSetColor(255,randomColorVal2,randomColorVal);
                font.drawString("PAUSE", (ofGetWidth()/2)-(font.getStringBoundingBox("PAUSE", 0,0).width)/2, ofGetHeight()/2);
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
